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

  using Children = std::vector<Antlr4Node>;
  Antlr4Node(int lang, antlr4::tree::ParseTree* tree);

  Antlr4Node(const Antlr4Node& other);
  Antlr4Node& operator=(const Antlr4Node& other);

  SrcRange sourceRange() const;

  std::vector<Antlr4Node>& getChildren() {
    return children_;
  };

  Antlr4Node* parent;

  bool setNode(const Antlr4Node& other);

  void appendChild(Antlr4Node& node);
  void appendChild(Antlr4Node&& node);

  Antlr4Node clone();

  bool operator==(const Antlr4Node&) const;
  antlr4::tree::ParseTree* tree() { return tree_; };
private:
  int lang_;
  Children children_;

  // no-owning
  antlr4::tree::ParseTree* tree_;
};
using Antlr4GPT = GenericParseTree<Antlr4Node>;

} // Base

#endif /* GENERIC_PARSETREE_ANTLR4_H */
