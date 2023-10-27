
#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include <optional>

#include "Concepts/n_ary_tree.h"
#include "SigmaTerm.h"

namespace Algorithms {
enum MatchAlgor {
  NORMAL
};

template<Base::GPTMeta T,
         MatchAlgor select = NORMAL,
         typename = std::enable_if_t<select == NORMAL>>
std::optional<Base::GenericParseTree<T>*>
patternMatching(TransEngine::Pattern<T>& pattern,
                Base::GenericParseTree<T>& subjectTree) {
  const auto matchingSubTree =
    [](const TransEngine::Pattern<T>& pattern,
       const Base::GenericParseTree<T> subjectTree) -> bool {

      return Concepts::NAryTree::equal<
        TransEngine::Pattern<T>,
        Base::GenericParseTree<T>>(

          pattern, subjectTree,
          [](const TransEngine::Pattern<T>& lhs,
             const Base::GenericParseTree<T>& rhs) {
            if (lhs.isTermVar()) {
              return true;
            } else {
              return lhs.getMeta() == rhs.getMeta();
            }
          });
    };

  // Maching on the root of subject tree
  if (matchingSubTree(pattern, subjectTree)) {
    return &subjectTree;
  }

  // Maching on another SubTree of Subject Tree.
  for (auto& child: Concepts::NAryTree::getChildren(subjectTree)) {
    auto matchRet = patternMatching<T>(pattern, child);
    if (matchRet.has_value()) {
      return matchRet.value();
    }
  }

  return std::nullopt;
}

} // Algorithms

#endif /* PATTERNMATCHING_H */
