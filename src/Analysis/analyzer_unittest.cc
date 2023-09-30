#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <iostream>
#include <typeinfo>
#include <map>
#include <tuple>

#include "analyzer.h"
#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

#include "utility.h"
#include "Base/generic_parsetree_antlr4.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Analyzer {

// An Node analyzer to analyzing a TestLang ParseTree
// to collect all operand infos.
//
// This NodeAnalyzer collect all expression information
// about the TestLang parsetree that analyzed by it.
struct NodeAnalyzerStub {
  using Antlr4GenericParseTree = Base::GenericParseTree<Base::Antlr4Node>;

  std::tuple<
    AnalyzeState, AnalyzeData<Antlr4GenericParseTree>>
  operator()(const Base::GenericParseTree<Base::Antlr4Node>& node) {
    auto& raw_node = *const_cast<Base::Antlr4Node&>(
      node.getMeta()).tree();

    auto ret = std::make_tuple<AnalyzeState>(
      {AnalyzeState::Finished}, AnalyzeData<Antlr4GenericParseTree>());

    size_t nodeTypeID = typeid(raw_node).hash_code();
    if (nodeTypeID == typeid(TestLangParser::ExprContext).hash_code()) {
      auto data = std::get<1>(ret).data;
      if (!data.contains("EXPR")) {
        auto set = AnalyzeData<Antlr4GenericParseTree>::DataSet{
          std::reference_wrapper<Antlr4GenericParseTree>(
            const_cast<Antlr4GenericParseTree&>(node))};
        data.insert({"EXPR", set});
      } else {
        data["EXPR"].insert(
          std::reference_wrapper<Antlr4GenericParseTree>(
            const_cast<Antlr4GenericParseTree&>(node)));
      }
    } else {
      /* Node type that not recognized by this analyzer */
    }

    return ret;
  }
};

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
  // Assert that Parsetree is generated correctly.
  RC_ASSERT((parsetree->getText() == expression));

  // Do analyzing.
  auto& tree = *const_cast<Base::Antlr4Node&>(
    parsetree->getMeta()).tree();

  std::cout << typeid(tree).name() << std::endl
            << typeid(TestLangParser::ExprContext).name() << std::endl;
}

} // Analyzer
