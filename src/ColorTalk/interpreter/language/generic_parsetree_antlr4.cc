#include <plog/Log.h>
#include "generic_parsetree.h"
#include "parsers/ts/TypeScriptLexer.h"
#include "parsers/ts/TypeScriptParser.h"
#include "parsers/ts/TypeScriptParserBaseListener.h"

namespace Rules::Interpreter::Language {

using Antlr4Tree = antlr4::tree::ParseTree;
using Antlr4GPT = GenericParseTree<const std::type_info&>;

Antlr4GPT fromAntlr4_TS(Antlr4Tree& tree);
Antlr4GPT fromAntlr4_CPP(Antlr4Tree& tree);

template<>
Antlr4GPT Antlr4GPT::fromAntlr4(
  Antlr4Tree& tree, SUPPORTED_LANGUAGE lang) {
  // Type of root node should be replace soon.
  GenericParseTree root{typeid(void)};

  switch (lang) {
  case CPP:
    PLOG_FATAL << "Parsing CPP by Antlr4 is not supported";
    exit(1);
    break;
  case TYPESCRIPT:
    return fromAntlr4_TS(tree);
    break;
  default:
    // Invalid lang enum
    PLOG_FATAL << "Invalid language";
    exit(1);
  }

  return root;
}

Antlr4GPT fromAntlr4_TS(Antlr4Tree& tree) {
  /* Need to implement */
  PLOG_FATAL << "Parsing typescript is not implement";
  exit(1);
}


} // Rules::Interpreter::Language
