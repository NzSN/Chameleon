
#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include <unordered_map>
#include <optional>
#include <cassert>

#include "Concepts/n_ary_tree.h"
#include "SigmaTerm.h"

namespace Algorithms {
enum MatchAlgor {
  NORMAL
};

template<Base::GPTMeta T>
using CaptureTerms = std::unordered_map<
  typename TransEngine::Pattern<T>::TermID,
  Base::GenericParseTree<T>*>;

template<Base::GPTMeta T,
         MatchAlgor select = NORMAL,
         typename = std::enable_if_t<select == NORMAL>>
std::optional<Base::GenericParseTree<T>*>
patternMatchingTermCapture(
  TransEngine::Pattern<T>& pattern,
  Base::GenericParseTree<T>& subjectTree,
  CaptureTerms<T>* terms) {

  const auto matchingSubTree =
    [](const TransEngine::Pattern<T>& pattern,
       const Base::GenericParseTree<T>& subjectTree,
       CaptureTerms<T>* terms) -> bool {

      return Concepts::NAryTree::equal<
        TransEngine::Pattern<T>,
        Base::GenericParseTree<T>>(
          pattern, subjectTree,
          [&terms](const TransEngine::Pattern<T>& lhs,
             const Base::GenericParseTree<T>& rhs) {

            if (lhs.isTermVar()) {
              // Capture Term Variables
              if (terms != nullptr) {
                (*terms)[lhs.termID()] =
                  const_cast<Base::GenericParseTree<T>*>(&rhs);
              }

              return true;
            } else {
              return lhs.getMeta() == rhs.getMeta();
            }
          });
    };

  // Maching on the root of subject tree
  if (matchingSubTree(pattern, subjectTree, terms)) {
    return &subjectTree;
  }

  // Maching on another SubTree of Subject Tree.
  for (auto& child: Concepts::NAryTree::getChildren(subjectTree)) {
    auto matchRet = patternMatchingTermCapture<T>(pattern, child, terms);
    if (matchRet.has_value()) {
      return matchRet.value();
    }
  }

  return std::nullopt;
}


template<Base::GPTMeta T,
         MatchAlgor select = NORMAL,
         typename = std::enable_if_t<select == NORMAL>>
std::optional<Base::GenericParseTree<T>*>
patternMatching(TransEngine::Pattern<T>& pattern,
                Base::GenericParseTree<T>& subjectTree) {
  return patternMatchingTermCapture<T>(
    pattern, subjectTree, nullptr);
}

} // Algorithms

#endif /* PATTERNMATCHING_H */
