#include <gtest/gtest.h>
#include "Expr.h"


namespace TransEngine {
namespace Expression {

TEST(ExpressionTest, Value) {
  Unit<int> u1, u2;
  Bool<int> v1{true}, v2{false}, v3{true};

  // Check Value operator==
  EXPECT_TRUE(u1 != AS_VALUE(v1, int));
  EXPECT_TRUE(u2 != AS_VALUE(v1, int));
  EXPECT_TRUE(u1 == u2);

  EXPECT_TRUE(v1 != v2);
  EXPECT_TRUE(v1 == v3);
}

TEST(ExpressionTest, ConstExpression) {
  // Unit
  Constant<int> a{std::make_unique<Unit<int>>()};
  EXPECT_TRUE(*(a(nullptr)) == Unit<int>{});
  EXPECT_TRUE(*(a(nullptr)) != Bool<int>{});
  EXPECT_TRUE(*(a(nullptr)) == *(a(nullptr)));

  // Bool
  Constant<int> b{std::make_unique<Bool<int>>()};
  EXPECT_TRUE(*(b(nullptr)) != Unit<int>{});
  EXPECT_TRUE(*(b(nullptr)) == Bool<int>{});
  EXPECT_TRUE(*(b(nullptr)) == *(b(nullptr)));
}

TEST(ExpressionTest, EqualExpression) {
  // Expression () = () which should result
  // in True.
  Equal<int> a{
    std::make_unique<Constant<int>>(
      std::make_unique<Unit<int>>()),
    std::make_unique<Constant<int>>(
      std::make_unique<Unit<int>>())};
  EXPECT_TRUE(Bool<int>{true} == *a(nullptr));

  // Expression () = T which should result
  // in False.
  Equal<int> b{
    std::make_unique<Constant<int>>(
      std::make_unique<Unit<int>>()),
    std::make_unique<Constant<int>>(
      std::make_unique<Bool<int>>(true))};
  EXPECT_TRUE(Bool<int>{false} == *b(nullptr));
}

struct GenUnit: public Function<int> {
  std::unique_ptr<Value<int>> operator()(Arguments<int>* args) override {
    ++counter;
    return std::make_unique<Unit<int>>();
  }

  int counter = 0;
};

TEST(ExpressionTest, CallExpression) {
  // GenUnit is a Chameleons function
  GenUnit a{};

  // Got a Value once you evaluate the function,
  // in this case GenUnit will
  std::unique_ptr<Value<int>> v = a(nullptr);

  // Increase counter in function object
  // by side effect of function.
  a(nullptr);
  a(nullptr);

  EXPECT_TRUE(*v == Unit<int>{});
  EXPECT_TRUE(a.counter == 3);
}

} // Expression
} // TransEngine
