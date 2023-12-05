#include <gtest/gtest.h>
#include "CondExpr-inl.h"

namespace TransEngine {
namespace Rewrite {

TEST(CondExprTest, Intro) {
  // This Unittest introduce how and CondExpr is constructed
  // and evaluated.
  std::unique_ptr<Expression::Expr> equalExpr =
    std::make_unique<Expression::Equal>(
      std::make_unique<Expression::Constant>(
        std::make_unique<Expression::Unit>()),
      std::make_unique<Expression::Constant>(
        std::make_unique<Expression::Unit>())
      );

  CondExpr cond{std::move(equalExpr)};

  EXPECT_TRUE(cond(nullptr));
}

TEST(CondExprTest, CopySemantic) {
  std::unique_ptr<Expression::Expr> constExpr =
    std::make_unique<Expression::Constant>(
      std::make_unique<Expression::Unit>());

  CondExpr cond{std::move(constExpr)};

  // Move cond to cond2
  CondExpr cond2{cond};

  EXPECT_TRUE(!cond2.isEmpty() && !cond.isEmpty());
}


} // Rewrite
} // TransEngine
