#ifndef EXTERNALPARSER_H
#define EXTERNALPARSER_H

#include <string>
#include <vector>
#include <memory>

#include "Base/langs.h"
#include "utility.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

#include "parsers/wgsl/WGSLLexer.h"
#include "parsers/wgsl/WGSLParser.h"

namespace Parser {

#define EXTERNAL_PARSER_WRAPPING(                              \
  NSS, LANG_ENUM, EXT_PARSER, LEXER,                           \
  PARSER, ENTRY, ENTRY_MEMBER)                                 \
                                                               \
  struct EXT_PARSER {                                          \
    using Entry = PARSER::ENTRY##Context * (PARSER::*)();      \
    using Env = Utility::Antlr4ParseEnv<LEXER, PARSER, Entry>; \
    using EnvPtr = std::unique_ptr<Env>;                       \
                                                               \
    static antlr4::tree::ParseTree*                            \
    parse(std::istream *s) {                                   \
      Entry entry = &PARSER::ENTRY_MEMBER;                     \
                                                               \
      std::string expression;                                  \
      *s >> expression;                                        \
                                                               \
      std::unique_ptr<Env> env =                               \
        Utility::Antlr4_GenParseTree<LEXER, PARSER>(           \
          expression, entry);                                  \
      tree = env->tree;                                        \
      envs.push_back(std::move(env));                          \
      return tree;                                             \
    }                                                          \
    inline static antlr4::tree::ParseTree* tree{nullptr};      \
    inline static std::vector<EnvPtr> envs{};                  \
  };

SUPPORTED_LANG_LIST(EXTERNAL_PARSER_WRAPPING);

} // Parser

#endif /* EXTERNALPARSER_H */
