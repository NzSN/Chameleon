#ifndef TREELAYER_H
#define TREELAYER_H

#include <concepts>
#include <type_traits>

#include "Concepts/n_ary_tree.h"
#include "utility.h"


template<typename T>
struct TreeLayer {
  TreeLayer(): depth_{0} {}

  T& addChild(T type);

  void setDepth(size_t depth) {
    depth_ = depth;
  }

  size_t getDepth() const {
    return depth_;
  }

  template<Concepts::NAryTree::NAryTree U,
           Utility::ALLOC_STORAGE_DURATION Storage = Utility::AUTOMATIC>
  requires Utility::isAutoStorage<Storage>
  static T mapping(const U& o) {
    T tree = T(o);
    for (auto& c: Concepts::NAryTree::getChildren(o)) {
      tree.addChild(mapping<U, Utility::DYNAMIC>(
                      Concepts::NAryTree::derefMaybe(c)));
    }

    for (auto& c: Concepts::NAryTree::getChildren(tree)) {
      Concepts::NAryTree::derefMaybe(c).parent = &tree;
    }

    return tree;
  }

  // Cases that every nodes of generated Treelayer
  // is dynamics, with type std::unique_ptr<T>.
  template<Concepts::NAryTree::NAryTree U,
           Utility::ALLOC_STORAGE_DURATION Storage = Utility::AUTOMATIC>
  requires Utility::isDynamicStorage<Storage>
  static std::unique_ptr<T>
  mapping(const U& o) {
    std::unique_ptr<T> tree = std::make_unique<T>(o);
    for (auto& c: Concepts::NAryTree::getChildren(o)) {
      tree->addChild(mapping<U, Utility::DYNAMIC>(
                       Concepts::NAryTree::derefMaybe(c)));
    }

    for (auto& c: Concepts::NAryTree::getChildren(*tree)) {
      c->parent = tree.get();
    }

    return tree;
  }

private:
  size_t depth_;
};

#endif /* TREELAYER_H */
