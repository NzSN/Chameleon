#ifndef EXPR_H
#define EXPR_H

#include <type_traits>
#include <typeinfo>
#include <memory>
#include <variant>
#include <stdexcept>

#include "TransEngine/Rewrite/Term.h"
#include "TransEngine/Rewrite/Environment.h"

#include "TransEngine/TransLang/ChameleonsLexer.h"
#include "TransEngine/TransLang/ChameleonsParser.h"

namespace TransEngine {
namespace Expression {

using TransEngine::Rewrite::Environment;
using P = ChameleonsParser;

#define APPEND_EXPR(Es, E, V...)                 \
  Es.emplace_back(                            \
    std::make_unique<E>(V)                    \
  )

#define IS_SAME_TYPE(X, Y) \
  (typeid((X)) == typeid((Y)))

#define EXPR_LIST(V) \
  V(LOGICAL)         \
  V(ORDER)           \
  V(TERM)            \
  V(NUMBER)

enum ExprType {
  ERROR_TYPE,
  LOGICAL,
  ORDER,
  TERM,
  NUMBER,
  TYPE_COUNT,
};

enum OrderExprType {
  EQUAL,
  LESS,
  LESS_EQUAL,
  GREATER,
  GREATER_EQUAL,
};

// Logical operator
constexpr char LOGI_OP_AND[]  = "AND";
constexpr char LOGI_OP_OR[] = "OR";

// Order operator
constexpr char ORDER_OP_EQ[] = "=";
constexpr char ORDER_OP_LESSTHAN[] = "<";
constexpr char ORDER_OP_LESSEQUAL[] = "<=";
constexpr char ORDER_OP_GREATERTHAN[] = ">";
constexpr char ORDER_OP_GREATEREQUAL[] = ">=";

inline ExprType getExprType(P::CondExprContext* ctx) {
  if (ctx->LOGICOP() != nullptr) {
    return LOGICAL;
  }

  if (ctx->ORDEROP() != nullptr) {
    return ORDER;
  }

  if (ctx->TERM_VAR() != nullptr) {
    return TERM;
  }

  if (ctx->NUMBER() != nullptr) {
    return NUMBER;
  }

  return ERROR_TYPE;
}

/////////////////////////////////////////////////////////////////////////////
//                                  Value                                  //
/////////////////////////////////////////////////////////////////////////////

#define AS_VALUE(X, T) static_cast<Value<T>&>((X))

template<Base::GPTMeta T>
struct Bool;

template<Base::GPTMeta T>
struct Unit;

template<Base::GPTMeta T>
struct String;

// Caution: Instance of Value should be able to pass by value
//          and no resource release after instance destructed.
template<Base::GPTMeta T>
struct Value {
  ~Value() {}
  virtual bool operator==(const Value& other) const = 0;
  virtual std::unique_ptr<Value> duplicate() const = 0;

  static bool isBoolean(Value<T>& v) {
    return IS_SAME_TYPE(Bool<T>{}, v);
  }

  static bool isUnit(Value<T>& v) {
    return IS_SAME_TYPE(Unit<T>{}, v);
  }

  static bool isString(Value<T>& v) {
    return IS_SAME_TYPE(String<T>{}, v);
  }
};

// A type same as void in C++, () in Haskell.
template<Base::GPTMeta T>
struct Unit: public Value<T> {
  Unit() {}
  Unit(const Unit& other) {}
  bool operator==(const Value<T>& other) const override {
    if (IS_SAME_TYPE(*this, other)) {
      std::cout << typeid(*this).name() << std::endl;
      std::cout << typeid(other).name() << std::endl;
      return true;
    } else {
      return false;
    }
  }

  std::unique_ptr<Value<T>> duplicate() const override {
    std::unique_ptr<Value<T>> dup =
      std::make_unique<Unit>(*this);

    return dup;
  }
};

template<Base::GPTMeta T>
struct Bool: public Value<T> {
  Bool(): v{true} {}
  Bool(const Bool& other):
    v{other.v} {}
  Bool(bool v_): v{v_} {}
  ~Bool() {}

  bool operator==(const Value<T>& other) const override {
    if (IS_SAME_TYPE(*this, other)) {
      return v == dynamic_cast<const Bool<T>&>(other).v;
    } else {
      return false;
    }
  }

  bool operator&&(const Value<T>& other) const {
    return v && dynamic_cast<const Bool<T>&>(other).v;
  }

  bool operator||(const Value<T>& other) const {
    return v || dynamic_cast<const Bool<T>&>(other).v;
  }

