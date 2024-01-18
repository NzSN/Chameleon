#ifndef GENERIC_PARSETREE_ANTLR4_TESTLANG_H
#define GENERIC_PARSETREE_ANTLR4_TESTLANG_H

namespace Testlang {

#define TEST_LANG_CONTEXTS(V)   \
  V(TestLangParser, Prog, Prog) \
  V(TestLangParser, Prog, Expr)

}

#endif /* GENERIC_PARSETREE_ANTLR4_TESTLANG_H */
