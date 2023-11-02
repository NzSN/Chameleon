#ifndef TREELAYER_H
#define TREELAYER_H

#include <concepts>
#include <type_traits>

#include "Concepts/n_ary_tree.h"
#include "utility.h"


template<Concepts::NAryTree::NAryTree T>
struct TreeLayer {
  T& addChild(T type);

  std::vector<T>& getChildren();
  std::optional<T> getChild(int i);

  template<Concepts::NAryTree::NAryTree U,
           Utility::ALLOC_STORAGE_DURATION Storage = Utility::AUTOMATIC,
           typename = std::enable_if_t<Storage == Utility::AUTOMATIC>>
  static T mapping(const U& o);

};

#endif /* TREELAYER_H */
