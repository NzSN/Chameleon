#ifndef CONDEXPR-INL_H
#define CONDEXPR-INL_H

#include "CondExpr.h"

namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
bool CondExpr<T>::operator()(Environment<T>* env) {
  // First to evaluate the Expression::Expr<T> then
  // check that whether the value is Boolean, return
  // if it is otherwise throw an exception.

  std::unique_ptr<Expression::Value<T>> v = condExpr(env);

  ...
}

} // Rewrite
} // TransEngine


#endif /* CONDEXPR-INL_H */
