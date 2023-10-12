#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <sstream>

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
}

} // Algorithms
