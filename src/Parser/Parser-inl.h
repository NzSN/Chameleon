#ifndef PARSER_INL_H
#define PARSER_INL_H

#include "Parser.h"
#include <variant>
#include <sstream>
#include <memory>

#include "ExternalParser.h"
#include "Base/generic_parsetree_concrete.h"
#include "Misc/testLanguage/TestLangParser.h"

#include "Base/langs.h"

namespace Parser {

template<Base::isLangType L>
std::vector<std::unique_ptr<typename ParseArg<L>::Adapter>>
Parser<L>::adapters_ {};

// Static Parser Selecter
template<Base::isLangType L> struct ParserSelect;

#define PARSER_SELECT_IMPL(                                       \
  NSS, LANG_ENUM, EXT_PARSER, LEXER, PARSER, ENTRY, ENTRY_MEMBER) \
  template<>                                                      \
  struct ParserSelect<GET_LANG_TYPE(LANG_ENUM)> {      \
  typedef Parser<GET_LANG_TYPE(LANG_ENUM)> parser;                  \
};

SUPPORTED_LANG_LIST(PARSER_SELECT_IMPL);

// Dynamic Parser Selecter
using ParserT = std::variant<
  ParserSelect<GET_LANG_TYPE(TESTLANG)>::parser
  >;

std::optional<Base::ParseTreeT_DYNAMIC>
ParserRuntimeSelect(unsigned lang, std::istringstream& sentences);

} // Parser

#endif /* PARSER_INL_H */
