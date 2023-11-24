#ifndef EXPR_H
#define EXPR_H

#include <type_traits>
#include <typeinfo>
#include <memory>
#include <variant>
#include <stdexcept>

#include "Base/generic_parsetree_antlr4.h"

#include "TransEngine/Rewrite/Term.h"
#include "TransEngine/Rewrite/Environment.h"

#include "TransEngine/TransLang/ChameleonsLexer.h"
#include "TransEngine/TransLang/ChameleonsParser.h"

namespace TransEngine {
namespace Expression {

// Chameleons implement by Antlr4 currently
// so fix the adapter to Base::Antlr4Node.
using Adapter = Base::Antlr4Node;

using TransEngine::Rewrite::Environment;
using P = ChameleonsParser;

#define APPEND_EXPR(Es, E, V...) \
  Es.emplace_back(               \
    std::make_unique<E>(V)       \
  )

#define IS_SAME_TYPE(X, Y) \
  (typeid((X)) == typeid((Y)))

#define EXPR_LIST(V) \
  V(LOGICAL)         \
  V(ORDER)           \
  V(TERM)            \
  V(CONSTANT)

enum ExprType {
  ERROR_TYPE,
  LOGICAL,
  ORDER,
  TERM,
  CONSTANT,
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

  if (ctx->STRING() != nullptr) {
    return CONSTANT;
  }

  return ERROR_TYPE;
}

/////////////////////////////////////////////////////////////////////////////
//                                  Value                                  //
/////////////////////////////////////////////////////////////////////////////

#define AS_VALUE(X) static_cast<Value&>((X))

struct Bool;
struct Unit;
struct String;

// Caution: Instance of Value should be able to pass by value
//          and no resource release after instance destructed.
struct Value {
  virtual ~Value() {}
  virtual std::unique_ptr<Value> duplicate() const = 0;

  virtual bool operator==(const Value& other) const = 0;

  static bool isBoolean(Value& v);
  static bool isUnit(Value& v);
  static bool isString(Value& v);
};

struct OrderValue: public Value {
  virtual bool operator<(const OrderValue& other) const = 0;
  virtual bool operator<=(const OrderValue& other) const = 0;
  virtual bool operator>(const OrderValue& other) const = 0;
  virtual bool operator>=(const OrderValue& other) const = 0;
};

// A type same as void in C++, () in Haskell.
struct Unit: public Value {
  Unit() {}
  Unit(const Unit& other) {}
  bool operator==(const Value& other) const override {
    if (IS_SAME_TYPE(*this, other)) {
      return true;
    } else {
      return false;
    }
  }

  std::unique_ptr<Value> duplicate() const override {
    std::unique_ptr<Value> dup =
      std::make_unique<Unit>(*this);

    return dup;
  }
};

struct Bool: public Value {
  Bool(): v{true} {}
  Bool(const Bool& other):
    v{other.v} {}
  Bool(bool v_): v{v_} {}
  ~Bool() {}

  bool operator==(const Value& other) const override {
    if (IS_SAME_TYPE(*this, other)) {
      return v == dynamic_cast<const Bool&>(other).v;
    } else {
      return false;
    }
  }

  bool operator&&(const Value& other) const {
    return v && dynamic_cast<const Bool&>(other).v;
  }

  bool operator||(const Value& other) const {
    return v || dynamic_cast<const Bool&>(other).v;
  }

  std::unique_ptr<Value> duplicate() const override {
    std::unique_ptr<Value> dup =
      std::make_unique<Bool>(*this);

    return dup;
  }

  bool v;
};

// A type wrapper for std::string
struct String: public Value {
  String(): value{} {}
  String(std::string v): value{v} {}

  bool operator==(const Value& other) const final {
    if (IS_SAME_TYPE(*this, other)) {
      return value == dynamic_cast<const String&>(other).value;
    } else {
      return false;
    }
  };

  std::unique_ptr<Value> duplicate() const final {
    return std::make_unique<String>(value);
  };

