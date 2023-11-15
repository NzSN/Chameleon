#ifndef EXPR_H
#define EXPR_H

#include <typeinfo>
#include <memory>
#include <variant>
#include <stdexcept>

#include "TransEngine/Rewrite/Environment.h"

namespace TransEngine {
namespace Expression {

using TransEngine::Rewrite::Environment;

/////////////////////////////////////////////////////////////////////////////
//                                  Value                                  //
/////////////////////////////////////////////////////////////////////////////

// Caution: Instance of Value should be able to pass by value
//          and no resource release after instance destructed.
template<Base::GPTMeta T>
struct Value {
  bool operator==(const Value& other) = 0;
};

template<Base::GPTMeta T>
struct Unity: public Value<T> {};

template<Base::GPTMeta T>
struct Bool: public Value<T> {
  Bool(bool v_): v{v_} {}

  bool operator==(const Bool& other) {
    return v == other.v;
  }

  const bool v;
};

/////////////////////////////////////////////////////////////////////////////
//                                 Function                                //
/////////////////////////////////////////////////////////////////////////////
template<Base::GPTMeta T>
struct Arguments {
  std::vector<Value<T>> args;
};

template<Base::GPTMeta T>
struct Function {
  std::unique_ptr<Value<T>> operator()(Arguments<T>& args) = 0;
};

/////////////////////////////////////////////////////////////////////////////
//                                Expression                               //
/////////////////////////////////////////////////////////////////////////////
template<Base::GPTMeta T>
struct Expr {
  std::unique_ptr<Value<T>> operator()(Environment<T>&) = 0;
};

template<Base::GPTMeta T>
class Equal: public Expr<T> {
public:
  std::unique_ptr<Bool<T>> operator()(Environment<T>& env) {
    std::unique_ptr<Value<T>> loperand = lhs_(env);
    std::unique_ptr<Value<T>> roperand = rhs_(env);

    // Make sure type of loperand is same as
    // roperand.
    if (typeid(*loperand) != typeid(*roperand)) {
      throw std::runtime_error(
        "Failed to eval equality due to type of left operand "
        "is different from right operand");
    }

    return *loperand == *roperand;
  }
private:
  std::unique_ptr<Expr<T>> lhs_;
  std::unique_ptr<Expr<T>> rhs_;
};

template<Base::GPTMeta T>
class Call: public Expr<T> {
public:
  std::unique_ptr<Value<T>> operator()(Environment<T>& env) {
    // Evaluat all subexpressions to arguments
    Arguments<T> arguments;

    for (auto& e: args) {
      std::unique_ptr<Value<T>> v = (*e)(env);
      arguments.args.push_back(*v);
    }

    return (*f)(arguments);
  }
private:
  std::unique_ptr<Function<T>> f;
  std::vector<std::unique_ptr<Expr<T>>> args;
};

} // Expression
} // TransEngine

#endif /* EXPR_H */
