#ifndef CONDEXPR_H
#define CONDEXPR_H

#include "Environment.h"
#include "Expr/Expr.h"

namespace Chameleon {
namespace TransEngine {
namespace Rewrite {

class CondExpr {
public:
  // Default constructor will construct an
  // empty CondExpr.
  CondExpr(): condition_{nullptr} {}

  CondExpr(const CondExpr& ce):
    condition_{ce.condition_} {}

  CondExpr(CondExpr&& ce):
    condition_{ce.condition_} {}

  CondExpr(std::unique_ptr<Expression::Expr>&& condition):
    condition_{std::move(condition)} {}

  bool isEmpty() const {
    return condition_.get() == nullptr;
  }

  inline bool operator()(Environment<Base::Antlr4Node>* env);

  CondExpr& operator=(const CondExpr& expr) {
    condition_ = expr.condition_;
    return *this;
  }

  bool operator==(const CondExpr& expr) const {
    if (!condition_ || !expr.condition_) {
      return false;
    }
    return *condition_ == *expr.condition_;
  }

private:
  // Shared ownership here due to rule is copyable
  // which imply that CondExpr should also copyable.
  std::shared_ptr<Expression::Expr> condition_;
};

} // Rewrite
} // TransEngine
} // Chameleon

#endif /* CONDEXPR_H */
