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
      {AnalyzeState::Analyzing}, AnalyzeData<Antlr4GenericParseTree>());

    size_t nodeTypeID = typeid(raw_node).hash_code();
    if (nodeTypeID == typeid(TestLangParser::ExprContext).hash_code()) {
      auto& data = std::get<1>(ret).data;
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
      /* Do nothing */
    } else if (nodeTypeID == typeid(antlr4::tree::TerminalNodeImpl).hash_code()) {
      std::get<0>(ret) = {AnalyzeState::Finished};
    } else {
      /* Node type that not recognized by this analyzer */
    }

    return ret;
  }
};

struct AnalyzerTests: public ::testing::Test {
  void SetUp() final {
    // Generate source code randomly.
    numOfOperand = *rc::gen::inRange(1, 10);
    expression = Utility::testLangRandomExpr(numOfOperand);
    std::istringstream codes{expression};

    parsetree = Parser::Parser<
      antlr4::tree::ParseTree*,
      Parser::TestLangExt,
      Base::Antlr4Node,
      Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
      ::parse<Utility::DYNAMIC>(&codes);
  }

  int numOfOperand;
  std::string expression;
  std::unique_ptr<
    Base::GenericParseTree<
      Base::Antlr4Node>> parsetree;
};

RC_GTEST_FIXTURE_PROP(AnalyzerTests, Basics, ()) {
  // Assert that Parsetree is generated correctly.
  RC_ASSERT((parsetree->getText() == expression));
  std::cout << expression << std::endl;

  // Do analyzing.
  NodeAnalyzerStub analyzer{} ;
  AnalyzeData<Antlr4GenericParseTree> info =
    Analyzer<Antlr4GenericParseTree, NodeAnalyzerStub>::Analyze(
    *parsetree, analyzer);

  // Assert that only expr info reside in
  // AnalyzedData.
  RC_ASSERT(info.data.size() == 1);

  // Assert that num of expr node is
  // correct.
  int numOfExpr = 0;
  switch (numOfOperand) {
  case 1:
    numOfExpr = 1;
    break;
  case 2:
    numOfExpr = 3;
    break;
  default:
    numOfExpr = 3 + (numOfOperand - 2) * 2;
  }
  RC_ASSERT(info.data["EXPR"].size() == numOfExpr);
}

} // Analyzer
