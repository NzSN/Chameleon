#ifndef GENERIC_PARSETREE_ANTLR4_TESTLANG_DEEPCOPY_H
#define GENERIC_PARSETREE_ANTLR4_TESTLANG_DEEPCOPY_H

#include  "generic_parsetree_antlr4_deepcopy.h"
#include "src/Misc/testLanguage/TestLangBaseListener.h"

namespace TestLang {

using TreeNode = Antlr4DeepCopy::TreeNode;
using CopyRealm = Antlr4DeepCopy::CopyRealm<TreeNode*>;

#define COPY_ANTLR4_TESTLANG_NODE(CTX) \
  COPY_ANTLR4_NON_TERMINAL(TestLangParser, Prog, CTX)
#define TEST_LANG_CONTEXTS(V) \
  V(Prog) \
  V(Expr)

struct TestLangDeepCopyListener: public TestLangBaseListener {
  TEST_LANG_CONTEXTS(COPY_ANTLR4_TESTLANG_NODE);
  COPY_ANTLR4_TERMINAL();
};

inline TreeNode* clone(TreeNode* tree) {
  TestLangDeepCopyListener listener;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  std::optional<TreeNode*> copyRoot =  CopyRealm(tree)();
  return copyRoot.has_value() ?
    copyRoot.value() : nullptr;
}

} // TestLang



#endif /* GENERIC_PARSETREE_ANTLR4_TESTLANG_DEEPCOPY_H */
