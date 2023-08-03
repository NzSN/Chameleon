#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H

#include <ranges>
#include <concepts>
#include <functional>

namespace Concepts {

template<typename T>
concept NAryTree = requires(T t) {
  { t.children() } -> std::ranges::range;
};

/* Algorithms */
template<NAryTree T, NAryTree R>
bool equal(const T& l, const R& r,
           std::function<bool(const T&, const R&)> equal_fn) {
  bool isEqual = equal_fn(l, r);

  auto& children_l =
    const_cast<T&>(l).children();
  auto& children_r =
    const_cast<R&>(r).children();
  if (std::ranges::size(children_l) !=
      std::ranges::size(children_r)) {
    return false;
  }

  auto lcurrent = std::ranges::cbegin(children_l),
    lend = std::ranges::cend(children_l);
  auto rcurrent = std::ranges::cbegin(children_r),
    rend = std::ranges::cend(children_r);

  while (lcurrent != lend && rcurrent != rend) {
    isEqual &= equal(*lcurrent, *rcurrent, equal_fn);
    if (!isEqual) return isEqual;

    ++lcurrent;
    ++rcurrent;
  }

  return isEqual;
}

} // Concepts


#endif /* N_ARY_TREE_H */
