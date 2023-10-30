#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <sstream>

#include "PatternMatching.h"
#include "SigmaTerm.h"
#include "utility.h"
#include "Base/generic_parsetree_antlr4.h"
#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"
#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Algorithms {

struct PatternMatchingTests: public ::testing::Test {
  void SetUp() final {
    int numOfOperand = *rc::gen::inRange(1, 10);
    testExpr = Utility::testLangRandomExpr(numOfOperand);
  }

  std::string testExpr;
};

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, MapPatternToGPT, ()) {
  std::istringstream codes{testExpr};

  auto t = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse(&codes);

  // Building a Pattern base on ParseTree,
  // without term variables.
  TransEngine::Pattern<Base::Antlr4Node> pattern(t);
  Base::GenericParseTree<Base::Antlr4Node> sigmaterm(t);

  // Assert that a pattern from a concrete parsetree
  // is isomorhpic to the parsetree.
  RC_ASSERT(
    (Concepts::NAryTree::isIsomorphic<
     Base::GenericParseTree<Base::Antlr4Node>,
     TransEngine::Pattern<Base::Antlr4Node>>(pattern, t)));
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, Matching, ()) {
  std::istringstream codes{testExpr};

  auto t = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse(&codes);

  TransEngine::Pattern<Base::Antlr4Node> pattern(t);
  Base::GenericParseTree<Base::Antlr4Node> sigmaterm(t);

  // Try to matching the pattern and the sigmaterm
  RC_ASSERT(patternMatching<Base::Antlr4Node>(
              pattern, sigmaterm).has_value());
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, WithTermVar, ()) {
  // Matching pattern "a+1" with term "1+1".

  std::istringstream codes{"a+b+1"};
  std::istringstream codes2{"1+1+1"};

  auto t = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse(&codes);

  auto t2 = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse(&codes2);


  TransEngine::Pattern<Base::Antlr4Node> pattern(t);
  Base::GenericParseTree<Base::Antlr4Node> term(t2);

  std::vector<TransEngine::Pattern<Base::Antlr4Node>>&
    children = pattern.getChildren();

  // Make sure all term var is recognized.
  RC_ASSERT(
    children[0]
    .getChildren()[0]
    .getChildren()[0]
    .isTermVar());

  RC_ASSERT(
    children[0]
    .getChildren()[0]
    .getChildren()[2]
    .isTermVar());

  RC_ASSERT(patternMatching<Base::Antlr4Node>(
              pattern, term).has_value());
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, CaptureTermVar, ()) {
  std::istringstream codes{"a+b+1"};
  std::istringstream codes2{"1+2+1"};

  auto t = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse(&codes);

  auto t2 = Parser::Parser<
    antlr4::tree::ParseTree*,
    Parser::TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse(&codes2);

  TransEngine::Pattern<Base::Antlr4Node> pattern(t);
  Base::GenericParseTree<Base::Antlr4Node> term(t2);

  CaptureTerms<Base::Antlr4Node> terms{};

  RC_ASSERT(
    patternMatchingTermCapture<Base::Antlr4Node>(
      pattern, term, &terms).has_value());

  RC_ASSERT(terms.contains("a"));
  RC_ASSERT(terms["a"]->getText() == "1");
  RC_ASSERT(terms.contains("b"));
  RC_ASSERT(terms["b"]->getText() == "2");
}

} // Algorithms
