#include <variant>
#include "generic_parsetree_antlr4.h"

namespace Base {

using GptGeneric =
  std::variant<
  // Antlr4 Parsers
  GenericParseTree<Antlr4Node>
  >;

using GptSupportLang =
  GenericParseTree<int>::SUPPORTED_LANGUAGE;

} // Base
