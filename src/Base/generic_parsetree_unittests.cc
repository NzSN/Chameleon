#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <typeinfo>
#include <plog/Log.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/TxtFormatter.h>
#include "generic_parsetree_inl.h"
#include "generic_parsetree_antlr4.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>
#include <memory>

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

#include "Parser/Parser-inl.h"

#include "utility.h"
#include "misc/Interval.h"
#include "Concepts/n_ary_tree.h"

namespace Base {

struct GenericParseTreeTest: public ::testing::Test {
  // Generate arbitary parsetree contains
  // only N nodes (include the root node).
GenericParseTree<int> genTreeWithN(const int n) {
    GenericParseTree<int> root{1};

    std::function<void(GenericParseTree<int>*,int)>
      genSubTreeWithN = [&](GenericParseTree<int>* root, int nsubs) {
        while (nsubs > 0) {
          // Create directly child
          GenericParseTree<int>& child = root->addChild(
            std::make_unique<GenericParseTree<int>>(1));
          nsubs -= 1;
          if (nsubs == 0) {
            return;
          }

          // Create a subtree with M nodes,
          // M is in range [0, remain]
          int m = *rc::gen::inRange(0, nsubs);

          genSubTreeWithN(&child, m);
          nsubs -= m;
        }
    };

    genSubTreeWithN(&root, n - 1);
    return root;
  }

  int traverseN(GenericParseTree<int>& tree) {
    const auto& counting =
      [&](GenericParseTree<int>& tree) -> bool {
        ++node_counter;
        return true;
    };
    tree.traverse(counting);

    return node_counter;
  }

  GenericParseTree<int>& getNodeRandomly(GenericParseTree<int>& tree) {
    int counter = *rc::gen::inRange(100, 1000);

    const auto& selectNode =
      [&](GenericParseTree<int>& tree) -> bool {
        --counter;
        if (counter == 0) {
          return true;
        }
        return false;
      };

    GenericParseTree<int>* node = NULL;
    while (!node) {
      node = tree.select(selectNode);
    }
    return *node;
  }

  int node_counter = 0;
  std::vector<void*> nodes;
};

RC_GTEST_FIXTURE_PROP(GenericParseTreeTest, Basic, ()) {
  GenericParseTree<int> root{1};
  auto& child = root.addChild(
    std::make_unique<GenericParseTree<int>>(2));
  child.addChild(std::make_unique<GenericParseTree<int>>(3));

  traverseN(root);
  RC_ASSERT(node_counter == 3);
}

RC_GTEST_FIXTURE_PROP(GenericParseTreeTest, Traverse, ()) {
  const int N = *rc::gen::inRange(0, 100);
  if (N == 0) return;

  GenericParseTree<int> root = genTreeWithN(N);
  traverseN(root);
  RC_ASSERT(node_counter == N);
}

RC_GTEST_FIXTURE_PROP(GenericParseTreeTest, EqReflexivity, ()) {
  // Check basic case
  GenericParseTree<int> terminal{1};
  RC_ASSERT(terminal == terminal);

  // Assume ParseTree with N node satisfy
  // reflexivity.
  std::optional<GenericParseTree<int>> root =
    genTreeWithN(*rc::gen::inRange(1, 100));
  RC_ASSERT(root.value() == root.value());

  // Check N + 1 case
  // Select a place to add
  // a node randomly.
  GenericParseTree<int>& node = getNodeRandomly(root.value());
  node.addChild(std::make_unique<GenericParseTree<int>>(1));
  RC_ASSERT(root.value() == root.value());
}

/////////////////////////////////////////////////////////////////////////////
//                           Antlr4GPT Unittests                           //
/////////////////////////////////////////////////////////////////////////////
struct Antlr4GPTTests: public ::testing::Test {
  using Entry = TestLangParser::ProgContext* (TestLangParser::*)();
  void SetUp() final {
    plog::init<plog::TxtFormatterUtcTime>(plog::debug, plog::streamStdOut);
    Entry entry;
    entry = &TestLangParser::prog;

    std::function<std::string(unsigned)>
    randomSentences = [&](unsigned numOfOperands) -> std::string {
      constexpr int NumOfOperators = 5;
      static std::string operators[] ={
        "+", "-", "*", "/", "\n"
      };

      if (numOfOperands == 0) return {};


      std::string sentence = std::to_string(*rc::gen::inRange(0, 100));
      --numOfOperands;
      if (numOfOperands == 0) {
        return sentence;
      } else {
        sentence += operators[*rc::gen::inRange(0, NumOfOperators)];
        sentence += randomSentences(numOfOperands);
      }

      return sentence+"\n";
    };

    // Generate ParseTree randomly
    env = Utility::Antlr4_GenParseTree<
      TestLangLexer, TestLangParser>(
        randomSentences(*rc::gen::inRange(1, 10)), entry);
  }

