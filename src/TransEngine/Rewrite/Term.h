#ifndef TERM_H
#define TERM_H

#include <string>
#include <functional>

#include "class_prop.h"
#include "Base/generic_parsetree_inl.h"


namespace TransEngine {
namespace Rewrite {

/* This structure represent an already binded Term
 * variable. */
template<Base::GPTMeta T>
struct Term {
  Term(std::string identArg,
       Base::GenericParseTree<T>& t):
    ident{identArg}, tree{t} {}
  Term(const Term& other):
    ident{other.ident}, tree{other.tree} {}
  Term(const Term&& other):
    ident{std::move(other.ident)},
    tree{std::move(other.tree)} {}

  Term& operator=(const Term& other) const {
    ident = other.ident;
    tree = other.ident;
  }

  Term& operator=(const Term&& other) const {
    ident = std::move(other.ident);
    tree = std::move(other.tree);
  }

  bool operator==(const Term& other) const {
    return ident == other.ident &&
      tree.get() == other.tree.get();
  }

  const std::string ident;
  using RefWrapperGPT =
    std::reference_wrapper<Base::GenericParseTree<T>>;
  RefWrapperGPT tree;

  // Users should use Term as value.
  DISALLOW_HEAP_OBJECT_DIRECTLY;
};

} // Rewrite
} // TransEngine

#endif /* TERM_H */
