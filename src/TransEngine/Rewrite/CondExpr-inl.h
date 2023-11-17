#ifndef CONDEXPR_INL_H
#define CONDEXPR_INL_H

#include <stdexcept>
#include "CondExpr.h"

namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
bool CondExpr<T>::operator()(Environment<T>* env) {
  // First to evaluate the Expression::Expr<T> then
  // check that whether the value is Boolean, return
  // if it is otherwise throw an exception.
  std::unique_ptr<Expression::Value<T>> v = (*condition_)(env);

  // Gurantee that Value is boolean Because we have
  // no ways to detect whether an expression
  // is Boolean by checking the expression itself.
  if (!Expression::Value<T>::isBoolean(*v)) {
     throw std::runtime_error(
      "Non-Boolean expression is evaluate within"
      "CondExpr which is not allowed");
  }

  return dynamic_cast<Expression::Bool<T>&>(*v).v;
}

} // Rewrite
} // TransEngine


#endif /* CONDEXPR-INL_H */