  std::unique_ptr<
    Utility::Antlr4ParseEnv<
      TestLangLexer, TestLangParser, Entry>> env;
};

// foreach s in TestLang, correspond antlr4::tree::ParseTree
// and Antlr4Node is isomorphic.
RC_GTEST_FIXTURE_PROP(Antlr4GPTTests, MapToAntlr4Node, ()) {
  RC_ASSERT_FALSE(env->tree == nullptr);

  Antlr4Node nodes{
    GenericParseTree<Antlr4Node>::TESTLANG,
    env->tree };

  // Check equality between generated Antlr4Node
  // and correspond antlr4::tree::ParseTree.
  auto isEqual =
    Concepts::NAryTree::equal<Antlr4Node, antlr4::tree::ParseTree>
    (nodes, *env->tree,
     [](const Antlr4Node& l, const antlr4::tree::ParseTree& r) {
       return const_cast<Antlr4Node&>(l).tree()->getText() ==
         const_cast<antlr4::tree::ParseTree&>(r).getText();
    });

  RC_ASSERT(isEqual);
}

RC_GTEST_FIXTURE_PROP(Antlr4GPTTests, Clone, ()) {
  RC_ASSERT_FALSE(env->tree == nullptr);

  Antlr4Node nodes{
    GenericParseTree<Antlr4Node>::TESTLANG,
    env->tree };

  Antlr4Node::Node copy = nodes.clone();

  // Check equality of two nodes
  RC_ASSERT(nodes.tree()->getText() ==
            copy->tree() ->getText());

  // Make sure their two distinct trees.
  bool isEqual = Concepts::NAryTree::equal<Antlr4Node, Antlr4Node>(
    nodes, *copy,
    [](const Antlr4Node& lhs, const Antlr4Node& rhs) -> bool {
      return const_cast<Antlr4Node&>(lhs).tree() ==
        const_cast<Antlr4Node&>(rhs).tree();
    });
  RC_ASSERT(!isEqual);
}

RC_GTEST_FIXTURE_PROP(Antlr4GPTTests, MapToGenericParseTree, ()) {
  RC_ASSERT_FALSE(env->tree == nullptr);

  // Antlr4Node works as adapter
  Antlr4Node nodes{
    GenericParseTree<Antlr4Node>::TESTLANG,
    env->tree };

  GenericParseTree<Antlr4Node> gpt =
    GenericParseTree<Antlr4Node>::mapping(nodes);

  using GPT = GenericParseTree<Antlr4Node>;
  auto isEqual =
    Concepts::NAryTree::equal<GPT, Antlr4Node>(
      gpt, nodes, [](const GPT& l, const Antlr4Node& r) {
        return const_cast<GPT&>(l).getText() ==
          const_cast<Antlr4Node&>(r).tree()->getText();
      });
  RC_ASSERT(isEqual);
}

RC_GTEST_PROP(GenericParseTreeTest_NAry, Clone, ()) {
  std::istringstream codes{"a+1+2"};
  GenericParseTree<Antlr4Node> t =
      Parser::ParserSelect<GenericParseTree<Antlr4Node>::TESTLANG>
      ::parser::parse<GenericParseTree<Antlr4Node>>(&codes);

  Antlr4Node::Node copy_meta = t.getMeta().clone();
  GenericParseTree<Antlr4Node> copy =
    GenericParseTree<Antlr4Node>::mapping(
      *copy_meta);
  RC_ASSERT(copy.getText() == t.getText());
}

RC_GTEST_PROP(GenericParseTreeTest_NAry, SetNode, ()) {
  std::istringstream codes{"a+1+2"};
  GenericParseTree<Antlr4Node> t =
    Parser::ParserSelect<GenericParseTree<Antlr4Node>::TESTLANG>
    ::parser::parse<GenericParseTree<Antlr4Node>>(&codes);


  auto v = Concepts::NAryTree::search<GenericParseTree<Antlr4Node>>(
    t,
    [](GenericParseTree<Antlr4Node>& node) -> bool {
      return const_cast<Antlr4Node&>(node.getMeta())
        .tree()->getTreeType() == antlr4::tree::ParseTreeType::TERMINAL
        && node.getText() == "a";
    });

  auto v2 = Concepts::NAryTree::search<GenericParseTree<Antlr4Node>>(
    t,
    [](GenericParseTree<Antlr4Node>& node) -> bool {
      return const_cast<Antlr4Node&>(node.getMeta())
        .tree()->getTreeType() == antlr4::tree::ParseTreeType::TERMINAL
        && node.getText() == "1";
    });

  auto v3 = Concepts::NAryTree::search<GenericParseTree<Antlr4Node>>(
    t,
    [](GenericParseTree<Antlr4Node>& node) -> bool {
      return const_cast<Antlr4Node&>(node.getMeta())
        .tree()->getTreeType() == antlr4::tree::ParseTreeType::TERMINAL
        && node.getText() == "2";
    });

  RC_ASSERT(v.size() == 1);
  RC_ASSERT(v2.size() == 1);
  RC_ASSERT(v3.size() == 1);

  v2[0]->getMeta().clone();

  // Replace node 'a' with node '1'
  // by setNode.
  // RC_ASSERT(v[0]->setNode(
  //             const_cast<Antlr4Node&>(*(v2[0]->getMeta().clone()))));
  // RC_ASSERT(t.getText() == "1+1+2");
  // RC_ASSERT(v[0]->setNode(
  //             const_cast<Antlr4Node&>(*(v3[0]->getMeta()).clone())));
  // RC_ASSERT(t.getText() == "2+1+2");
}


} // Base
