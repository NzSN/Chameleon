#ifndef GENERIC_PARSETREE_ANTLR4_TESTLANG_H
#define GENERIC_PARSETREE_ANTLR4_TESTLANG_H

namespace TestLang {

#define TEST_LANG_CONTEXTS(V)   \
  V(TestLang, TestLangParser, Prog, Prog) \
  V(TestLang, TestLangParser, Prog, Expr)

}

#endif /* GENERIC_PARSETREE_ANTLR4_TESTLANG_H */
