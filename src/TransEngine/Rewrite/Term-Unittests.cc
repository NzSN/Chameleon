#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <iostream>

#include "Term.h"
#include "Base/generic_parsetree_inl.h"

namespace TransEngine {
namespace Rewrite {

struct TermTests: public ::testing::Test {
  TermTests(): tree{1} {}

  Base::GenericParseTree<int> tree;
};

TEST_F(TermTests, Assignable) {
  Term<int> t(tree);
  Term<int> t2{t};

  RC_ASSERT(t.tree.get() == t2.tree.get());
}

TEST_F(TermTests, Comparable) {
  Term<int> t{tree};
  Term<int> t2{t};

  RC_ASSERT(t == t2);
  RC_ASSERT((t == Term<int>{tree}));
}

} // Rewrite
} // TransEngine
