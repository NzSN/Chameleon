
#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include <unordered_map>
#include <optional>
#include <cassert>

#include "Concepts/n_ary_tree.h"
#include "SigmaTerm.h"

#include "Rewrite/Environment.h"
#include "Rewrite/Term.h"

using TransEngine::Rewrite::Environment;
using TransEngine::Rewrite::Term;

namespace Algorithms {
enum MatchAlgor {
  NORMAL
};

template<MatchAlgor A>
concept PATTERMATCH_ALGO_NAIVE = A == MatchAlgor::NORMAL;

template<Base::GPTMeta T>
using CaptureTerms = std::unordered_map<
  typename TransEngine::Pattern<T>::TermID,
  Base::GenericParseTree<T>*>;

template<Base::GPTMeta T,
         MatchAlgor algor = MatchAlgor::NORMAL>
requires PATTERMATCH_ALGO_NAIVE<algor>
std::optional<Base::GenericParseTree<T>*>
patternMatchingTermCapture(
  const TransEngine::Pattern<T>& pattern,
  Base::GenericParseTree<T>& subjectTree,
  Environment<T>* env) {

  const auto matching =
    [](const TransEngine::Pattern<T>& pattern,
       const Base::GenericParseTree<T>& subjectTree,
       Environment<T>* env) -> bool {

      return Concepts::NAryTree::equal<
        TransEngine::Pattern<T>,
        Base::GenericParseTree<T>>(
          pattern, subjectTree,
          [&env](const TransEngine::Pattern<T>& lhs,
                 const Base::GenericParseTree<T>& rhs) {

            TransEngine::Pattern<T>& lhsMut =
              const_cast<TransEngine::Pattern<T>&>(lhs);
            Base::GenericParseTree<T>& rhsMut =
              const_cast<Base::GenericParseTree<T>&>(rhs);

            if (lhs.isTermVar()) {
              // Capture Term Variables
              if (env != nullptr) {
                env->bindings().bind(
                 lhs.termID(),
                  Term(const_cast<Base::GenericParseTree<T>&>(rhs)));
              } else {
                return true;
              }
              return true;
            } else {
              return lhs.getMeta() == rhs.getMeta();
            }
          },
          // Predicate to detect extra condition to exits,
          // in this case, the extra condition is reach a TermVar
          // of a pattern.
          [](const TransEngine::Pattern<T>& lhs,
             const Base::GenericParseTree<T>& rhs) {
            return lhs.isTermVar();
          });
    };

  // Maching on the root of subject tree
  if (matching(pattern, subjectTree, env)) {
    return &subjectTree;
  }

  // Maching on another SubTree of Subject Tree.
  for (auto& child: Concepts::NAryTree::getChildren(subjectTree)) {
    auto matchRet = patternMatchingTermCapture<T>(pattern, *child, env);
    if (matchRet.has_value()) {
      return matchRet.value();
    }
  }

  return std::nullopt;
}


template<Base::GPTMeta T,
         MatchAlgor algor = MatchAlgor::NORMAL>
requires PATTERMATCH_ALGO_NAIVE<algor>
std::optional<Base::GenericParseTree<T>*>
patternMatching(TransEngine::Pattern<T>& pattern,
                Base::GenericParseTree<T>& subjectTree) {
  return patternMatchingTermCapture<T>(
    pattern, subjectTree, nullptr);
}

} // Algorithms

#endif /* PATTERNMATCHING_H */
