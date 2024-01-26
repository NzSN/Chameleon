
#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include <unordered_map>
#include <optional>
#include <cassert>
#include <ranges>

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

enum MatchMode {
  FIRST_MATCH,
  MATCH_ALL,
};

template<MatchAlgor A>
concept PATTERMATCH_ALGO_NAIVE = A == MatchAlgor::NORMAL;
template<MatchMode M>
concept PATTERNMATCH_MODE_FIRST_MATCH = M == MatchMode::FIRST_MATCH;
template<MatchMode M>
concept PATTERNMATCH_MODE_MATCH_ALL = M == MatchMode::MATCH_ALL;

template<Base::GPTMeta T>
struct Match {
  using TermIdent = TransEngine::Rewrite::Bindings<T>::TermIdent;
  using MatchTerms = std::vector<std::tuple<TermIdent, Term<T>>>;
  // The tree be matched
  Base::GenericParseTree<T>* matched;
  MatchTerms termVars;
};

template<Base::GPTMeta T>
bool matching(const TransEngine::Pattern<T>& pattern,
             const Base::GenericParseTree<T>& subjectTree,
             typename Match<T>::MatchTerms* termVars) {

  return Concepts::NAryTree::equal<TransEngine::Pattern<T>,
                              Base::GenericParseTree<T>>
    (pattern, subjectTree,
     // Equality predicate
     [termVars](const TransEngine::Pattern<T>& lhs,
                 const Base::GenericParseTree<T>& rhs) {
       if (lhs.isTermVar()) {
         if (termVars) {
           termVars->push_back(
             std::make_tuple(
               lhs.termID(),
               Term(const_cast<Base::GenericParseTree<T>&>(rhs)))
             );
         }
         return true;
       } else {
         return lhs.getMeta() == rhs.getMeta();
       }
     },
     // Bottom condition, stop when a TermVar is matched.
     [](const TransEngine::Pattern<T>& lhs,
        const Base::GenericParseTree<T>& rhs)
       { return lhs.isTermVar(); }
      );
}

template<Base::GPTMeta T,
         MatchMode mode = MatchMode::MATCH_ALL,
         MatchAlgor algor = MatchAlgor::NORMAL>
requires PATTERMATCH_ALGO_NAIVE<algor>
std::vector<Match<T>>
doPatternMatching(
  const TransEngine::Pattern<T>& pattern,
  Base::GenericParseTree<T>& subjectTree) {

  std::vector<Match<T>> matchs{};

  Match<T> match{&subjectTree};
  if (matching(pattern, subjectTree, &match.termVars)) {
    matchs.push_back(match);
    if (PATTERNMATCH_MODE_FIRST_MATCH<mode>) {
      return matchs;
    }
  }

  auto& children = Concepts::NAryTree::getChildren(subjectTree);
  for (auto& child: children) {
    auto matches_child = doPatternMatching<T>(pattern, *child);
    matchs.insert(matchs.end(), matches_child.begin(), matches_child.end());
  }

  return matchs;
}

// FIXME: Remove side effect in matching,
//        so the argument Environment<T> can also
//        be removed.
template<Base::GPTMeta T,
         MatchAlgor algor = MatchAlgor::NORMAL>
requires PATTERMATCH_ALGO_NAIVE<algor>
std::optional<Base::GenericParseTree<T>*>
patternMatchingTermCapture(
  const TransEngine::Pattern<T>& pattern,
  Base::GenericParseTree<T>& subjectTree, Environment<T>* env) {

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
