#include <memory>
#include "Parser-inl.h"

namespace Parser {

std::optional<Base::GenericParseTreeT_DYNAMIC>
ParserRuntimeSelect(unsigned lang, std::istringstream& sentences) {
  switch (lang) {
  case Base::GenericParseTree<Base::Antlr4Node>::TESTLANG: {

    std::unique_ptr<Base::GenericParseTree<Base::Antlr4Node>>
      t = ParserSelect<Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
      ::parser::parse<
        Base::GenericParseTree<Base::Antlr4Node>,
        Base::DYNAMIC>(&sentences);

    return std::move(t);
  }
  default:
    return std::nullopt;
  };
}

} // Parser
