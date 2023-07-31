#ifndef GENERIC_PARSETREE_ANTLR4_H
#define GENERIC_PARSETREE_ANTLR4_H

#include "generic_parsetree_inl.h"

namespace Rules::Interpreter::Language {

// Due to antlr4::tree::ParseTree does not
// satisfy the constraint of GPTMeta then
// an adapter is required.
//
// With Antlr4Node, user able to spawn a
// GenericParseTree from Antlr4Node by calling to
// method Antlr4GPT::mapping().
struct Antlr4Node {
  const int lang;
  antlr4::tree::ParseTree* tree;

  Antlr4Node(int lang1, antlr4::tree::ParseTree* t1):
    lang{lang1}, tree{t1} {}

  Antlr4Node& preorder_traverse();
  SrcRange sourceRange();

  std::vector<antlr4::tree::ParseTree> childs();
  bool operator==(const Antlr4Node&) const;
};
using Antlr4GPT = GenericParseTree<Antlr4Node>;

} // Rules::Interpreter::Language

#endif /* GENERIC_PARSETREE_ANTLR4_H */
