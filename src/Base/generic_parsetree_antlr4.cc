#include "tree/ParseTreeType.h"
#include "generic_parsetree_antlr4.h"

namespace Rules::Interpreter::Language {

bool Antlr4Node::operator==(const Antlr4Node& node) const {
  if (this->tree->getTreeType() !=
      node.tree->getTreeType()) {

    return false;
  }

  if (this->tree->getTreeType() ==
      antlr4::tree::ParseTreeType::TERMINAL) {

    // Check equality of contents of terminal
    if (this->tree->getText() !=
        node.tree->getText()) {
      return false;
    }
  }

  return true;
}

SrcRange Antlr4Node::sourceRange() const {
  antlr4::ParserRuleContext* rctx =
    static_cast<antlr4::ParserRuleContext*>(tree);

  return {
    // Get position of first token.
    { rctx->getStart()->getLine(),
      rctx->getStart()->getCharPositionInLine(),
    },
    // Get position of stop token.
    {
      rctx->getStop()->getLine(),
      rctx->getStop()->getCharPositionInLine(),
    }};
}

} // Rules::Interpreter::Language
