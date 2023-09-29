#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <iostream>

#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

#include "utility.h"
#include "Base/generic_parsetree_antlr4.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Analyzer {

struct AnalyzerTests: public ::testing::Test {
  void SetUp() final {
    // Generate source code randomly.
    expression = Utility::testLangRandomExpr(*rc::gen::inRange(1, 10));
    std::istringstream codes{expression};

    parsetree = Parser::Parser<
      antlr4::tree::ParseTree*,
      Parser::TestLangExt,
      Base::Antlr4Node,
      Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
      ::parse<Utility::DYNAMIC>(&codes);
  }

  std::string expression;
  std::unique_ptr<
    Base::GenericParseTree<
      Base::Antlr4Node>> parsetree;
};

RC_GTEST_FIXTURE_PROP(AnalyzerTests, Basics, ()) {
  RC_ASSERT((parsetree->getText() == expression));
}

} // Analyzer
