#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "ExprTree.h"

namespace Chameleon::Utility {

struct IntegerOP {
  virtual ~IntegerOP() {};
  virtual int operator()(std::optional<int> lhs,
                         std::optional<int> rhs,
                         int* count)
    { return lhs.value(); };
};

struct IntegerPlus: public IntegerOP {
  ~IntegerPlus() {};
  int operator()(std::optional<int> lhs,
                 std::optional<int> rhs,
                 int* count) override {
    assert(lhs.has_value() && rhs.has_value());
    ++(*count);
    return lhs.value() + rhs.value();
  }
};

struct IntegerMulti: public IntegerOP {
  ~IntegerMulti() {};
  int operator()(std::optional<int> lhs,
                 std::optional<int> rhs,
                 int* count) override {
    assert(lhs.has_value() && rhs.has_value());
    ++(*count);
    return lhs.value() * rhs.value();
  }
};

struct PlusOne: public IntegerOP {
  ~PlusOne() {};
  int operator()(std::optional<int> lhs,
                 std::optional<int> rhs,
                 int* count) override {
    assert(lhs.has_value());
    ++(*count);
    return lhs.value() + 1;
  }
};

struct ExprTreeTests: public ::testing::Test {
  void SetUp() override {

  }
};

using IntOperator =
  std::function<int(std::optional<int>, std::optional<int>, int*)>;
using IntExprTree =
  BinExprTree<int, int,
              IntOperator,
              int*>;
TEST(ExprTreeTests, Basics) {
  // +(1,2)

  // Spawn root
  IntExprTree tree{
    IntExprTree::OPERATOR,
    IntegerPlus{}};
  // Then give two operands to this oeprator.
  tree.setL(std::make_unique<IntExprTree>(IntExprTree::OPERAND, 1));
  tree.setR(std::make_unique<IntExprTree>(IntExprTree::OPERAND, 2));

  int count = 0;

  // Evaluate the expression
  ASSERT_EQ(3, tree(&count));
  ASSERT_EQ(1, count);
}

TEST(ExprTreeTests, WithUnary) {
  // +(+(1,2),++1)

  // Sawn root
  IntExprTree tree{
    IntExprTree::OPERATOR,
    IntegerPlus{}};

  // Left child
  std::unique_ptr<IntExprTree> subPlus =
    std::make_unique<IntExprTree>(
      IntExprTree::OPERATOR,
      IntegerPlus{});
  subPlus->setL(std::make_unique<IntExprTree>(IntExprTree::OPERAND, 1));
  subPlus->setR(std::make_unique<IntExprTree>(IntExprTree::OPERAND, 2));

  // Right child
  std::unique_ptr<IntExprTree> subPlusOne =
    std::make_unique<IntExprTree>(
      IntExprTree::OPERATOR,
      PlusOne{});
  subPlusOne->setL(std::make_unique<IntExprTree>(IntExprTree::OPERAND, 1));

  tree.setL(std::move(subPlus));
  tree.setR(std::move(subPlusOne));

  int count = 0;
  ASSERT_EQ(5, tree(&count));
  ASSERT_EQ(3, count);
}

TEST(ExprTreeTests, SideEffectLeaf) {

}

} // Utility
