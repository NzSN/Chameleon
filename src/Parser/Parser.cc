#include "Parser-inl.h"

namespace Parser {

std::optional<Base::GenericParseTreeT>
ParserRuntimeSelect(unsigned lang, std::istringstream& sentences) {
  switch (lang) {
  case Base::GenericParseTree<Base::Antlr4Node>::TESTLANG:
    return ParserSelect<Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
      ::parser::parse<Base::GenericParseTree<Base::Antlr4Node>>(&sentences);
  default:
    return std::nullopt;
  };
}

} // Parser
