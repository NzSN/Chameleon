#include <algorithm>
#include <exception>
#include "tree/ParseTreeType.h"
#include "generic_parsetree_antlr4.h"

namespace Base {

namespace {

Antlr4Node cloneTestLang(const Antlr4Node& tree) {
  Antlr4Node copy = Concepts::NAryTree::transform<Antlr4Node>(
    tree, [](const Antlr4Node& node) -> Antlr4Node {

    });
}

}

// Deep copy
Antlr4Node Antlr4Node::clone() {
  switch (lang_) {
  case GenericParseTree<Antlr4Node>::TESTLANG:
    return cloneTestLang(*this);
  default:
    throw std::runtime_error("Failed to clone Antlr4Node");
  }
}


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

  for (auto& c: children_) {
    c.parent = this;
  }
}

// Shallow copy
Antlr4Node::Antlr4Node(const Antlr4Node& other):
  lang_{other.lang_}, tree_{other.tree_},
  children_{other.children_} {}

// Shallow copy
Antlr4Node& Antlr4Node::operator=(const Antlr4Node& other) {
  lang_ = other.lang_;
  tree_ = other.tree_;
  children_ = other.children_;

  return *this;
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

bool Antlr4Node::setNode(const Antlr4Node& other) {
  if (tree_ == nullptr || other.tree_ == nullptr) {
    return false;
  }

  antlr4::tree::ParseTree* tree = tree_;
  std::vector<antlr4::tree::ParseTree*>&
    siblings = tree_->parent->children;

  std::vector<antlr4::tree::ParseTree*> siblings_new(siblings.size());

  std::transform(siblings.cbegin(), siblings.cend(),
                 siblings.begin(),
                 [tree, &other](antlr4::tree::ParseTree* t) -> antlr4::tree::ParseTree* {
                   std::cout << "T" << t->getText() << std::endl;
                   if (tree == t) {
                     std::cout << "M" << t->getText() << std::endl;
                     return other.tree_;
                   }

                   return t;
                 });
  tree_ = other.tree_;
  return true;
}

void Antlr4Node::appendChild(Antlr4Node& node) {
  children_.push_back(node);
}

void Antlr4Node::appendChild(Antlr4Node&& node) {
  children_.push_back(node);
}

} // Base
