#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <memory>
#include <string>
#include <istream>
#include <sstream>
#include <iostream>

#include "Parser-inl.h"
#include "Base/generic_parsetree_antlr4.h"
#include "utility.h"
#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"
#include "Concepts/n_ary_tree.h"
#include "ExternalParser.h"
#include "TransEngine/SigmaTerm.h"

namespace Parser {

struct ParserTests: public ::testing::Test {
  void SetUp() final {
      // Generate TestLang expression randomly
      expression = Utility::testLangRandomExpr(*rc::gen::inRange(1, 10));
  }

  std::string expression;
};


RC_GTEST_FIXTURE_PROP(ParserTests, IsomorphicToExtTree, ()) {
  std::istringstream codes{expression};

  auto t = Parser<
    antlr4::tree::ParseTree*,
    TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse<Base::GenericParseTree<Base::Antlr4Node>,
            Base::DYNAMIC>(&codes);

  Base::Antlr4Node nodes {
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG,
    TestLangExt::tree};

  using GPT = Base::GenericParseTree<Base::Antlr4Node>;
  auto isEqual = Concepts::NAryTree::equal<GPT, Base::Antlr4Node>(
    *t, nodes,
    [](const GPT& l, const Base::Antlr4Node& r) {
      return const_cast<GPT&>(l).getText() ==
        const_cast<Base::Antlr4Node&>(r).tree()->getText();
    });

  RC_ASSERT(isEqual);
}

RC_GTEST_FIXTURE_PROP(ParserTests, DoubleDynamicAlloc, ()) {
  std::istringstream codes{"a+b+c"};
  std::istringstream codes2{"c+b+a"};
  std::istringstream codes3{"c+b+a"};

  std::unique_ptr<TransEngine::Pattern<Base::Antlr4Node>>
    t = ParserSelect<2>
    ::parser
    ::template parse<TransEngine::Pattern<Base::Antlr4Node>,
                     Base::DYNAMIC>(&codes);

  std::unique_ptr<TransEngine::Pattern<Base::Antlr4Node>>
    t2 = ParserSelect<2>
    ::parser
    ::template parse<TransEngine::Pattern<Base::Antlr4Node>,
                     Base::DYNAMIC>(&codes2);

  RC_ASSERT(
    const_cast<Base::Antlr4Node&>(t.get()->getMeta()).lang() ==
    2);
  RC_ASSERT(
    const_cast<Base::Antlr4Node&>(t2.get()->getMeta()).lang() ==
    2);

}

} // Parser
