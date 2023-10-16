
#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include "Concepts/n_ary_tree.h"
#include "SigmaTerm.h"

namespace Algorithms {
enum MatchAlgor {
  NORMAL
};

template<Base::GPTMeta T,
         MatchAlgor select = NORMAL,
         typename = std::enable_if_t<select == NORMAL>>
bool patternMatching(TransEngine::Pattern<T> pattern,
                    TransEngine::SigmaTerm<T> subjectTree) {

  const auto matchingSubTree =
    [](const TransEngine::Pattern<T>& pattern,
       const TransEngine::SigmaTerm<T> subjectTree) -> bool {

      return Concepts::NAryTree::equal<
        TransEngine::Pattern<T>,
        TransEngine::SigmaTerm<T>>(

          pattern, subjectTree,
          [](const TransEngine::Pattern<T>& lhs,
             const TransEngine::SigmaTerm<T>& rhs) {
            if (lhs.isTermVar()) {
              return true;
            } else {
              return lhs.getMeta() == rhs.getMeta();
            }
          });
    };

  // Maching on the root of subject tree
  if (matchingSubTree(pattern, subjectTree)) {
    return true;
  }

  // Maching on another SubTree of Subject Tree.
  for (auto& child: Concepts::NAryTree::getChildren(subjectTree)) {
    if (patternMatching<T>(pattern, child)) {
      return true;
    }
  }

  return false;
}

} // Algorithms

#endif /* PATTERNMATCHING_H */
