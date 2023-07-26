#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <typeinfo>
#include "generic_parsetree.h"

namespace Rules::Interpreter::Language {

struct GenericParseTreeTest: public ::testing::Test {
  // Generate arbitary parsetree contains
  // only N nodes (include the root node).
  GenericParseTree genTreeWithN(const int n) {
    GenericParseTree root{typeid(int)};

    std::function<void(GenericParseTree*,int)>
      genSubTreeWithN = [&](GenericParseTree* root, int nsubs) {
        while (nsubs > 0) {
          // Create directly child
          GenericParseTree& child = root->addChild(typeid(int));
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
  GenericParseTree terminal{typeid(int)};
  RC_ASSERT(terminal == terminal);

  // Assume ParseTree with N node satisfy
  // reflexivity.
  GenericParseTree root = genTreeWithN(10);
  RC_ASSERT(root == root);

  // Check N + 1 case
  root.addChild(typeid(char));
  RC_ASSERT(root == root);
}

} // Rules::Interpreter::Language
