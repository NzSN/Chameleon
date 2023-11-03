#ifndef GENERIC_PARSETREE_INL_H
#define GENERIC_PARSETREE_INL_H

#include <memory>
#include "generic_parsetree.h"
#include "utility.h"

namespace Base {

template<GPTMeta T>
bool GenericParseTree<T>::operator==(
  const GenericParseTree& other) const {
  // GenericParseTree is recursive type which requrie that
  // equality check should be recursive too.
  std::function<bool(const GenericParseTree& l,
    const GenericParseTree& r)>
    equality_check = [&equality_check](
      const GenericParseTree& l, const GenericParseTree& r) {
      // Check node type
      if (!(l.metaRef == r.metaRef)) {
        return false;
      }

      // Check equality of childs
      if (l.childs_.size() != r.childs_.size()) {
        return false;
      } else {
        // Terminal
        if (l.childs_.size() == 0) {
          return true;
        }

        auto zipped = Utility::zip_vector<GenericParseTree>(
          l.childs_, r.childs_);
        if (zipped.size() == 0) { return false; }

        for (auto& [thisChilds, otherChilds]: zipped) {
          if (!equality_check(thisChilds, otherChilds)) {
            return false;
          }
        }
        return true;
      }
    };
  return equality_check(*this, other);
}

template<GPTMeta T>
void GenericParseTree<T>::traverse(
  std::function<bool(GenericParseTree&)> proc) {

  if (!proc(*this)) return;
  for (auto& c: childs_) {
    c.traverse(proc);
  }
}


template<GPTMeta T>
GenericParseTree<T>* GenericParseTree<T>::select(
  std::function<bool(GenericParseTree&)> predicate) {

  GenericParseTree* tree = NULL;
  traverse([&](GenericParseTree& node) {
    if (predicate(node)) {
      tree = &node;
      return false;
    } else {
      return true;
    }
  });
  return tree;
}

} // Base

#endif /* GENERIC_PARSETREE_INL_H */
