#include <gtest/gtest.h>
#include <memory>
#include "Expr.h"

#include "Base/generic_parsetree_antlr4.h"

namespace TransEngine {
namespace Expression {

TEST(ExpressionTest, Value) {
  Unit<Base::Antlr4Node> u1, u2;
  Bool<Base::Antlr4Node> v1{true}, v2{false}, v3{true};

  // Check Value operator==
  EXPECT_TRUE(u1 != AS_VALUE(v1, Base::Antlr4Node));
  EXPECT_TRUE(u2 != AS_VALUE(v1, Base::Antlr4Node));
  EXPECT_TRUE(u1 == u2);

  EXPECT_TRUE(v1 != v2);
  EXPECT_TRUE(v1 == v3);
}

TEST(ExpressionTest, ConstExpression) {
  // Unit
  Constant<Base::Antlr4Node> a{std::make_unique<Unit<Base::Antlr4Node>>()};
  EXPECT_TRUE(*(a(nullptr)) == Unit<Base::Antlr4Node>{});
  EXPECT_TRUE(*(a(nullptr)) != Bool<Base::Antlr4Node>{});
  EXPECT_TRUE(*(a(nullptr)) == *(a(nullptr)));

  // Bool
  Constant<Base::Antlr4Node> b{std::make_unique<Bool<Base::Antlr4Node>>()};
  EXPECT_TRUE(*(b(nullptr)) != Unit<Base::Antlr4Node>{});
  EXPECT_TRUE(*(b(nullptr)) == Bool<Base::Antlr4Node>{});
  EXPECT_TRUE(*(b(nullptr)) == *(b(nullptr)));
}

TEST(ExpressionTest, EqualExpression) {
  // Expression () = () which should result
  // in True.
  Equal<Base::Antlr4Node> a{
    std::make_unique<Constant<Base::Antlr4Node>>(
      std::make_unique<Unit<Base::Antlr4Node>>()),
    std::make_unique<Constant<Base::Antlr4Node>>(
      std::make_unique<Unit<Base::Antlr4Node>>())};
  EXPECT_TRUE(Bool<Base::Antlr4Node>{true} == *a(nullptr));

  // Expression () = T which should result
  // in False.
  Equal<Base::Antlr4Node> b{
    std::make_unique<Constant<Base::Antlr4Node>>(
      std::make_unique<Unit<Base::Antlr4Node>>()),
    std::make_unique<Constant<Base::Antlr4Node>>(
      std::make_unique<Bool<Base::Antlr4Node>>(true))};
  EXPECT_TRUE(Bool<Base::Antlr4Node>{false} == *b(nullptr));
}

// This function will checkging whether all of
// it's arguments has same type.
struct CheckEquality: public Function<Base::Antlr4Node> {
  std::unique_ptr<Value<Base::Antlr4Node>> operator()(Arguments<Base::Antlr4Node>* args) override {

    Value<Base::Antlr4Node>& first = *args->args[0];
    for (auto& c: args->args) {
      if (!IS_SAME_TYPE(first, *c)) {
        return std::make_unique<Bool<Base::Antlr4Node>>(false);
      }
    }

    return std::make_unique<Bool<Base::Antlr4Node>>(true);
  }
};

TEST(ExpressionTest, CallExpression) {
  // Build up arguments
  std::vector<std::unique_ptr<Expr<Base::Antlr4Node>>> args;

  args.emplace_back(
    // Constant Expression
    std::make_unique<Constant<Base::Antlr4Node>>(
      std::make_unique<Unit<Base::Antlr4Node>>())
  );

  args.emplace_back(
    // Constant Expression
    std::make_unique<Constant<Base::Antlr4Node>>(
      std::make_unique<Unit<Base::Antlr4Node>>())
  );

  // GenUnit is a Chameleons function
  Call<Base::Antlr4Node> c{
    std::make_unique<CheckEquality>(),
    std::move(args) };

  // Got a Value once you evaluate the function.
  std::unique_ptr<Value<Base::Antlr4Node>> v = c(nullptr);

  EXPECT_TRUE(*v == Bool<Base::Antlr4Node>{true});
}

TEST(ExpressionTest, CallExpression_FalseCase) {
  // Build up arguments
  std::vector<std::unique_ptr<Expr<Base::Antlr4Node>>> args;

  APPEND_EXPR(
    args,
    Constant<Base::Antlr4Node>,
    std::make_unique<Unit<Base::Antlr4Node>>());

  APPEND_EXPR(
    args,
    Constant<Base::Antlr4Node>,
    std::make_unique<Bool<Base::Antlr4Node>>());

  // GenUnit is a Chameleons function
  Call<Base::Antlr4Node> c{
    std::make_unique<CheckEquality>(),
    std::move(args) };

  // Got a Value once you evaluate the function.
  std::unique_ptr<Value<Base::Antlr4Node>> v = c(nullptr);

  EXPECT_TRUE(*v == Bool<Base::Antlr4Node>{false});

}

TEST(ExpressionTest, ValueIface_TypeCheck) {
  std::unique_ptr<Value<Base::Antlr4Node>> v = std::make_unique<Bool<Base::Antlr4Node>>();
  EXPECT_TRUE(Value<Base::Antlr4Node>::isBoolean(*v));

  std::unique_ptr<Value<Base::Antlr4Node>> v2 = std::make_unique<Unit<Base::Antlr4Node>>();
  EXPECT_TRUE(Value<Base::Antlr4Node>::isUnit(*v2));
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
    LogiAndExpr<Base::Antlr4Node> v_and{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<Base::Antlr4Node>{true});
  }

  // T F
  {
    LogiAndExpr<Base::Antlr4Node> v_and{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<Base::Antlr4Node>{false});
  }

  // F T
  {
    LogiAndExpr<Base::Antlr4Node> v_and{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<Base::Antlr4Node>{false});
  }

  // F F
  {
    LogiAndExpr<Base::Antlr4Node> v_and{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool<Base::Antlr4Node>{false});
  }
}

TEST(ExpressionTest, LogicalOr) {
  // T T
  {
    LogiOrExpr<Base::Antlr4Node> v_or{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<Base::Antlr4Node>{true});
  }
  // T F
  {
    LogiOrExpr<Base::Antlr4Node> v_or{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<Base::Antlr4Node>{true});
  }
  // F T
  {
    LogiOrExpr<Base::Antlr4Node> v_or{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(true)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<Base::Antlr4Node>{true});
  }
  // F F
  {
    LogiOrExpr<Base::Antlr4Node> v_or{
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
      std::make_unique<Constant<Base::Antlr4Node>>(std::make_unique<Bool<Base::Antlr4Node>>(false)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool<Base::Antlr4Node>{false});
  }
}

TEST(ExpressionTest, NumberOperator) {
  /* TODO: Implement unittest for Expression::Number */
}

} // Expression
} // TransEngine
