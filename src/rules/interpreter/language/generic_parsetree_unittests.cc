#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <typeinfo>
#include <plog/Log.h>
#include "generic_parsetree.h"
#include <iostream>

namespace Rules::Interpreter::Language {

struct GenericParseTreeTest: public ::testing::Test {
  // Generate arbitary parsetree contains
  // only N nodes (include the root node).
  GenericParseTree<int> genTreeWithN(const int n) {
    GenericParseTree<int> root{1};

    std::function<void(GenericParseTree<int>*,int)>
      genSubTreeWithN = [&](GenericParseTree<int>* root, int nsubs) {
        while (nsubs > 0) {
          // Create directly child
          GenericParseTree<int>& child = root->addChild(1);
          nsubs -= 1;
          if (nsubs == 0) { return; }

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
};

RC_GTEST_FIXTURE_PROP(GenericParseTreeTest, EqReflexivity, ()) {
  // Check basic case
  GenericParseTree<int> terminal{1};
  RC_ASSERT(terminal == terminal);

  // Assume ParseTree with N node satisfy
  // reflexivity.
  GenericParseTree<int> root = genTreeWithN(10);
  RC_ASSERT(root == root);

  // Check N + 1 case
  root.addChild(2);
  RC_ASSERT(root == root);
}

} // Rules::Interpreter::Language
