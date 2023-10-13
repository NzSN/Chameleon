#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H

#include <cassert>
#include <iostream>
#include <ranges>
#include <concepts>
#include <functional>
#include <utility>
#include <vector>

namespace Concepts::NAryTree {

template<typename T, typename V>
concept Children_t = std::ranges::range<T> &&
  (std::same_as<std::ranges::range_value_t<T>, V> ||
   std::same_as<std::ranges::range_value_t<T>, V*>);

template<typename T>
concept WalkByFunction = requires(T t) {
  { t.getChildren() } -> Children_t<T>;
};

template<typename T>
concept WalkByDataMember = requires(T t) {
  { t.children } -> Children_t<T>;
};

template<typename T>
concept NAryTree =
  WalkByFunction<T> || WalkByDataMember<T>;

template<WalkByFunction T>
auto& getChildren(const T& t) {
  return const_cast<T&>(t).getChildren();
}

template<WalkByDataMember T>
auto& getChildren(const T& t) {
  return const_cast<T&>(t).children;
}

template<typename T,
         typename = std::enable_if_t<std::is_pointer_v<T>>>
auto& derferIfAvailable(T t) {
  return *t;
}

template<typename T,
         typename = std::enable_if_t<!std::is_pointer_v<T>>>
T derferIfAvailable(T t) {
  return t;
}

/* Algorithms */
template<NAryTree T, NAryTree R>
bool equal(const T& l, const R& r,
           std::function<bool(const T&, const R&)> equal_fn) {
  bool isEqual = equal_fn(l, r);

  const auto& children_l = getChildren(l);
  const auto& children_r = getChildren(r);

  if (std::ranges::size(children_l) !=
      std::ranges::size(children_r)) {
    return false;
  }

  auto lcurrent = std::ranges::cbegin(children_l),
    lend = std::ranges::cend(children_l);
  auto rcurrent = std::ranges::cbegin(children_r),
    rend = std::ranges::cend(children_r);

  while (lcurrent != lend && rcurrent != rend) {
    const T& lchild = derferIfAvailable(*lcurrent);
    const R& rchild = derferIfAvailable(*rcurrent);

    isEqual &= Concepts::NAryTree::equal(lchild, rchild, equal_fn);
    if (!isEqual) return isEqual;

    ++lcurrent;
    ++rcurrent;
  }

  return isEqual;
}

// Note: T should be in Concept NAryTree.
#define MAP_TO_TREE(T) buildLayer(*this, T);
#define DEFINE_AS_LAYER_OF_NARY_TREE(L, T) \
  std::vector<L>& getChildren() { return children; }  \
  std::vector<L> children; \
  const T* lowerLayer;\
  void buildLayer(L& l, const T& t) {\
    /* Mapping  to lower layer for current node */               \
    mapLayer(l, t);                                              \
    /* Mapping to lower layer for children */                    \
    for (const auto& c: const_cast<T&>(t).getChildren()) {             \
      children.emplace_back(c);                  \
    }                                       \
  }                                         \
  void mapLayer(L& l, const T& t) { l.lowerLayer = &t; }

template<typename T, typename L>
concept TreeLayer =
  NAryTree<T> &&
  NAryTree<L> &&
  requires(T t) {
    { t.lowerLayer } -> std::convertible_to<const L*>;
  };

template<NAryTree LOWER, TreeLayer<LOWER> UPPER>
bool isIsomorphic(const UPPER& u, const LOWER& l) {
  std::vector<int> pos;

  const LOWER* current = nullptr;
  const auto& getNode =
    [](std::vector<int>& pos, const LOWER& l) -> LOWER* {
      LOWER* node = &const_cast<LOWER&>(l);
      for (auto& idx: pos) {
        assert(idx < node->getChildren().size());
        node = &node->getChildren()[idx];
      }

      return node;
    };
  const std::function<bool(const UPPER& u,
    const LOWER& l,
    std::vector<int>&,
    int)> isomorphicCheck =

    [&](const UPPER& u,
        const LOWER& l,
        std::vector<int>& pos,
        int level) {

      // Root node
      if (level == 0) {
        current = &l;
      } else {
        current = getNode(pos, l);
      }

      assert(current != nullptr);

      // Check equality of current node
      if (u.lowerLayer == current) {
        // FIXME: No concept to assert that
        //        there is a member function, size(),
        //        is exists.
        if (const_cast<UPPER&>(u).getChildren().size() == 0) {
          // No Child
          return true;
        } else {
          // Checking for subtree
          int i = 0;
          pos.push_back(0);

          for (auto& c: const_cast<UPPER&>(u).getChildren()) {
            pos[level] = i++;

            if (!isomorphicCheck(c, l, pos, level+1)) {
              pos.pop_back();
              return false;
            }
          }
          pos.pop_back();
          return true;
        }
      } else {
        return false;
      }
    };

  return isomorphicCheck(u, l, pos, 0);
}

} // Concepts::NAryTree


#endif /* N_ARY_TREE_H */
