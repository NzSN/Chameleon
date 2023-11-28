#include <gtest/gtest.h>
#include <memory>
#include "Expr.h"

#include "Base/generic_parsetree_antlr4.h"

namespace TransEngine {
namespace Expression {

TEST(ExpressionTest, Value) {
  Unit u1, u2;
  Bool v1{true}, v2{false}, v3{true};

  // Check Value operator==
  EXPECT_TRUE(u1 != AS_VALUE(v1));
  EXPECT_TRUE(u2 != AS_VALUE(v1));
  EXPECT_TRUE(u1 == u2);

  EXPECT_TRUE(v1 != v2);
  EXPECT_TRUE(v1 == v3);
}

TEST(ExpressionTest, ConstExpression) {
  // Unit
  Constant a{std::make_unique<Unit>()};
  EXPECT_TRUE(*(a(nullptr)) == Unit{});
  EXPECT_TRUE(*(a(nullptr)) != Bool{});
  EXPECT_TRUE(*(a(nullptr)) == *(a(nullptr)));

  // Bool
  Constant b{std::make_unique<Bool>()};
  EXPECT_TRUE(*(b(nullptr)) != Unit{});
  EXPECT_TRUE(*(b(nullptr)) == Bool{});
  EXPECT_TRUE(*(b(nullptr)) == *(b(nullptr)));
}

TEST(ExpressionTest, EqualExpression) {
  // Expression () = () which should result
  // in True.
  Equal a{
    std::make_unique<Constant>(
      std::make_unique<Unit>()),
    std::make_unique<Constant>(
      std::make_unique<Unit>())};
  EXPECT_TRUE(Bool{true} == *a(nullptr));

  // Expression () = T which should result
  // in False.
  Equal b{
    std::make_unique<Constant>(
      std::make_unique<Unit>()),
    std::make_unique<Constant>(
      std::make_unique<Bool>(true))};
  EXPECT_TRUE(Bool{false} == *b(nullptr));
}

// This function will checkging whether all of
// it's arguments has same type.
struct CheckEquality: public Function {
  std::unique_ptr<Value> operator()(Arguments* args) override {

    Value& first = *args->args[0];
    for (auto& c: args->args) {
      if (!IS_SAME_TYPE(first, *c)) {
        return std::make_unique<Bool>(false);
      }
    }

    return std::make_unique<Bool>(true);
  }
};

TEST(ExpressionTest, CallExpression) {
  // Build up arguments
  std::vector<std::unique_ptr<Expr>> args;

  args.emplace_back(
    // Constant Expression
    std::make_unique<Constant>(
      std::make_unique<Unit>())
  );

  args.emplace_back(
    // Constant Expression
    std::make_unique<Constant>(
      std::make_unique<Unit>())
  );

  // GenUnit is a Chameleons function
  Call c{
    std::make_unique<CheckEquality>(),
    std::move(args) };

  // Got a Value once you evaluate the function.
  std::unique_ptr<Value> v = c(nullptr);

  EXPECT_TRUE(*v == Bool{true});
}

TEST(ExpressionTest, CallExpression_FalseCase) {
  // Build up arguments
  std::vector<std::unique_ptr<Expr>> args;

  APPEND_EXPR(
    args,
    Constant,
    std::make_unique<Unit>());

  APPEND_EXPR(
    args,
    Constant,
    std::make_unique<Bool>());

  // GenUnit is a Chameleons function
  Call c{
    std::make_unique<CheckEquality>(),
    std::move(args) };

  // Got a Value once you evaluate the function.
  std::unique_ptr<Value> v = c(nullptr);

  EXPECT_TRUE(*v == Bool{false});

}

TEST(ExpressionTest, ValueIface_TypeCheck) {
  std::unique_ptr<Value> v = std::make_unique<Bool>();
  EXPECT_TRUE(Value::isBoolean(*v));

  std::unique_ptr<Value> v2 = std::make_unique<Unit>();
  EXPECT_TRUE(Value::isUnit(*v2));
}

struct Antlr4ParseTreeStub: public antlr4::tree::ParseTree {
  Antlr4ParseTreeStub(std::string text_):
    antlr4::tree::ParseTree{
      antlr4::tree::ParseTreeType::TERMINAL},
    text{text_} {}

  ~Antlr4ParseTreeStub() {}

  std::string toStringTree(bool pretty = false) {
    return "";
  }

  std::string toString() {
    return text;
  }

  std::string toStringTree(antlr4::Parser* parser, bool pretty = false) {
    return text;
  }

  bool operator==(const ParseTree &other) {
    return true;
  }

  std::any accept(antlr4::tree::ParseTreeVisitor* visitor) {
    return 0;
  }

  std::string getText() {
    return text;
  }

  antlr4::misc::Interval getSourceInterval() {
    return antlr4::misc::Interval{};
  }

  std::string text;
};

TEST(ExpressionTest, TermRef) {
  Antlr4ParseTreeStub stub{"123"};
  Base::Antlr4Node node{2, &stub};
  Base::GenericParseTree<Base::Antlr4Node> tree{node};
  Rewrite::Term<Base::Antlr4Node> t{tree};

  // Create a term
  Term term{&t};

  TermRef v{"ID", term};

  Environment<Base::Antlr4Node> env;
  env.bindings().bind("ID", t);

  std::unique_ptr<Value> termValue = v(&env);
  EXPECT_TRUE(Value::isString(*termValue));
}

TEST(ExpressionTest, LogicalAnd) {
  // T T
  {
    LogiAndExpr v_and{
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool{true});
  }

  // T F
  {
    LogiAndExpr v_and{
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool{false});
  }

  // F T
  {
    LogiAndExpr v_and{
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool{false});
  }

  // F F
  {
    LogiAndExpr v_and{
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
    };
    EXPECT_TRUE(*v_and(nullptr) == Bool{false});
  }
}

TEST(ExpressionTest, LogicalOr) {
  // T T
  {
    LogiOrExpr v_or{
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool{true});
  }
  // T F
  {
    LogiOrExpr v_or{
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool{true});
  }
  // F T
  {
    LogiOrExpr v_or{
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
      std::make_unique<Constant>(std::make_unique<Bool>(true)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool{true});
  }
  // F F
  {
    LogiOrExpr v_or{
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
      std::make_unique<Constant>(std::make_unique<Bool>(false)),
    };
    EXPECT_TRUE(*v_or(nullptr) == Bool{false});
  }
}

// TEST(ExpressionTest, NumberOperator) {
//   /* TODO: Implement unittest for Expression::Number */
// }

} // Expression
} // TransEngine
