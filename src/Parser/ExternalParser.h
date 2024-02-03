#ifndef EXTERNALPARSER_H
#define EXTERNALPARSER_H

#include <memory>
#include <list>
#include <map>

#include "Base/langs.h"
#include "utility.h"

#include "Base/generic_parsetree_antlr4.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

#include "parsers/wgsl/WGSLLexer.h"
#include "parsers/wgsl/WGSLParser.h"

namespace Parser {

template<Base::isLangType T>
struct ParseArg;

#define DEFINE_PARSE_ARG(__NSS, __LANG, __EXT, __L, __P, __E, __EM) \
  template<>                                                        \
  struct ParseArg<GET_LANG_TYPE(__LANG)> {                          \
    using Entry = __P::__E##Context * (__P::*)();                   \
    using Env = Utility::Antlr4ParseEnv<__L, __P, Entry>;           \
    using Lexer = __L;                                              \
    using Parser = __P;                                             \
    using Adapter = Base::Antlr4Node;                               \
    inline static Entry entry = &__P::__EM;                         \
  };
SUPPORTED_LANG_LIST(DEFINE_PARSE_ARG);

// Currently, only support Antlr4
template<Base::isLangType T>
class ExternalParser {
public:
  using Arg = ParseArg<T>;
  using Env = typename Arg::Env;
  using Lexer = typename Arg::Lexer;
  using Parser = typename Arg::Parser;

  [[nodiscard]] static antlr4::tree::ParseTree*
  parse(std::istream *s) {
    if (!s) { return nullptr; }

    std::unique_ptr<Env> env = Utility::Antlr4_GenParseTree<Lexer, Parser>(
        *s, Arg::entry);

    if (!env->tree) { return nullptr; }
    else {
      auto tree = env->tree;
      resources.push_back(std::move(env));
      auto iter = --resources.end();
      auto key = reinterpret_cast<uintptr_t>(tree);
      resourceTrack[key] = iter;

      return tree;
    }
  }

  void release(uintptr_t ptr) {
    if (!resourceTrack.contains(ptr)) {
      return;
    } else {
      auto iter = resourceTrack[ptr];
      resources.erase(iter);
      resourceTrack.erase(ptr);
    }
  }

  void releaseAll() {
    resources.clear();
    resourceTrack.clear();
  }

  size_t numOfResInTracked() const {
    return resourceTrack.size();
  }
private:
  using Resources = std::list<Utility::HeapResourceHolder>;
  inline static Resources resources{};
  inline static std::map<uintptr_t, Resources::const_iterator> resourceTrack{};
};

} // Parser

#endif /* EXTERNALPARSER_H */
