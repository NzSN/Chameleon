#ifndef TREELAYER_H
#define TREELAYER_H

#include <memory>
#include "Base/Concepts/n_ary_tree.h"

namespace Base {

enum ALLOC_STORAGE_DURATION {
  AUTOMATIC,
  DYNAMIC,
};

template<ALLOC_STORAGE_DURATION duration>
concept isAutoStorage = duration == ALLOC_STORAGE_DURATION::AUTOMATIC;

template<ALLOC_STORAGE_DURATION duration>
concept isDynamicStorage = duration == ALLOC_STORAGE_DURATION::DYNAMIC;

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
           ALLOC_STORAGE_DURATION Storage = AUTOMATIC>
  requires isAutoStorage<Storage>
  static T mapping(const U& o) {
    T tree = T(o);
    for (auto& c: Concepts::NAryTree::getChildren(o)) {
      tree.addChild(mapping<U, DYNAMIC>(
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
           ALLOC_STORAGE_DURATION Storage = AUTOMATIC>
  requires isDynamicStorage<Storage>
  static std::unique_ptr<T>
  mapping(const U& o) {
    std::unique_ptr<T> tree = std::make_unique<T>(o);
    for (auto& c: Concepts::NAryTree::getChildren(o)) {
      tree->addChild(mapping<U, DYNAMIC>(
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

template<typename T, typename Lower>
struct BindableLayer {
  BindableLayer() = default;
  BindableLayer(BindableLayer&& other) noexcept :
    lower_{std::move(other.lower_)} {}

  void bindLayer(std::unique_ptr<Lower>&& lower) {
    lower_ = std::move(lower);
  }

  std::unique_ptr<Lower> unbindLayer() {
    return std::move(lower_);
  }
private:
  std::unique_ptr<Lower> lower_;
};

} // Base


#endif /* TREELAYER_H */