  std::unique_ptr<Value<T>> duplicate() const {
    std::unique_ptr<Value<T>> dup =
      std::make_unique<Bool>(*this);

    return dup;
  }

  bool v;
};

// A type wrapper for std::string
template<Base::GPTMeta T>
struct String: public Value<T> {
  String(): value{} {}
  String(std::string v): value{v} {}

  bool operator==(const Value<T>& other) const final {
    if (IS_SAME_TYPE(*this, other)) {
      return value == dynamic_cast<const String&>(other).value;
    } else {
      return false;
    }
  };

  std::unique_ptr<Value<T>> duplicate() const final {
    return std::make_unique<String>(value);
  };

  std::string value;
};

// 32bits signed integer
template<Base::GPTMeta T>
struct Number: public Value<T> {
  Number(): value{} {}
  Number(int32_t v): value{v} {}

  #define ORDER_OP_DEFINE(OP)                        \
    bool operator OP (const Number& other) {         \
      return value OP other.value;                   \
    }

  ORDER_OP_DEFINE(==);
  ORDER_OP_DEFINE(<);
  ORDER_OP_DEFINE(<=);
  ORDER_OP_DEFINE(>);
  ORDER_OP_DEFINE(>=);

  #undef ORDER_OP_DEFINE

  #define NUMBER_OP_DEFINE(OP)                                      \
    std::unique_ptr<Value<T>> operator OP (const Number& other) { \
      return std::make_unique<Number>(value OP other.value);      \
    }

  NUMBER_OP_DEFINE(+);
  NUMBER_OP_DEFINE(-);
  NUMBER_OP_DEFINE(*);
  NUMBER_OP_DEFINE(/);

  #undef NUMBER_OP_DEFINE

  int32_t value;
};

/////////////////////////////////////////////////////////////////////////////
//                                 Function                                //
/////////////////////////////////////////////////////////////////////////////
template<Base::GPTMeta T>
struct Arguments {
  std::vector<std::unique_ptr<Value<T>>> args;
};

template<Base::GPTMeta T>
struct Function {
  virtual std::unique_ptr<Value<T>> operator()(Arguments<T>* args) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//                                Expression                               //
/////////////////////////////////////////////////////////////////////////////
template<Base::GPTMeta T>
struct Expr {
  ~Expr() {}
  virtual std::unique_ptr<Value<T>> operator()(Environment<T>*) = 0;
};

/* Rewrite Terms */
template<Base::GPTMeta T>
class TermRef: public Expr<T> {
public:
  TermRef(Rewrite::TermID tid, Rewrite::Term<T> term):
    tid_{tid}, term_{term} {}

  // Evaluating of TermRef will gain the underlying value of a Term.
  std::unique_ptr<Value<T>> operator()(Environment<T>* env) {
    // First to check that whether is binded
    bool binded = env->bindings().isBinded(tid_);
    if (!binded) {
      throw std::runtime_error(
        "Term is not binded " + tid_);
    }

    return std::make_unique<String<T>>(
      term_.tree.get().getText());
  }

private:
  Rewrite::TermID tid_;
  Rewrite::Term<T> term_;
};

/* Literal values */
template<Base::GPTMeta T>
class Constant: public Expr<T> {
public:
  // A copy of Value is spawned if an Constant expression is evaluated,
  // so Value is required to be copy constructible.
  template<typename U,
           typename = std::enable_if_t<std::is_base_of_v<Value<T>, U> &&
                                       std::is_copy_constructible_v<U>>>
  Constant(std::unique_ptr<U> v):
    v_{std::move(v)} {}

  std::unique_ptr<Value<T>> operator()(Environment<T>*) {
    std::unique_ptr<Value<T>> copy = v_->duplicate();

    return copy;
  }

  std::unique_ptr<Value<T>> v_;
};

template<Base::GPTMeta T>
class LogiAndExpr: public Expr<T> {
public:
  LogiAndExpr() {}

  LogiAndExpr(std::unique_ptr<Expr<T>> lhs,
              std::unique_ptr<Expr<T>> rhs):
    lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  std::unique_ptr<Value<T>> operator()(Environment<T>* env) final {
    std::unique_ptr<Value<T>> loperand = (*lhs_)(env);
    std::unique_ptr<Value<T>> roperand = (*rhs_)(env);

    if (!Value<T>::isBoolean(*loperand) ||
        !Value<T>::isBoolean(*roperand)) {
      throw std::runtime_error(
        "Type of operand for logical or is wrong");
    }

    return std::make_unique<Bool<T>>(
      *dynamic_cast<Bool<T>*>(loperand.get()) && *roperand);
  }

private:
  std::unique_ptr<Expr<T>> lhs_;
  std::unique_ptr<Expr<T>> rhs_;
};

template<Base::GPTMeta T>
class LogiOrExpr: public Expr<T> {
public:
  LogiOrExpr() {}

