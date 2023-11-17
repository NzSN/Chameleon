#ifndef EXPR_H
#define EXPR_H

#include <type_traits>
#include <typeinfo>
#include <memory>
#include <variant>
#include <stdexcept>

#include "../Environment.h"

namespace TransEngine {
namespace Expression {

using TransEngine::Rewrite::Environment;

#define APPEND_EXPR(Es, E, V...)                 \
  Es.emplace_back(                            \
    std::make_unique<E>(V)                    \
  )

#define IS_SAME_TYPE(X, Y) \
  (typeid((X)) == typeid((Y)))

/////////////////////////////////////////////////////////////////////////////
//                                  Value                                  //
/////////////////////////////////////////////////////////////////////////////

#define AS_VALUE(X, T) static_cast<Value<T>&>((X))

template<Base::GPTMeta T>
struct Bool;

template<Base::GPTMeta T>
struct Unit;

// Caution: Instance of Value should be able to pass by value
//          and no resource release after instance destructed.
template<Base::GPTMeta T>
struct Value {
  ~Value() {}
  virtual bool operator==(const Value& other) const = 0;
  virtual std::unique_ptr<Value<T>> duplicate() const = 0;

  static bool isBoolean(Value<T>& v) {
    return IS_SAME_TYPE(Bool<T>{}, v);
  }

  static bool isUnit(Value<T>& v) {
    return IS_SAME_TYPE(Unit<T>{}, v);
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

  std::unique_ptr<Value<T>> duplicate() const override {
    std::unique_ptr<Value<T>> dup =
      std::make_unique<Bool>(*this);

    return dup;
  }

  bool v;
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
class Equal: public Expr<T> {
public:
  Equal() {}

  Equal(std::unique_ptr<Expr<T>> lhs,
        std::unique_ptr<Expr<T>> rhs):
    lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  std::unique_ptr<Value<T>> operator()(Environment<T>* env) {
    std::unique_ptr<Value<T>> loperand = (*lhs_)(env);
    std::unique_ptr<Value<T>> roperand = (*rhs_)(env);

    return std::make_unique<Bool<T>>(*loperand == *roperand);
  }
private:
  std::unique_ptr<Expr<T>> lhs_;
  std::unique_ptr<Expr<T>> rhs_;
};

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
