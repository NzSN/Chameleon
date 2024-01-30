#include "gtest/gtest.h"
#include "Strategy-inl.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <Base/generic_parsetree_antlr4.h>
#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"


namespace TransEngine {
namespace Rewrite {

using Node = Base::Antlr4Node;
using RuleT = Rule<Node>;
using PatternT = Pattern<Node>;
using GPT = Base::GenericParseTree<Node>;

struct StrategySuccess: public ::testing::Test {
  StrategySuccess():
     tCodes{"1+2+1"}, lCodes{"a+b+1"}, rCodes{"b+a+1"} {}

  void SetUp() override {
    target = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<GPT, Utility::DYNAMIC>(&tCodes);

    lPattern = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<PatternT, Utility::DYNAMIC>(&lCodes);

    rPattern = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<PatternT, Utility::DYNAMIC>(&rCodes);

    rule = std::make_unique<RuleT>(
      "R",
      *lPattern,
      *rPattern,
      GPT::TESTLANG);
  }

  std::istringstream tCodes;
  std::istringstream lCodes;
  std::istringstream rCodes;

  std::unique_ptr<GPT> target;

  std::unique_ptr<PatternT> lPattern;
  std::unique_ptr<PatternT> rPattern;

  std::unique_ptr<RuleT> rule;
};

struct StrategyFailed: public ::testing::Test {
  StrategyFailed():
     tCodes{"1*2*1"}, lCodes{"a+b+1"}, rCodes{"b+a+1"} {}

  void SetUp() override {
    target = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<GPT, Utility::DYNAMIC>(&tCodes);

    lPattern = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<PatternT, Utility::DYNAMIC>(&lCodes);

    rPattern = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<PatternT, Utility::DYNAMIC>(&rCodes);

    rule = std::make_unique<RuleT>(
      "R",
      *lPattern,
      *rPattern,
      GPT::TESTLANG);
  }

  std::istringstream tCodes;
  std::istringstream lCodes;
  std::istringstream rCodes;

  std::unique_ptr<GPT> target;

  std::unique_ptr<PatternT> lPattern;
  std::unique_ptr<PatternT> rPattern;

  std::unique_ptr<RuleT> rule;
};

TEST_F(StrategySuccess, BasicMatchStrat) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  // Assert Precondition of Match Strategy
  // is satisfied.
  ASSERT_TRUE(env.matchTerm() == nullptr);

  // We construct
  MatchStra<Node>{}(*rule, env);

  // Make sure variable bindings is done correctly.
  ASSERT_TRUE(env.matchTerms().size() == 1);
  env.setCurrentTerm(env.matchTerms().front());

  ASSERT_TRUE(env.bindings().isBinded("a"));
  ASSERT_TRUE(env.bindings()["a"].tree.get().getText() == "1");
  ASSERT_TRUE(env.bindings().isBinded("b"));
  ASSERT_TRUE(env.bindings()["b"].tree.get().getText() == "2");
}

TEST_F(StrategyFailed, FailedToMatched) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  // Assert Precondition of Match Strategy
  // is satisfied.
  ASSERT_TRUE(env.matchTerm() == nullptr);

  MatchStra<Node>{}(*rule, env);

  ASSERT_TRUE(env.matchTerm() == nullptr);
  ASSERT_TRUE(env.targetTerm() == target.get());
  ASSERT_TRUE(env.bindings().size() == 0);
}

TEST_F(StrategySuccess, Build) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  // {| a+b+1 |} => {| b+a+1 |}
  MatchStra<Node>{}(*rule, env);
  BuildStra<Node>{}(*rule, env);

  ASSERT_TRUE(target->getText() == "2+1+1");
}

TEST_F(StrategySuccess, RuleBreakDown) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  // Break a rule to form that represent by
  // strategy languages.
  StrategySeq<Node> seq = ruleBreakDown(*rule);
  for (auto& s: seq) {
    (*s)(*rule, env);
  }

  ASSERT_TRUE(env.targetTerm()->getText() == "2+1+1");
}

TEST_F(StrategySuccess, TRYCASE) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  rPattern = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<PatternT, Utility::DYNAMIC>(&rCodes);

  auto* t = const_cast<Node&>(target->getMeta()).tree();
  t->children = const_cast<Node&>(rPattern->getMeta()).tree()->children;
}

