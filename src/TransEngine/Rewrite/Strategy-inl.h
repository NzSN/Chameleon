#ifndef STRATEGY_INL_H
#define STRATEGY_INL_H

#include <stdexcept>

#include "Strategy.h"
#include "TransEngine/PatternMatching.h"

namespace TransEngine {
namespace Rewrite {

// PRECONDITION:
//   1.*Environment<T>::targetTerm_ in GenericParseTree<T>
//   2.Cardinality of Environment<T>::bindings_ is 0.
// POSTCONDITION(success):
//   1.Environment<T>::matchTerm_ != nullptr
//   2.Cardinality of Environment<T>::bindings_ should be
//     bigger than 0 if there are TermVar in left side pattern.
// otherwise left the Environment UNCHANGED.
template<Base::GPTMeta T>
struct MatchStra: public Strategy<T> {

  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    if (env.targetTerm() == nullptr) {
      throw std::runtime_error(
        "TargetTerm not found by MatchStra Object");
    }

    // PatternMatching TargetTerm within Environment with
    // left side pattern of Rule, all TermVars will be binded
    // to correspond terms during PatternMatching.
    auto maybeMatch = Algorithms::patternMatchingTermCapture<T>(
      *rule.leftSide,
      *env.targetTerm(),
      &env);

    if (!maybeMatch.has_value()) {
      // Failed to pattern matched, do nothing
      // about side effect works to environments.
      return rule;
    }

    // Setup the term that have matched, so conseque
    // straties able to apply changed.
    env.setMatchTerm(maybeMatch.value());

    return rule;
  }
};

template<Base::GPTMeta T>
StrategySet<T> ruleBreakDown(Rule<T> rule) {

}

} // Rewrite
} // TransEngine

#endif /* STRATEGY_INL_H */
