#ifndef STRATEGY_INL_H
#define STRATEGY_INL_H

#include "Strategy.h"
#include "TransEngine/PatternMatching.h"

namespace TransEngine {
namespace Rewrite {

// BuildStra(MatchStra(R, E), E);

template<Base::GPTMeta T>
struct MatchStra: public Strategy<T> {

  Algorithms::CaptureTerms<T> termVars;

  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    auto maybeMatch = Algorithms::patternMatchingTermCapture<T>(
      rule.leftSide,
      env.targetTerm(),
      &termVars);

    if (!maybeMatch.has_value()) {
      // Failed to pattern matched, do nothing
      // about side effect works to environments.
      return rule;
    }

    // Setup the term that have matched, so conseque
    // straties able to apply changed.
    env.setMatchTerm(maybeMatch.value());

    // Setup Variable bindings to Environments.
  }
};

template<Base::GPTMeta T>
StrategySet<T> ruleBreakDown(Rule<T> rule) {

}

} // Rewrite
} // TransEngine

#endif /* STRATEGY_INL_H */
