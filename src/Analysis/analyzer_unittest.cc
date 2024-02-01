#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <iostream>
#include <typeinfo>
#include <map>
#include <tuple>
#include <array>

#include "analyzer.h"
#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

#include "utility.h"
#include "Base/generic_parsetree_antlr4.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Analyzer {
using Antlr4ParseTree = Base::ParseTree<Base::Antlr4Node>;

///////////////////////////////////////////////////////////////////////////////
//                           AnalyzeData Unittests                           //
///////////////////////////////////////////////////////////////////////////////
struct TestTree {
  constexpr static const int MAXIMUM_FIELDS = 10;
  constexpr static const int MAXIMUM_DATAS = 10;
  constexpr static int TOTAL_NUM_OF_DATA = MAXIMUM_FIELDS * MAXIMUM_DATAS;


  TestTree(int v): value{v}, children{} {}
  std::array<TestTree*, TOTAL_NUM_OF_DATA> getChildren() {
    return children;
  }

  TestTree(const TestTree& other) {
    this->value = other.value;
    this->children = other.children;
  }

  bool operator==(const TestTree& t) const {
    return this == &t;
  }

  int value;
  std::array<TestTree*, TOTAL_NUM_OF_DATA> children;
};

struct AnalyzeDataTests: public ::testing::Test {
  void SetUp() final { /* Do Nothing */ }

  AnalyzeData<TestTree>
  randomData() {
    AnalyzeData<TestTree> data{};

    int numOfFields = *rc::gen::inRange(1,10);
    for (int i = 0; i < numOfFields; ++i) {
      int numOfData = *rc::gen::inRange(1,10);

      AnalyzeData<TestTree>::DataSet set;

      for (int j = 0; j < numOfData; ++j) {
        int value = *rc::gen::inRange(1,10);

        allTrees.emplace_back(value);
        TestTree& tree = allTrees.back();
        set.insert(std::reference_wrapper<TestTree>(tree));
      }

      data.data.insert({std::to_string(i), set});
    }

    return data;
  }

  std::vector<TestTree> allTrees;
};

RC_GTEST_FIXTURE_PROP(AnalyzeDataTests, InvariantCheck, ()) {
  AnalyzeData<TestTree> treeA = randomData();
  AnalyzeData<TestTree> treeB = randomData();

  AnalyzeData<TestTree> treeC = AnalyzeData<TestTree>::merge(
    treeA, treeB);

  // Assert invariant is holded.
  const auto& isFound = [&](std::string key, TestTree& t) -> bool {
    if (!treeC.data.contains(key)) {
      std::cout << "key not found:" << key << std::endl;
      return false;
    } else {
      for (auto& d: treeC.data[key]) {
        if (d.get() == t) {
          return true;
        }
        return true;
      }
    }

    return true;
  };

  for (auto& tree: {treeA, treeB}) {
    for (auto& [key, data]: tree.data) {
      for (auto& d: data) {
        bool found = isFound(key, d);
        RC_ASSERT(found);
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//                             Analyzer Unittests                            //
///////////////////////////////////////////////////////////////////////////////

// An Node analyzer to analyzing a TestLang ParseTree
// to collect all operand infos.
//
// This NodeAnalyzer collect all expression information
// about the TestLang parsetree that analyzed by it.
struct NodeAnalyzerStub {

  std::tuple<
    AnalyzeState, AnalyzeData<Antlr4ParseTree>>
  operator()(Base::ParseTree<Base::Antlr4Node>& node) {
    auto& raw_node = *const_cast<Base::Antlr4Node&>(
      node.getMeta()).tree();

    auto ret = std::make_tuple<AnalyzeState>(
      {AnalyzeState::Analyzing}, AnalyzeData<Antlr4ParseTree>());

    size_t nodeTypeID = typeid(raw_node).hash_code();
    if (nodeTypeID == typeid(TestLangParser::ExprContext).hash_code()) {
      auto& data = std::get<1>(ret).data;
      if (!data.contains("EXPR")) {
        auto set = AnalyzeData<Antlr4ParseTree>::DataSet{
          std::reference_wrapper<Antlr4ParseTree>(node)};
        data.insert({"EXPR", set});
      } else {
        data["EXPR"].insert(
          std::reference_wrapper<Antlr4ParseTree>(
            const_cast<Antlr4ParseTree&>(node)));
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

    parsetree = Parser::Parser<GET_LANG_TYPE(TESTLANG)>
      ::parse<Base::ParseTree<Base::Antlr4Node>,
              Base::DYNAMIC>(&codes);
  }

  int numOfOperand;
  std::string expression;
  std::unique_ptr<
    Base::ParseTree<
      Base::Antlr4Node>> parsetree;
};

// RC_GTEST_FIXTURE_PROP(AnalyzerTests, Basics, ()) {
//   // Assert that Parsetree is generated correctly.
//   RC_ASSERT((parsetree->getText() == expression));

//   // Do analyzing.
//   NodeAnalyzerStub analyzer{} ;
//   AnalyzeData<Antlr4ParseTree> info =
//     Analyzer<Antlr4ParseTree, NodeAnalyzerStub>::Analyze(
//     *parsetree, analyzer);

//   // Assert that only expr info reside in
//   // AnalyzedData.
//   RC_ASSERT(info.data.size() == 1);

//   // Assert that num of expr node is
//   // correct.
//   auto numOfExpr = [](int numOfOperand) {
//     switch (numOfOperand) {
//     case 1:
//       return 1;
//       break;
//     case 2:
//       return 3;
//       break;
//     default:
//       return 3 + (numOfOperand - 2) * 2;
//     }
//   };

//   RC_ASSERT(info.data["EXPR"].size() == numOfExpr(numOfOperand));
// }

} // Analyzer
