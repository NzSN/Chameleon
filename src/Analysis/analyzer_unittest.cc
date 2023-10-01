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

using Antlr4GenericParseTree = Base::GenericParseTree<Base::Antlr4Node>;

// An Node analyzer to analyzing a TestLang ParseTree
// to collect all operand infos.
//
// This NodeAnalyzer collect all expression information
// about the TestLang parsetree that analyzed by it.
struct NodeAnalyzerStub {

  std::tuple<
    AnalyzeState, AnalyzeData<Antlr4GenericParseTree>>
  operator()(Base::GenericParseTree<Base::Antlr4Node>& node) {
    auto& raw_node = *const_cast<Base::Antlr4Node&>(
      node.getMeta()).tree();

    auto ret = std::make_tuple<AnalyzeState>(
      {AnalyzeState::Finished}, AnalyzeData<Antlr4GenericParseTree>());

    size_t nodeTypeID = typeid(raw_node).hash_code();
    if (nodeTypeID == typeid(TestLangParser::ExprContext).hash_code()) {
      auto data = std::get<1>(ret).data;
      if (!data.contains("EXPR")) {
        auto set = AnalyzeData<Antlr4GenericParseTree>::DataSet{
          std::reference_wrapper<Antlr4GenericParseTree>(node)};
        data.insert({"EXPR", set});
      } else {
        data["EXPR"].insert(
          std::reference_wrapper<Antlr4GenericParseTree>(
            const_cast<Antlr4GenericParseTree&>(node)));
      }
    } else if (nodeTypeID == typeid(TestLangParser::ProgContext).hash_code()) {
      std::get<0>(ret) = {AnalyzeState::Analyzing};
    } else {
      /* Node type that not recognized by this analyzer */
    }

    return ret;
  }
};

struct AnalyzerTests: public ::testing::Test {
  void SetUp() final {
    // Generate source code randomly.
    numOfExpr = *rc::gen::inRange(1, 10);
    expression = Utility::testLangRandomExpr(numOfExpr);
    std::istringstream codes{expression};

    parsetree = Parser::Parser<
      antlr4::tree::ParseTree*,
      Parser::TestLangExt,
      Base::Antlr4Node,
      Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
      ::parse<Utility::DYNAMIC>(&codes);
  }

  int numOfExpr;
  std::string expression;
  std::unique_ptr<
    Base::GenericParseTree<
      Base::Antlr4Node>> parsetree;
};

RC_GTEST_FIXTURE_PROP(AnalyzerTests, Basics, ()) {
  // Assert that Parsetree is generated correctly.
  RC_ASSERT((parsetree->getText() == expression));

  // Do analyzing.
  NodeAnalyzerStub analyzer{} ;
  AnalyzeData<Antlr4GenericParseTree> info =
    Analyzer<Antlr4GenericParseTree, NodeAnalyzerStub>::Analyze(
    *parsetree, analyzer);

  RC_ASSERT(info.data.size() == 1);
  RC_ASSERT(info.data["EXPR"].size() == numOfExpr);
}

} // Analyzer