// Side effects make by Match Strategy is required
// to revert if any where expression is evaluating to
// FALSE.
TEST_F(StrategySuccess, FailedOnWhereExpr) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  // Add Where Expression, that always evaluate for
  // false, to rule
  CondExpr expr{
    std::make_unique<Expression::Constant>(
      std::make_unique<Expression::Bool>(false))};
  rule->appendCond(expr);

  MatchStra<Node> match{};
  WhereStra<Node> where{};
  BuildStra<Node> build{};

  EXPECT_TRUE(env.bindings().size() == 0);
  EXPECT_TRUE(env.matchTerm() == nullptr);

  // Evaluating of Match Strategy result in
  // a state that there are some new bindings
  // and a term matched by left pattern of rule
  // is set to environment.
  match(*rule, env);

  // All those side effects will be revert
  // once where expressions declared here,
  // due to the expression declared here always
  // result in FALSE.
  where(*rule, env);
  EXPECT_TRUE(env.matchTerms().size() == 0);

  // Finally, Build Strategy should be evaluating
  // without erros in this case.
  build(*rule, env);
}

struct StrategyMulti: public ::testing::Test {
  StrategyMulti():
     tCodes{"1+2+3"}, lCodes{"a+b"}, rCodes{"b+a+1"} {}

  void SetUp() override {
    target = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<GPT, Utility::DYNAMIC>(&tCodes);

    lPattern = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<PatternT, Utility::DYNAMIC>(&lCodes);

    rPattern = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<PatternT, Utility::DYNAMIC>(&rCodes);

    rule = std::make_unique<RuleT>(
      "R",
      *lPattern,
      *rPattern,
      GPT::TESTLANG);
  }

  std::istringstream tCodes;
  std::istringstream lCodes;
  std::istringstream rCodes;

  std::unique_ptr<GPT> target;

  std::unique_ptr<PatternT> lPattern;
  std::unique_ptr<PatternT> rPattern;

  std::unique_ptr<RuleT> rule;
};

TEST_F(StrategyMulti, MultiMatch) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  ASSERT_TRUE(env.matchTerms().size() == 0);

  MatchMultiStra<Node>{}(*rule, env);

  ASSERT_TRUE(env.matchTerms().size() > 0);
  ASSERT_TRUE(env.targetTerm() == target.get());

  // Match result assert

  // First match
  Environment<Node>::MatchTerms::iterator iter =
    env.matchTerms().begin();

  Base::GenericParseTree<Node>* tree = std::get<0>(*iter);
  Bindings<Node>& bindings = std::get<1>(*iter);
  ASSERT_TRUE(tree->getText() == "1+2+3");
  ASSERT_TRUE(bindings.size() == 2);
  ASSERT_TRUE(bindings.isBinded("a"));
  ASSERT_TRUE(bindings["a"].tree.get().getText() == "1+2");
  ASSERT_TRUE(bindings.isBinded("b"));
  ASSERT_TRUE(bindings["b"].tree.get().getText() == "3");
  // Second match
  Base::GenericParseTree<Node>* tree2 = std::get<0>(*++iter);
  Bindings<Node>& bindings2 = std::get<1>(*iter);
  ASSERT_TRUE(tree2->getText() == "1+2");
  ASSERT_TRUE(bindings2.size() == 2);
  ASSERT_TRUE(bindings2.isBinded("a"));
  ASSERT_TRUE(bindings2["a"].tree.get().getText() == "1");
  ASSERT_TRUE(bindings2.isBinded("b"));
  ASSERT_TRUE(bindings2["b"].tree.get().getText() == "2");
}

TEST_F(StrategyMulti, WhereMulti) {
 Environment<Node> env{};
  env.setTargetTerm(target.get());

  // Condition expression to fail all
  // matchs.
  CondExpr expr{
    std::make_unique<Expression::Constant>(
      std::make_unique<Expression::Bool>(false))};
  rule->appendCond(expr);

  MatchMultiStra<Node>{}(*rule, env);
  WhereMultiStra<Node>{}(*rule, env);

  ASSERT_TRUE(env.matchTerms().size() == 0);
}

TEST_F(StrategyMulti, BuildMulti) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  MatchMultiStra<Node>{}(*rule, env);
  BuildMultiStra<Node>{}(*rule, env);

  ASSERT_TRUE(target->getText() == "3+2+1+1+1");
}

} // Rewrite
} // TransEngine
