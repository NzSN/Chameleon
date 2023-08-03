#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H

#include <ranges>
#include <concepts>
#include <functional>

namespace Concepts {

template<typename T>
concept NAryTree = requires(T t) {
  { t.children } -> std::ranges::range;
} || requires(T t) {
  { t.children() } -> std::ranges::range;
};

/* Algorithms */
template<NAryTree T, NAryTree R>
bool equal(const T& l, const R& r,
           std::function<bool(const T&, const R&)> equal_fn) {
  bool isEqual = equal_fn(l, r);

  if (std::ranges::size(l.children) != std::ranges::size(r.children)) {
    return false;
  }

  auto lcurrent = std::ranges::cbegin(l.children),
    lend = std::ranges::cend(l.children);
  auto rcurrent = std::ranges::cbegin(r.children),
    rend = std::ranges::cend(r.children);

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
