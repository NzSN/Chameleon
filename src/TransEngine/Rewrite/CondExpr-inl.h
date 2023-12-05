#ifndef CONDEXPR_INL_H
#define CONDEXPR_INL_H

#include <stdexcept>
#include "CondExpr.h"

namespace TransEngine {
namespace Rewrite {

inline bool CondExpr::operator()(Environment<Base::Antlr4Node>* env) {
  // First to evaluate the Expression::Expr<T> then
  // check that whether the value is Boolean, return
  // if it is otherwise throw an exception.
  std::unique_ptr<Expression::Value> v = (*condition_)(env);

  // Gurantee that Value is boolean Because we have
  // no ways to detect whether an expression
  // is Boolean by checking the expression itself.
  if (!Expression::Value::isBoolean(*v)) {
     throw std::runtime_error(
      "Non-Boolean expression is evaluate within"
      "CondExpr which is not allowed");
  }

  return dynamic_cast<Expression::Bool&>(*v).v;
}

} // Rewrite
} // TransEngine


#endif /* CONDEXPR-INL_H */