  std::string value;
};

// 32bits signed integer
struct Number: public OrderValue {
  Number(): value{} {}
  Number(int32_t v): value{v} {}

  std::unique_ptr<Value> duplicate() const {
    return std::make_unique<Number>(value);
  }

#define ORDER_OP_DEFINE(OP, VT)                                     \
  bool operator OP (const VT& other) const {       \
    if (typeid(Number) != typeid(other)) {                         \
      throw std::runtime_error("Type error");                   \
    } else {                                                    \
      return value OP dynamic_cast<const Number&>(other).value; \
    }                                                           \
  }

  ORDER_OP_DEFINE(==, Value);
  ORDER_OP_DEFINE(<, OrderValue);
  ORDER_OP_DEFINE(<=, OrderValue);
  ORDER_OP_DEFINE(>, OrderValue);
  ORDER_OP_DEFINE(>=, OrderValue);
#undef ORDER_OP_DEFINE

#define NUMBER_OP_DEFINE(OP)                                 \
  std::unique_ptr<Value> operator OP (const Number& other) { \
    return std::make_unique<Number>(value OP other.value);   \
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
struct Arguments {
  std::vector<std::unique_ptr<Value>> args;
};

struct Function {
  virtual std::unique_ptr<Value> operator()(Arguments* args) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//                                Expression                               //
/////////////////////////////////////////////////////////////////////////////
struct Expr {
  ~Expr() {}
  virtual std::unique_ptr<Value> operator()(
    Environment<Adapter>*) = 0;
};

/* Rewrite Terms */
class TermRef: public Expr {
public:
  TermRef(Rewrite::TermID tid,
          Rewrite::Term<Adapter> term):
    tid_{tid}, term_{term} {}

  // Evaluating of TermRef will gain the underlying
  // value of a Term.
  std::unique_ptr<Value> operator()(
    Environment<Adapter>* env) {

    // First to check that whether is binded
    bool binded = env->bindings().isBinded(tid_);
    if (!binded) {
      throw std::runtime_error(
        "Term is not binded " + tid_);
    }

    return std::make_unique<String>(
      term_.tree.get().getText());
  }

private:
  Rewrite::TermID tid_;
  Rewrite::Term<Adapter> term_;
};

/* Literal values */
class Constant: public Expr {
public:
  // A copy of Value is spawned if an Constant expression is evaluated,
  // so Value is required to be copy constructible.
  template<typename U,
           typename = std::enable_if_t<std::is_base_of_v<Value, U> &&
                                       std::is_copy_constructible_v<U>>>
  Constant(std::unique_ptr<U> v):
    v_{std::move(v)} {}

  std::unique_ptr<Value> operator()(Environment<Adapter>*) {
    std::unique_ptr<Value> copy = v_->duplicate();

    return copy;
  }

  std::unique_ptr<Value> v_;
};

class LogiAndExpr: public Expr {
public:
  LogiAndExpr() {}

  LogiAndExpr(std::unique_ptr<Expr> lhs,
              std::unique_ptr<Expr> rhs):
    lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  std::unique_ptr<Value> operator()(Environment<Adapter>* env) final {
    std::unique_ptr<Value> loperand = (*lhs_)(env);
    std::unique_ptr<Value> roperand = (*rhs_)(env);

    if (!Value::isBoolean(*loperand) ||
        !Value::isBoolean(*roperand)) {
      throw std::runtime_error(
        "Type of operand for logical or is wrong");
    }

    return std::make_unique<Bool>(
      *dynamic_cast<Bool*>(loperand.get()) && *roperand);
  }

private:
  std::unique_ptr<Expr> lhs_;
  std::unique_ptr<Expr> rhs_;
};

class LogiOrExpr: public Expr {
public:
  LogiOrExpr() {}

  LogiOrExpr(std::unique_ptr<Expr> lhs,
             std::unique_ptr<Expr> rhs):
    lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  std::unique_ptr<Value> operator()(Environment<Adapter>* env) final {
    std::unique_ptr<Value> loperand = (*lhs_)(env);
    std::unique_ptr<Value> roperand = (*rhs_)(env);

    if (!Value::isBoolean(*loperand) ||
        !Value::isBoolean(*roperand)) {
      throw std::runtime_error(
        "Type of operand for logical or is wrong");
    }

    return std::make_unique<Bool>(
      *dynamic_cast<Bool*>(loperand.get()) || *roperand);
  }

private:
  std::unique_ptr<Expr> lhs_;
  std::unique_ptr<Expr> rhs_;
};

/////////////////////////////////////////////////////////////////////////////
//                             Order Expression                            //
/////////////////////////////////////////////////////////////////////////////
template<std::unique_ptr<Value> (*op)(Value&, Value&)>
class OrderExpr: public Expr {
public:
  OrderExpr() {}
  OrderExpr(std::unique_ptr<Expr> lhs,
            std::unique_ptr<Expr> rhs):
    lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  std::unique_ptr<Value> operator()(Environment<Adapter>* env) {
    std::unique_ptr<Value> loperand = (*lhs_)(env);
    std::unique_ptr<Value> roperand = (*rhs_)(env);

    return op(*loperand, *roperand);
  }


  bool operator==(const Value& other) const {
    return true;
  }
  std::unique_ptr<Value> duplicate() const {
    return nullptr;
  }
private:
  std::unique_ptr<Expr> lhs_;
  std::unique_ptr<Expr> rhs_;
};

#define ORDER_EXPRS_LIST(V)                                             \
  V(Equal        , ==, EQUAL        , ORDER_OP_EQ, Value)               \
  V(LessThan     , < , LESS         , ORDER_OP_LESSTHAN, OrderValue)    \
  V(LessEqual    , <=, LESS_EQUAL   , ORDER_OP_LESSEQUAL, OrderValue)   \
  V(GreaterThan  , > , GREATER      , ORDER_OP_GREATERTHAN, OrderValue) \
  V(GreaterEqual , >=, GREATER_EQUAL, ORDER_OP_GREATEREQUAL, OrderValue)

#define ORDER_EXPR_DEFINE(__E, __OP, __ENUM, __STR, __ValueType)    \
  namespace {                                                       \
                                                                    \
  inline std::unique_ptr<Value> __E##Eval(Value& lhs, Value& rhs) { \
    /* Currentl, there are only small amout of types */             \
    /* so do it by if statement. */                                 \
      return std::make_unique<Bool>(                                \
        dynamic_cast<__ValueType&>(lhs) __OP                        \
        dynamic_cast<__ValueType&>(rhs));                           \
    }                                                               \
  };                                                                \
  using __E##Base =                                                 \
    OrderExpr<__E##Eval>;                                           \
  class __E: public __E##Base {                                     \
  public:                                                           \
  __E() {}                                                          \
  __E(std::unique_ptr<Expr> lhs,                                    \
      std::unique_ptr<Expr> rhs):                                   \
    __E##Base{std::move(lhs), std::move(rhs)} {}                    \
  };

ORDER_EXPRS_LIST(ORDER_EXPR_DEFINE);

#undef ORDER_EXPR_DEFINE

class Call: public Expr {
public:
  Call(std::unique_ptr<Function> f,
       std::vector<std::unique_ptr<Expr>>&& args):
    f_{std::move(f)}, args_{std::move(args)} {}

  std::unique_ptr<Value> operator()(Environment<Adapter>* env) {
    // Evaluat all subexpressions to arguments
    Arguments arguments;

    for (auto& e: args_) {
      std::unique_ptr<Value> v = (*e)(env);
      arguments.args.push_back(std::move(v));
    }

    return std::move((*f_)(&arguments));
  }
private:
  std::unique_ptr<Function> f_;
  std::vector<std::unique_ptr<Expr>> args_;
};

} // Expression
} // TransEngine

#endif /* EXPR_H */
