#ifndef GENERIC_PARSETREE_ANTLR4_H
#define GENERIC_PARSETREE_ANTLR4_H

#include "generic_parsetree_inl.h"

/////////////////////////////////////////////////////////////////////////////
//                         ANTLR4 DeepCopy Listener                        //
/////////////////////////////////////////////////////////////////////////////
#include "generic_parsetree_antlr4_testlang_deepcopy.h"
#include "generic_parsetree_antlr4_wgsl_deepcopy.h"


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

  Antlr4Node() = default;

  using Node = std::unique_ptr<Antlr4Node>;
  using Children = std::vector<Node>;
  Antlr4Node(int lang, antlr4::tree::ParseTree* tree);

  Antlr4Node(const Antlr4Node& other);

  Antlr4Node& operator=(const Antlr4Node& other);

  ~Antlr4Node() {}

  SrcRange sourceRange() const;

  Children& getChildren() {
    return children_;
  };

  Antlr4Node* parent;

  bool setNode(const Antlr4Node& other);

  void appendChild(Node& node);
  void appendChild(Node&& node);

  Node clone() const;

  bool operator==(const Antlr4Node&) const;
  antlr4::tree::ParseTree* tree() { return tree_; };

  std::string getText() {
    return tree_->getText();
  }

  Antlr4Node* withoutHeader();

  int lang() { return lang_; }

private:
  int lang_;

  // no-owning
  antlr4::tree::ParseTree* tree_;

  Children children_;
};
using Antlr4GPT = GenericParseTree<Antlr4Node>;

} // Base

#endif /* GENERIC_PARSETREE_ANTLR4_H */
