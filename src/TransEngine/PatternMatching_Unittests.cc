#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <sstream>

#include "PatternMatching.h"
#include "SigmaTerm.h"
#include "utility.h"
#include "Base/generic_parsetree_antlr4.h"
#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

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
  std::istringstream codes2{testExpr};

  TransEngine::Pattern<Base::Antlr4Node> t =
    Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&codes);

  Base::ParseTree<Base::Antlr4Node> t2 =
    Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<Base::ParseTree<Base::Antlr4Node>>(&codes2);


  // Assert that a pattern from a concrete parsetree
  // is isomorhpic to the parsetree.
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, Matching, ()) {
  std::istringstream codes{testExpr};
  std::istringstream codes2{testExpr};

  TransEngine::Pattern<Base::Antlr4Node> t =
     Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&codes);

  Base::ParseTree<Base::Antlr4Node> t2 =
    Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<Base::ParseTree<Base::Antlr4Node>>(&codes2);

  // Try to matching the pattern and the sigmaterm
  RC_ASSERT(patternMatching<Base::Antlr4Node>(
              t, t2).has_value());
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, WithTermVar, ()) {
  // Matching pattern "a+1" with term "1+1".

  std::istringstream codes{"a+b+1"};
  std::istringstream codes2{"1+1+1"};

  auto t = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&codes);

  auto t2 = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<Base::ParseTree<Base::Antlr4Node>>(&codes2);


  std::vector<std::unique_ptr<TransEngine::Pattern<Base::Antlr4Node>>>&
    children = t.getChildren();

  // Make sure all term var is recognized.
  RC_ASSERT(
    children[0]
    ->getChildren()[0]
    ->getChildren()[0]
    ->isTermVar());

  RC_ASSERT(
    children[0]
    ->getChildren()[0]
    ->getChildren()[2]
    ->isTermVar());

  RC_ASSERT(patternMatching<Base::Antlr4Node>(
              t, t2).has_value());
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, CaptureTermVar, ()) {
  std::istringstream codes{"a+b+1"};
  std::istringstream codes2{"1+2+1"};

  auto t = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&codes);

  auto t2 = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<Base::ParseTree<Base::Antlr4Node>>(&codes2);


  Environment<Base::Antlr4Node> env;

  RC_ASSERT(
    patternMatchingTermCapture<Base::Antlr4Node>(
      t, t2, &env).has_value());

  RC_ASSERT(env.bindings().isBinded("a"));
  RC_ASSERT(env.bindings()["a"]
            .tree
            .get()
            .getText() == "1");
  RC_ASSERT(env.bindings().isBinded("b"));
  RC_ASSERT(env.bindings()["b"]
            .tree
            .get()
            .getText() == "2");
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, MultipleMatch, ()) {
  std::istringstream codes{"a+a"};
  std::istringstream codes2{"1+2+3"};

  auto t = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&codes);

  auto t2 = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<Base::ParseTree<Base::Antlr4Node>>(&codes2);

  auto matches = patternMatchingTermCaptureMulti<Base::Antlr4Node>(
    *t.lowerAsPossible(), t2);
  RC_ASSERT(matches.size() == 2);
  RC_ASSERT(matches[0].matched->getText() == "1+2+3");
  RC_ASSERT(matches[1].matched->getText() == "1+2");
}

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, MultipleMatch_Failed, ()) {
  std::istringstream codes{"a*a"};
  std::istringstream codes2{"1+2+3"};

  auto t = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&codes);

  auto t2 = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<Base::ParseTree<Base::Antlr4Node>>(&codes2);

  auto matches = patternMatchingTermCaptureMulti<Base::Antlr4Node>(
    *t.lowerAsPossible(), t2);
  RC_ASSERT(matches.size() == 0);
}


RC_GTEST_FIXTURE_PROP(PatternMatchingTests, MultipleMatch_Case1, ()) {
  std::istringstream pattern_1{"a*a"};
  std::istringstream pattern_2{"a+a"};
  std::istringstream codes2{"1+2+3*8+2*6"};

  auto p1 = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&pattern_1);
  auto p2 = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<TransEngine::Pattern<Base::Antlr4Node>>(&pattern_2);

  auto t = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
    ::parse<Base::ParseTree<Base::Antlr4Node>>(&codes2);

  auto matches_1 = patternMatchingTermCaptureMulti(*p1.lowerAsPossible(), t);
  RC_ASSERT(matches_1.size() == 2);
  RC_ASSERT(matches_1[0].matched->getText() == "3*8");
  RC_ASSERT(matches_1[1].matched->getText() == "2*6");


  auto matches_2 = patternMatchingTermCaptureMulti<Base::Antlr4Node>(
    *p2.lowerAsPossible(), t);
  RC_ASSERT(matches_2.size() == 3);
  RC_ASSERT(matches_2[0].matched->getText() == "1+2+3*8+2*6");
  RC_ASSERT(matches_2[1].matched->getText() == "1+2+3*8");
  RC_ASSERT(matches_2[2].matched->getText() == "1+2");
}



} // Algorithms
