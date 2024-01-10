#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "utility.h"
#include "generic_parsetree_antlr4_testlang_deepcopy.h"
#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"
#include "Concepts/n_ary_tree.h"


using TreeNode = antlr4::tree::ParseTree;
using TerminalNode = antlr4::tree::TerminalNodeImpl;

/* Checkt deep copy on TestLang ParseTrees */
namespace TestLang {

struct AntlrDeepCopy: public ::testing::Test {

  using Entry = TestLangParser::ProgContext* (TestLangParser::*)();
  void SetUp() final {
    const int N = *rc::gen::inRange(1, 100);
    Entry entry = &TestLangParser::prog;;
    std::string expr = Utility::testLangRandomExpr(N);

    env = Utility::Antlr4_GenParseTree<
      TestLangLexer, TestLangParser>(
        expr, entry);
  }

  std::unique_ptr<
    Utility::Antlr4ParseEnv<
      TestLangLexer, TestLangParser, Entry>> env;
};


RC_GTEST_FIXTURE_PROP(AntlrDeepCopy, Basic, ()) {
  TreeNode* copy = TestLang::clone(env->tree);

  bool equal = Concepts::NAryTree::equal<TreeNode, TreeNode>(
    *copy, *(env->tree),
    [](const TreeNode& l, const TreeNode& r) -> bool {
      // Make sure l and r not the same node but
      // structure of tree remain equal.
      return &l != &r;
    });
  RC_ASSERT(equal);
  RC_ASSERT(copy->getText() == env->tree->getText());

  return;
}

} // TestLang
