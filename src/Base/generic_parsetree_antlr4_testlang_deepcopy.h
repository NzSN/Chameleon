#ifndef GENERIC_PARSETREE_ANTLR4_TESTLANG_DEEPCOPY_H
#define GENERIC_PARSETREE_ANTLR4_TESTLANG_DEEPCOPY_H

#include  "generic_parsetree_antlr4_deepcopy.h"
#include "src/Misc/testLanguage/TestLangBaseListener.h"

namespace TestLang {

#define TEST_LANG_CONTEXTS(V)   \
  V(TestLangParser, Prog, Prog) \
  V(TestLangParser, Prog, Expr)

DEEPCOPY_IMPL(
  TestLangBaseListener,
  TEST_LANG_CONTEXTS);


} // TestLang


#endif /* GENERIC_PARSETREE_ANTLR4_TESTLANG_DEEPCOPY_H */
