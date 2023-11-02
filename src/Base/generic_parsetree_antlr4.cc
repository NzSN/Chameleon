#include <algorithm>
#include <exception>
#include <typeinfo>
#include <stdexcept>

#include "tree/ParseTreeType.h"
#include "generic_parsetree_antlr4.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Base {

namespace {

using Concepts::NAryTree::TransformInfo;

TestLangParser::ProgContext*
cloneProgContext(TestLangParser::ProgContext* node,
                 TransformInfo<Antlr4Node>& info) {

  // Start Rule
  TestLangParser::ProgContext* copy =
    new TestLangParser::ProgContext(nullptr, -1);

  return copy;
}

TestLangParser::ExprContext*
cloneExprContext(TestLangParser::ExprContext* node,
                 TransformInfo<Antlr4Node>& info) {
  TestLangParser::ExprContext* copy =
    new TestLangParser::ExprContext(
      dynamic_cast<TestLangParser::ExprContext*>(
        info.parent != nullptr ?
          info.parent->tree() : nullptr),
      node->invokingState);

  return copy;
}

Antlr4Node cloneTestLangNode(const Antlr4Node& node,
                             TransformInfo<Antlr4Node>& info) {
  Antlr4Node& node_nonconst =
    const_cast<Antlr4Node&>(node);

  const std::type_info& tinfo =
    typeid(*node_nonconst.tree());

  if (tinfo == typeid(TestLangParser::ProgContext)) {
    TestLangParser::ProgContext* copy =
      cloneProgContext(
        dynamic_cast<TestLangParser::ProgContext*>(node_nonconst.tree()),
        info);

    return Antlr4Node(GenericParseTree<Antlr4Node>::TESTLANG, copy);

  } else if (tinfo == typeid(TestLangParser::ExprContext)) {
    TestLangParser::ExprContext* copy =
      cloneExprContext(
        dynamic_cast<TestLangParser::ExprContext*>(node_nonconst.tree()),
        info);
    return Antlr4Node(GenericParseTree<Antlr4Node>::TESTLANG, copy);

  } else if (tinfo == typeid(antlr4::tree::TerminalNodeImpl)) {
    antlr4::tree::TerminalNodeImpl* copy =
      new antlr4::tree::TerminalNodeImpl(
        dynamic_cast<antlr4::tree::TerminalNodeImpl*>(node_nonconst.tree())->getSymbol());

    copy->setParent(
      info.parent != nullptr ?
      dynamic_cast<antlr4::RuleContext*>(info.parent->tree()) :
      nullptr);

    return Antlr4Node(
      GenericParseTree<Antlr4Node>::TESTLANG,
      copy);
  }

  /* Unknown type */
  throw std::runtime_error(
    "Unknow TestLang NodeType: " + std::string(tinfo.name()));
}

Antlr4Node cloneTestLang(const Antlr4Node& tree) {
  return Concepts::NAryTree::transform<Antlr4Node>(
    tree, cloneTestLangNode);
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
                   if (tree == t) {
                     return other.tree_;
                   }

                   return t;
                 });

  other.tree_->parent = tree_->parent;
  tree_ = other.tree_;
  return true;
}

void Antlr4Node::appendChild(Antlr4Node& node) {
  this->tree()->children.push_back(node.tree());
  children_.push_back(node);
}

void Antlr4Node::appendChild(Antlr4Node&& node) {
  this->tree()->children.push_back(node.tree());
  children_.push_back(node);
}

} // Base
