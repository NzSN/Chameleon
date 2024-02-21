#ifndef LANGSINFO_H
#define LANGSINFO_H

#include "langs.h"
#include "utility.h"

#include "Base/generic_parsetree_antlr4.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

#include "parsers/wgsl/WGSLLexer.h"
#include "parsers/wgsl/WGSLParser.h"


namespace Chameleon::Base {

template<Base::isLangType T>
struct LangArg;

#define DEFINE_PARSE_ARG(__NSS, __LANG, __EXT, __L, __P, __E, __EM) \
  template<>                                                        \
  struct LangArg<GET_LANG_TYPE(__LANG)> {                          \
    using Entry = __P::__E##Context * (__P::*)();                   \
    using Env = Utility::Antlr4ParseEnv<__L, __P, Entry>;           \
    using Lexer = __L;                                              \
    using Parser = __P;                                             \
    using Adapter = Base::Antlr4Node;                               \
    inline static Base::SUPPORTED_LANGUAGE langEnum =                   \
      Base::SUPPORTED_LANGUAGE::__LANG;                             \
    inline static Entry entry = &__P::__EM;                         \
    inline static std::string name = #__LANG;                                \
  };
SUPPORTED_LANG_LIST(DEFINE_PARSE_ARG);


} // Base


#endif /* LANGSINFO_H */
