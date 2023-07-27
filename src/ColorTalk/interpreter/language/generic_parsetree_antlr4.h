#ifndef GENERIC_PARSETREE_ANTLR4_H
#define GENERIC_PARSETREE_ANTLR4_H

#include "generic_parsetree.h"

namespace Rules::Interpreter::Language {

// Due to antlr4::tree::ParseTree does not
// satisfy the constraint of GPTMeta then
// an adapter is required.
struct Antlr4Node {
  const int lang;
  antlr4::tree::ParseTree* tree;

  Antlr4Node(int lang1, antlr4::tree::ParseTree* t1):
    lang{lang1}, tree{t1} {}

  bool operator==(const Antlr4Node&) const;
};
using Antlr4GPT = GenericParseTree<Antlr4Node>;

template<>
template<>
Antlr4GPT Antlr4GPT::mapping(Antlr4Node tree);

} // Rules::Interpreter::Language

#endif /* GENERIC_PARSETREE_ANTLR4_H */
