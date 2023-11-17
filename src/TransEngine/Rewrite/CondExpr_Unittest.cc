#include <gtest/gtest.h>
#include "CondExpr-inl.h"

namespace TransEngine {
namespace Rewrite {

TEST(CondExprTest, Intro) {
  // This Unittest introduce how and CondExpr is constructed
  // and evaluated.
  std::unique_ptr<Expression::Expr<int>> equalExpr =
    std::make_unique<Expression::Equal<int>>(
      std::make_unique<Expression::Constant<int>>(
        std::make_unique<Expression::Unit<int>>()),
      std::make_unique<Expression::Constant<int>>(
        std::make_unique<Expression::Unit<int>>())
      );

  CondExpr<int> cond{std::move(equalExpr)};

  EXPECT_TRUE(cond(nullptr));
}

TEST(CondExprTest, CopySemantic) {
  std::unique_ptr<Expression::Expr<int>> constExpr =
    std::make_unique<Expression::Constant<int>>(
      std::make_unique<Expression::Unit<int>>());

  CondExpr<int> cond{std::move(constExpr)};

  // Move cond to cond2
  CondExpr<int> cond2{cond};

  EXPECT_TRUE(!cond2.isEmpty() && !cond.isEmpty());
}


} // Rewrite
} // TransEngine
