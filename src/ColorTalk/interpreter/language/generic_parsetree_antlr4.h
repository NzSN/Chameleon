#ifndef GENERIC_PARSETREE_ANTLR4_H
#define GENERIC_PARSETREE_ANTLR4_H

#include "generic_parsetree.h"

namespace Rules::Interpreter::Language {

struct Antlr4Node {
  const int lang;

  bool operator==(const Antlr4Node&) const;
};
using Antlr4GPT = GenericParseTree<Antlr4Node>;

template<>
template<>
Antlr4GPT Antlr4GPT::mapping(Antlr4Node tree);

} // Rules::Interpreter::Language

#endif /* GENERIC_PARSETREE_ANTLR4_H */
