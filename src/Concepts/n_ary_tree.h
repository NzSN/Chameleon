#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H

#include <iostream>
#include <ranges>
#include <concepts>
#include <functional>
#include <utility>

namespace Concepts::NAryTree {

template<typename T, typename V>
concept Children_t = std::ranges::range<T> &&
  (std::same_as<std::ranges::range_value_t<T>, V> ||
   std::same_as<std::ranges::range_value_t<T>, V*>);


template<typename T>
concept WalkByFunction = requires(T t) {
  { t.getChildren() } -> Children_t<T>;
  { t.getChild(int{}) } -> std::same_as<T>;
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

} // Concepts::NAryTree


#endif /* N_ARY_TREE_H */
