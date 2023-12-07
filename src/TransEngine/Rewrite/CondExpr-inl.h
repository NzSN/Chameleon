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

  if (!Expression::Value::isBoolean(*v)) {
    // Treat all unconditional expression, side effects
    // on Environment is expected from those expression,
    // as conditional expression that always be true.
    return true;
  }

  return dynamic_cast<Expression::Bool&>(*v).v;
}

} // Rewrite
} // TransEngine


#endif /* CONDEXPR-INL_H */
