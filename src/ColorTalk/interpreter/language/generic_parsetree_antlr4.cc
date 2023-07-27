#include <plog/Log.h>
#include "generic_parsetree_antlr4.h"
#include "parsers/ts/TypeScriptLexer.h"
#include "parsers/ts/TypeScriptParser.h"
#include "parsers/ts/TypeScriptParserBaseListener.h"

namespace Rules::Interpreter::Language {

using Antlr4Tree = antlr4::tree::ParseTree;

/////////////////////////////////////////////////////////////////////////////
//                                 Mapping                                  //
/////////////////////////////////////////////////////////////////////////////
Antlr4GPT fromAntlr4_TS(Antlr4Node& tree);
Antlr4GPT fromAntlr4_CPP(Antlr4Node& tree);

template<>
template<>
Antlr4GPT Antlr4GPT::mapping(Antlr4Node tree) {
  switch (tree.lang) {
  case Antlr4GPT::CPP:
    PLOG_FATAL << "Parsing CPP by Antlr4 is not supported";
    exit(1);
    break;
  case Antlr4GPT::TYPESCRIPT:
    return fromAntlr4_TS(tree);
    break;
  default:
    // Invalid lang enum
    PLOG_FATAL << "Invalid language";
    exit(1);
  }
}

Antlr4GPT fromAntlr4_TS(Antlr4Node& tree) {
  /* Need to implement */
  PLOG_FATAL << "Parsing typescript is not implement";
  exit(1);
}

} // Rules::Interpreter::Language
