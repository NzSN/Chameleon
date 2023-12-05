#ifndef CONDEXPR_H
#define CONDEXPR_H

#include <vector>

#include "Environment.h"
#include "Base/generic_parsetree.h"
#include "Expr/Expr.h"

#include "TransEngine/SigmaTerm.h"


namespace TransEngine {
namespace Rewrite {

class CondExpr {
public:
  // Default constructor will construct an
  // empty CondExpr.
  CondExpr(): condition_{nullptr} {}

  CondExpr(const CondExpr& ce):
    condition_{ce.condition_} {}

  CondExpr(std::unique_ptr<Expression::Expr>&& condition):
    condition_{std::move(condition)} {}

  bool isEmpty() const {
    return condition_.get() == nullptr;
  }

  inline bool operator()(Environment<Base::Antlr4Node>* env);

private:

  // Shared ownership here due to rule is copyable
  // which imply that CondExpr should also copyable.
  std::shared_ptr<Expression::Expr> condition_;
};

} // Rewrite
} // TransEngine

#endif /* CONDEXPR_H */
