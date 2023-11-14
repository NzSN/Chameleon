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

template<>
struct ParserSelect<Base::GenericParseTree<Base::Antlr4Node>::TESTLANG> {
  typedef Parser<antlr4::tree::ParseTree*,
                 TestLangExt,
                 Base::Antlr4Node,
                 Base::GenericParseTree<Base::Antlr4Node>::TESTLANG> parser;
};

// Dynamic Parser Selecter
using ParserT = std::variant<
  ParserSelect<Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>::parser
  >;

std::optional<Base::GenericParseTreeT_DYNAMIC>
ParserRuntimeSelect(unsigned lang, std::istringstream& sentences);

} // Parser

#endif /* PARSER_INL_H */
