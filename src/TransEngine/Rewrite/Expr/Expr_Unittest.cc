#include <gtest/gtest.h>
#include <memory>
#include "Expr.h"

#include "Base/generic_parsetree_inl.h"

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

// This function will checkging whether all of
// it's arguments has same type.
struct CheckEquality: public Function<int> {
  std::unique_ptr<Value<int>> operator()(Arguments<int>* args) override {

    Value<int>& first = *args->args[0];
    for (auto& c: args->args) {
      if (!IS_SAME_TYPE(first, *c)) {
        return std::make_unique<Bool<int>>(false);
      }
    }

    return std::make_unique<Bool<int>>(true);
  }
};

TEST(ExpressionTest, CallExpression) {
  // Build up arguments
  std::vector<std::unique_ptr<Expr<int>>> args;

  args.emplace_back(
    // Constant Expression
    std::make_unique<Constant<int>>(
      std::make_unique<Unit<int>>())
  );

  args.emplace_back(
    // Constant Expression
    std::make_unique<Constant<int>>(
      std::make_unique<Unit<int>>())
  );

  // GenUnit is a Chameleons function
  Call<int> c{
    std::make_unique<CheckEquality>(),
    std::move(args) };

  // Got a Value once you evaluate the function.
  std::unique_ptr<Value<int>> v = c(nullptr);

  EXPECT_TRUE(*v == Bool<int>{true});
}

TEST(ExpressionTest, CallExpression_FalseCase) {
  // Build up arguments
  std::vector<std::unique_ptr<Expr<int>>> args;

  APPEND_EXPR(
    args,
    Constant<int>,
    std::make_unique<Unit<int>>());

  APPEND_EXPR(
    args,
    Constant<int>,
    std::make_unique<Bool<int>>());

  // GenUnit is a Chameleons function
  Call<int> c{
    std::make_unique<CheckEquality>(),
    std::move(args) };

  // Got a Value once you evaluate the function.
  std::unique_ptr<Value<int>> v = c(nullptr);

  EXPECT_TRUE(*v == Bool<int>{false});

}

TEST(ExpressionTest, ValueIface_TypeCheck) {
  std::unique_ptr<Value<int>> v = std::make_unique<Bool<int>>();
  EXPECT_TRUE(Value<int>::isBoolean(*v));

  std::unique_ptr<Value<int>> v2 = std::make_unique<Unit<int>>();
  EXPECT_TRUE(Value<int>::isUnit(*v2));
}


struct MetaTest {

  MetaTest(std::string s):
    value{s} {}

  std::string getText() {
    return value;
  }

  bool operator==(const MetaTest& other) const {
    return value == other.value;
  }

  bool operator!=(const MetaTest& other) const {
    return value != other.value;
  }

  std::string value;
};

TEST(ExpressionTest, TermRef) {
  MetaTest m{"123"};
  Base::GenericParseTree<MetaTest> tree{m};
  Rewrite::Term<MetaTest> t{tree};
  TermRef<MetaTest> v{"ID", t};

  Environment<MetaTest> env;
  env.bindings().bind("ID", t);

  std::unique_ptr<Value<MetaTest>> termValue = v(&env);
  EXPECT_TRUE(Value<MetaTest>::isString(*termValue));
}

TEST(ExpressionTest, LogicalAnd) {
  // T T
  {
    LogiAndExpr<int> v_and{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<int>{true});
  }

  // T F
  {
    LogiAndExpr<int> v_and{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<int>{false});
  }

  // F T
  {
    LogiAndExpr<int> v_and{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<int>{false});
  }

  // F F
  {
    LogiAndExpr<int> v_and{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<int>{false});
  }
}

TEST(ExpressionTest, LogicalOr) {
  // T T
  {
    LogiOrExpr<int> v_or{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<int>{true});
  }
  // T F
  {
    LogiOrExpr<int> v_or{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<int>{true});
  }
  // F T
  {
    LogiOrExpr<int> v_or{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(true)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<int>{true});
  }
  // F F
  {
    LogiOrExpr<int> v_or{
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
      std::make_unique<Constant<int>>(std::make_unique<Bool<int>>(false)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<int>{false});
  }
}

TEST(ExpressionTest, NumberOperator) {
  /* TODO: Implement unittest for Expression::Number */
}

} // Expression
} // TransEngine
