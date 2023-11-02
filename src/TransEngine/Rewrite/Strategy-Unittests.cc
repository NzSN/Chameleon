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
    ::parse<Utility::DYNAMIC>(&tCodes);

    lTree = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<Utility::DYNAMIC>(&lCodes);

    rTree = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<Utility::DYNAMIC>(&rCodes);

    lPattern = std::make_unique<PatternT>(*lTree);
    rPattern = std::make_unique<PatternT>(*rTree);

    lRule = std::make_unique<RuleT>(
      "R",
      *lPattern,
      *rPattern,
      GPT::TESTLANG);
  }

  std::istringstream tCodes;
  std::istringstream lCodes;
  std::istringstream rCodes;

  std::unique_ptr<GPT> target;
  std::unique_ptr<GPT> lTree;
  std::unique_ptr<GPT> rTree;

  std::unique_ptr<PatternT> lPattern;
  std::unique_ptr<PatternT> rPattern;

  std::unique_ptr<RuleT> lRule;
  std::unique_ptr<RuleT> rRule;
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
    ::parse<Utility::DYNAMIC>(&tCodes);

    lTree = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<Utility::DYNAMIC>(&lCodes);

    rTree = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<Utility::DYNAMIC>(&rCodes);

    lPattern = std::make_unique<PatternT>(*lTree);
    rPattern = std::make_unique<PatternT>(*rTree);

    lRule = std::make_unique<RuleT>(
      "R",
      *lPattern,
      *rPattern,
      GPT::TESTLANG);
  }

  std::istringstream tCodes;
  std::istringstream lCodes;
  std::istringstream rCodes;

  std::unique_ptr<GPT> target;
  std::unique_ptr<GPT> lTree;
  std::unique_ptr<GPT> rTree;

  std::unique_ptr<PatternT> lPattern;
  std::unique_ptr<PatternT> rPattern;

  std::unique_ptr<RuleT> lRule;
  std::unique_ptr<RuleT> rRule;
};

TEST_F(StrategySuccess, BasicMatchStrat) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  // Assert Precondition of Match Strategy
  // is satisfied.
  ASSERT_TRUE(env.matchTerm() == nullptr);

  // We construct
  MatchStra<Node>{}(*lRule, env);

  // Make sure variable bindings is done correctly.
  ASSERT_TRUE(env.matchTerm() != nullptr);
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

  MatchStra<Node>{}(*lRule, env);

  ASSERT_TRUE(env.matchTerm() == nullptr);
  ASSERT_TRUE(env.targetTerm() == target.get());
  ASSERT_TRUE(env.bindings().size() == 0);
}

TEST_F(StrategySuccess, Build) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  MatchStra<Node>{}(*lRule, env);
  BuildStra<Node>{}(*lRule, env);
}

TEST_F(StrategySuccess, TRYCASE) {
  Environment<Node> env{};
  env.setTargetTerm(target.get());

  rTree = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Node,
    GPT::TESTLANG>
    ::parse<Utility::DYNAMIC>(&rCodes);

  rPattern = std::make_unique<PatternT>(*rTree);


  auto* t = const_cast<Node&>(target->getMeta()).tree();
  t->children = const_cast<Node&>(rPattern->getMeta()).tree()->children;

}

} // Rewrite
} // TransEngine
