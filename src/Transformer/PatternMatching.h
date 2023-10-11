
#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include "Concepts/n_ary_tree.h"
#include "SigmaTerm.h"

namespace Algorithms {
enum MatchAlgor {
  NORMAL
};

template<MatchAlgor select = NORMAL,
         Base::GPTMeta T,
         std::enable_if_t<select == NORMAL>>
bool patternMaching(Transformer::Pattern<T> pattern,
                    Transformer::SigmaTerm<T> subjectTree) {

  auto& matchingSubTree =
    [](const Transformer::Pattern<T>& pattern,
       const Transformer::SigmaTerm<T> subjectTree) {

      Concepts::NAryTree::equal<Transformer::Pattern<T>,
                                Transformer::SigmaTerm<T>>(
        pattern, subjectTree,
        [](const Transformer::Pattern<T>& lhs,
           const Transformer::SigmaTerm<T>& rhs) {
          if (lhs.isTermVar || rhs.isTermVar) {
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
  for (auto& child: subjectTree.getChildren()) {
    if (patternMaching<NORMAL, T>(pattern, child)) {
      return true;
    }
  }

  return false;
}

} // Algorithms

#endif /* PATTERNMATCHING_H */
