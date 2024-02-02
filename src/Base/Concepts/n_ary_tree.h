#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H

#include <memory>
#include <cassert>
#include <ranges>
#include <concepts>
#include <functional>
#include <vector>
#include <type_traits>

#include "utility.h"

namespace Concepts::NAryTree {

template<typename T, typename V>
concept Children_t =
  std::ranges::range<T> &&
  (std::same_as<std::ranges::range_value_t<T>, V> ||
   std::same_as<std::ranges::range_value_t<T>,
                std::unique_ptr<V>> ||
   std::same_as<std::ranges::range_value_t<T>, V*>);

template<typename T>
concept WalkByFunction =
  requires(T t) {
    { t.getChildren() } -> Children_t<T>;
    { t.parent } -> std::convertible_to<T*>;
  };

template<typename T>
concept WalkByDataMember = requires(T t) {
  { t.children } -> Children_t<T>;
  { t.parent } -> std::convertible_to<T*>;
};

template<typename T>
concept NAryTree =
  (WalkByFunction<T> || WalkByDataMember<T>);

// Types that satisfied this constrains could be
// used to construct an NAryTree.
template<typename T>
concept Constructible =
  NAryTree<T> &&
  // Interface to append children.
  // Caution: This operation is required to setup parent pointer of child.
  requires(T t, std::unique_ptr<T> arg) {
    { t.appendChild(arg) } -> std::same_as<void>;
  };


template<WalkByFunction T>
auto& getChildren(const T& t) {
  return const_cast<T&>(t).getChildren();
}

template<WalkByDataMember T>
auto& getChildren(const T& t) {
  return const_cast<T&>(t).children;
}

// Raw pointer version
template<typename T>
requires std::is_pointer_v<T>
auto& derefMaybe(T t) {
  return *t;
}

// Deal with smart pointer
template<typename T>
requires Utility::is_derefable<T>::value &&
         Utility::is_arrow<T>::value &&
         (!std::is_pointer_v<T>)
auto& derefMaybe(T& t) {
  return *t;
}

template<typename T>
requires Utility::is_derefable<T>::value &&
         Utility::is_arrow<T>::value &&
         (!std::is_pointer_v<T>)
auto& derefMaybe(const T& t) {
  return *t;
}


// Value semantic
template<typename T>
requires (!std::is_pointer_v<T>) &&
         (!Utility::is_derefable<T>::value) &&
         (!Utility::is_arrow<T>::value)
T& derefMaybe(T& t) {
  return t;
}

/* Algorithms */
template<NAryTree T>
std::vector<T*> search(const T& t, std::function<bool(T&)> p) {
  std::vector<T*> result;

  T& tMut = const_cast<T&>(t);
  if (p(tMut)) {
    result.push_back(&tMut);
  }

  for (auto& c: getChildren(t)) {
    T& v = derefMaybe(c);
    auto subResult = search(v, p);

    for (auto c: subResult) {
      result.push_back(c);
    }
  }

  return result;
}

template<NAryTree T, NAryTree R>
bool equal(const T& l, const R& r,
           std::function<bool(const T&, const R&)> equal_fn,
           std::function<bool(const T&, const R&)> bottom_fn = nullptr) {
  bool isEqual = equal_fn(l, r);
  if (!isEqual) { return false; }

  if (bottom_fn && bottom_fn(l, r)) {
    return isEqual;
  }

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
    const T& lchild = derefMaybe(*lcurrent);
    const R& rchild = derefMaybe(*rcurrent);

    isEqual &= Concepts::NAryTree::equal(
      lchild, rchild, equal_fn, bottom_fn);

    if (!isEqual) return isEqual;

    ++lcurrent;
    ++rcurrent;
  }

  return isEqual;
}

// Note: T should be in Concept NAryTree.
#define MAP_TO_TREE(T) buildLayer(*this, T);
#define DEFINE_AS_LAYER_OF_NARY_TREE(L, T, ACCESS)         \
public:                                                    \
  L* parent;                                               \
  std::vector<L>& getChildren() { return children_; }      \
  const T* lowerLayer;                                     \
private:                                                   \
  /* Hide children to prevent ambiguous
   * to choose getChidlren */                              \
  std::vector<L> children_;                                \
  void buildLayer(L& l, const T& t) {                      \
    parent = nullptr;                                      \
    /* Mapping  to lower layer for current node */         \
    mapLayer(l, t);                                        \
    /* Mapping to lower layer for children */              \
    for (auto& c: Concepts::NAryTree::getChildren(t)) {    \
      children_.emplace_back(c);                           \
    }                                                      \
    for (auto& c: children_) {                             \
      c.parent = &l;                                       \
    }                                                      \
  }                                                        \
  void mapLayer(L& l, const T& t) { l.lowerLayer = &t; }   \
ACCESS:

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
        auto& children = getChildren(*node);
        if (idx >= static_cast<int>(children.size())) {
          return nullptr;
        }

        node = &children[idx];
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

      // Check equality of current node
      if (u.lowerLayer == current) {
        // FIXME: No concept to assert that
        //        there is a member function, size(),
        //        is exists.
        if (getChildren(u).size() == 0) {
          // No Child
          return true;
        } else {
          // Checking for subtree
          int i = 0;
          pos.push_back(0);

          for (auto& c: getChildren(u)) {
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


template<typename T>
struct TransformInfo {
  T* parent;
};

template<Constructible T>
std::unique_ptr<T> transform_unique(
  const T* t,
  std::function<std::unique_ptr<T>(
    const T&, TransformInfo<T>&)> f,
  TransformInfo<T> info = { nullptr }) {

  std::unique_ptr<T> copy = f(*t, info);

  for (auto& c: getChildren(*t)) {
    copy->appendChild(transform_unique(c.get(), f, { copy.get() }));
  }

  return copy;
}

template<Constructible T>
requires std::is_copy_assignable_v<T>
T transform(const T& t,
            std::function<T(const T&, TransformInfo<T>& info)> f,
            TransformInfo<T> info = { nullptr }) {
  T copy = f(t, info);

  for (auto& c: getChildren(t)) {
    copy.appendChild(transform(c, f, { &copy }));
  }

  return copy;
}

} // Concepts::NAryTree


#endif /* N_ARY_TREE_H */
