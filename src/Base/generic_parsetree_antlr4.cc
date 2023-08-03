#include <exception>
#include "tree/ParseTreeType.h"
#include "generic_parsetree_antlr4.h"

namespace Base {

Antlr4Node::Antlr4Node(int lang, antlr4::tree::ParseTree* tree):
  lang_{lang}, tree_{tree} {

  if (!tree) {
    throw std::runtime_error(
      "No antlr4 parsetree found (nullpointer)");
  }

  // Construct subtrees
  for (auto c: tree->children) {
    children_.emplace_back(lang, c);
  }
}

bool Antlr4Node::operator==(const Antlr4Node& node) const {
  if (this->tree_->getTreeType() !=
      node.tree_->getTreeType()) {

    return false;
  }

  if (this->tree_->getTreeType() ==
      antlr4::tree::ParseTreeType::TERMINAL) {

    // Check equality of contents of terminal
    if (this->tree_->getText() !=
        node.tree_->getText()) {
      return false;
    }
  }

  return true;
}

SrcRange Antlr4Node::sourceRange() const {
  antlr4::ParserRuleContext* rctx =
    static_cast<antlr4::ParserRuleContext*>(tree_);

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

} // Base
