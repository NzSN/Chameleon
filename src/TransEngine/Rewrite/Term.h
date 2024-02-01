#ifndef TERM_H
#define TERM_H

#include <string>
#include <functional>

#include "class_prop.h"
#include "Base/generic_parsetree_inl.h"


namespace TransEngine {
namespace Rewrite {

using TermID = std::string;

/* This structure represent a subtree of
 * ParseTree, and this structures is used for
 * binding purposes. */
template<Base::Layer T>
struct Term {
  Term() {}

  Term(std::unique_ptr<Base::GenericParseTree<T>>&& t):
    dangleTree_{std::move(t)}, tree{dangleTree_} {}

  Term(Base::GenericParseTree<T>& t):
    tree{t} {}
  Term(const Term& other):
    tree{other.tree} {}
  Term(const Term&& other):
    tree{std::move(other.tree)} {}

  Term& operator=(const Term& other) {
    tree = other.tree;
    return *this;
  }

  Term& operator=(const Term&& other) {
    tree = std::move(other.tree);
    return *this;
  }

  bool operator==(const Term& other) const {
    return tree.get() == other.tree.get();
  }

  bool operator!=(const Term& other) const {
    return tree.get() != other.tree.get();
  }


  using RefWrapperGPT =
    std::reference_wrapper<
    Base::GenericParseTree<T>>;


private:
  std::unique_ptr<Base::GenericParseTree<T>> dangleTree_;

public:
  RefWrapperGPT tree;

  // Users should use Term as value.
  DISALLOW_HEAP_OBJECT_DIRECTLY;
};

} // Rewrite
} // TransEngine

#endif /* TERM_H */
