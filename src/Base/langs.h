#ifndef LANGS_H
#define LANGS_H

#include <concepts>

namespace Base {

enum SUPPORTED_LANGUAGE {
  MINIMUM_LANG_INDEX = 0,
  TYPESCRIPT = 0,
  CPP = 1,

  // Testing purposes
  TESTLANG = 2,
  WGSL = 3,
  NUM_OF_LANG_SUPPORTED,
};

template<SUPPORTED_LANGUAGE lang>
concept isTestLang = lang == SUPPORTED_LANGUAGE::TESTLANG;

template<SUPPORTED_LANGUAGE lang>
concept isWGSL = lang == SUPPORTED_LANGUAGE::WGSL;


// FIELD DESCRIPTIONS
// | Namespace | LANG ENUM | EXTERNAL PARSER | LEXER | PARSER | ENTRY | ENTRY_MEMBER |
#define SUPPORTED_LANG_LIST(V)                                          \
  V(TestLang , TESTLANG, TestLangExt, TestLangLexer, TestLangParser, Prog, prog) \
  V(WGSL     , WGSL, WGSLLangExt, WGSLLexer, WGSLParser, Translation_unit, translation_unit)

} // Base

#endif /* LANGS_H */
