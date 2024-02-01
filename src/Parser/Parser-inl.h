#ifndef PARSER_INL_H
#define PARSER_INL_H

#include "Parser.h"
#include <variant>
#include <sstream>
#include <memory>

#include "ExternalParser.h"
#include "Base/generic_parsetree_concrete.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Parser {

template<typename ExtNode,
         ExtParser<ExtNode> P,
         NodeAdapter<ExtNode> A,
         int lang>
std::vector<std::unique_ptr<A>> Parser<ExtNode, P, A, lang>::adapters_ {};

// Static Parser Selecter
template<int lang> struct ParserSelect;

#define PARSER_SELECT_IMPL(                                       \
  NSS, LANG_ENUM, EXT_PARSER, LEXER, PARSER, ENTRY, ENTRY_MEMBER) \
  template<>                                                      \
  struct ParserSelect<Base::SUPPORTED_LANGUAGE::LANG_ENUM> {      \
  typedef Parser<antlr4::tree::ParseTree*,                        \
    EXT_PARSER,                                                   \
    Base::Antlr4Node,                                             \
    Base::SUPPORTED_LANGUAGE::LANG_ENUM> parser;                  \
};

SUPPORTED_LANG_LIST(PARSER_SELECT_IMPL);

// Dynamic Parser Selecter
using ParserT = std::variant<
  ParserSelect<Base::ParseTree<Base::Antlr4Node>::TESTLANG>::parser
  >;

std::optional<Base::ParseTreeT_DYNAMIC>
ParserRuntimeSelect(unsigned lang, std::istringstream& sentences);

} // Parser

#endif /* PARSER_INL_H */