  LogiOrExpr(std::unique_ptr<Expr<T>> lhs,
             std::unique_ptr<Expr<T>> rhs):
    lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  std::unique_ptr<Value<T>> operator()(Environment<T>* env) final {
    std::unique_ptr<Value<T>> loperand = (*lhs_)(env);
    std::unique_ptr<Value<T>> roperand = (*rhs_)(env);

    if (!Value<T>::isBoolean(*loperand) ||
        !Value<T>::isBoolean(*roperand)) {
      throw std::runtime_error(
        "Type of operand for logical or is wrong");
    }

    return std::make_unique<Bool<T>>(
      *dynamic_cast<Bool<T>*>(loperand.get()) || *roperand);
  }

private:
  std::unique_ptr<Expr<T>> lhs_;
  std::unique_ptr<Expr<T>> rhs_;
};

/////////////////////////////////////////////////////////////////////////////
//                             Order Expression                            //
/////////////////////////////////////////////////////////////////////////////
template<Base::GPTMeta T,
         std::unique_ptr<Value<T>> (*op)(Value<T>&, Value<T>&)>
class OrderExpr: public Expr<T> {
public:
  OrderExpr() {}
  OrderExpr(std::unique_ptr<Expr<T>> lhs,
            std::unique_ptr<Expr<T>> rhs):
    lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  std::unique_ptr<Value<T>> operator()(Environment<T>* env) {
    std::unique_ptr<Value<T>> loperand = (*lhs_)(env);
    std::unique_ptr<Value<T>> roperand = (*rhs_)(env);

    return op(*loperand, *roperand);
  }
private:
  std::unique_ptr<Expr<T>> lhs_;
  std::unique_ptr<Expr<T>> rhs_;
};

#define ORDER_EXPRS_LIST(V)                                                  \
  V(Equal        , ==, EQUAL        , ORDER_OP_EQ)                                      \
  V(LessThan     , < , LESS         , ORDER_OP_LESSTHAN)           \
  V(LessEqual    , <=, LESS_EQUAL   , ORDER_OP_LESSEQUAL)  \
  V(GreaterThan  , > , GREATER      , ORDER_OP_GREATERTHAN) \
  V(GreaterEqual , >=, GREATER_EQUAL, ORDER_OP_GREATEREQUAL)

#define ORDER_EXPR_DEFINE(__E, __OP, __ENUM, __STR)                   \
  namespace {                                                         \
                                                                      \
  template<typename T>                                                \
  std::unique_ptr<Value<T>> __E##Eval(Value<T>& lhs, Value<T>& rhs) { \
    return std::make_unique<Bool<T>>(lhs __OP rhs);                   \
  };                                                                  \
  template<Base::GPTMeta T>                                           \
  using __E##Base =                                                   \
    OrderExpr<T, __E##Eval<T>>;                                       \
  }                                                                   \
                                                                      \
  template<Base::GPTMeta T>                                           \
  class __E: public __E##Base<T> {                                    \
  public:                                                             \
  __E() {}                                                            \
  __E(std::unique_ptr<Expr<T>> lhs,                                   \
      std::unique_ptr<Expr<T>> rhs):                                  \
    __E##Base<T>{std::move(lhs), std::move(rhs)} {}                   \
  };

ORDER_EXPRS_LIST(ORDER_EXPR_DEFINE);

#undef ORDER_EXPR_DEFINE

template<Base::GPTMeta T>
class Call: public Expr<T> {
public:
  Call(std::unique_ptr<Function<T>> f,
       std::vector<std::unique_ptr<Expr<T>>>&& args):
    f_{std::move(f)}, args_{std::move(args)} {}

  std::unique_ptr<Value<T>> operator()(Environment<T>* env) {
    // Evaluat all subexpressions to arguments
    Arguments<T> arguments;

    for (auto& e: args_) {
      std::unique_ptr<Value<T>> v = (*e)(env);
      arguments.args.push_back(std::move(v));
    }

    return std::move((*f_)(&arguments));
  }
private:
  std::unique_ptr<Function<T>> f_;
  std::vector<std::unique_ptr<Expr<T>>> args_;
};

} // Expression
} // TransEngine

#endif /* EXPR_H */
