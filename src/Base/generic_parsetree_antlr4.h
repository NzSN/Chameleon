#ifndef GENERIC_PARSETREE_ANTLR4_H
#define GENERIC_PARSETREE_ANTLR4_H

#include "generic_parsetree_inl.h"

namespace Base {

// Due to antlr4::tree::ParseTree does not
// satisfy the constraint of GPTMeta then
// an adapter is required.
//
// With Antlr4Node, user able to spawn a
// GenericParseTree from Antlr4Node by calling to
// method Antlr4GPT::mapping().
class Antlr4Node {
public:
  const int lang;
  Antlr4Node(int lang1, antlr4::tree::ParseTree* t1):
    lang{lang1}, tree{t1} {}

  SrcRange sourceRange() const;
  std::vector<antlr4::tree::ParseTree> childs();
  bool operator==(const Antlr4Node&) const;
private:
  antlr4::tree::ParseTree* tree;
};
using Antlr4GPT = GenericParseTree<Antlr4Node>;

} // Base

#endif /* GENERIC_PARSETREE_ANTLR4_H */
