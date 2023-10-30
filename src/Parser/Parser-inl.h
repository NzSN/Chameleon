#ifndef PARSER_INL_H
#define PARSER_INL_H

#include "Parser.h"

#include "ExternalParser.h"
#include "Base/generic_parsetree_antlr4.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Parser {

template<typename ExtNode,
         ExtParser<ExtNode> P,
         NodeAdapter<ExtNode> A,
         int lang>
std::vector<A> Parser<ExtNode, P, A, lang>::adapters_ {};

// Static Parser Selecter
template<int lang> struct ParserSelect;

template<>
struct ParserSelect<Base::GenericParseTree<Base::Antlr4Node>::TESTLANG> {
  typedef Parser<antlr4::tree::ParseTree*,
                 TestLangExt,
                 Base::Antlr4Node,
                 2> parser;
};

// Dynamic Parser Selecter


} // Parser

#endif /* PARSER_INL_H */
