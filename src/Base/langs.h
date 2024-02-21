#ifndef LANGS_H
#define LANGS_H

#include <type_traits>

namespace Chameleon {
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

struct LangTypeBase {};

template<typename T>
concept isLangType = std::is_base_of_v<LangTypeBase, T>;

#define LANG_TYPE_NAME(L) __##L##__T_
#define NEW_LANG_TYPE(L) \
  struct LANG_TYPE_NAME(L): public LangTypeBase { \
    inline static auto typeEnum = L;              \
  }
#define GET_LANG_TYPE(L) Chameleon::Base::LANG_TYPE_NAME(L)

// FIELD DESCRIPTIONS
// | Namespace | LANG ENUM (LANG TYPE NAME) | EXTERNAL PARSER | LEXER | PARSER | ENTRY | ENTRY_MEMBER |
#define SUPPORTED_LANG_LIST(V)                                          \
  V(TestLang , TESTLANG, TestLangExt, TestLangLexer, TestLangParser, Prog, prog) \
  V(WGSL     , WGSL, WGSLLangExt, WGSLLexer, WGSLParser, Translation_unit, translation_unit)

//
#define DEFINE_LANG_TYPE(NSS, LANG, EXT, L, P, E, EM) \
  NEW_LANG_TYPE(LANG);
SUPPORTED_LANG_LIST(DEFINE_LANG_TYPE)
#undef LANG_TYPE_IMPL

} // Base
} // Chameleon

#endif /* LANGS_H */
