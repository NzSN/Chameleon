#ifndef STRATEGY_INL_H
#define STRATEGY_INL_H

#include <iostream>
#include <stdexcept>

#include "Strategy.h"
#include "Parser/Parser-inl.h"
#include "TransEngine/PatternMatching.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

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
    if (env.bindings().size() > 0) {
      throw std::runtime_error(
        "Some dirty bindings remains in Environment.");
    }

    // PatternMatching TargetTerm within Environment with
    // left side pattern of Rule, all TermVars will be binded
    // to correspond terms during PatternMatching.
    auto maybeMatch = Algorithms::patternMatchingTermCapture<T>(
      *rule.leftSide,
      *env.targetTerm(),
      &env);

    if (!maybeMatch.has_value()) {
      // Reset all bindings otherwise
      // INVARIANT break which will
      // cause dirty bindings to allow
      // ill-formed rule to perform.
      env.bindings().clear();
      return rule;
    }

    // Setup the term that have matched, so conseque
    // straties able to apply changed.
    env.setMatchTerm(maybeMatch.value());

    return rule;
  }
};

// Build right side pattern on Environment<T>::buildTerm_
template<Base::GPTMeta T>
struct BuildStra: public Strategy<T> {
  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    // Build right side pattern
    std::istringstream codes{rule.rTemplate};

    auto treeMaybe = Parser::ParserRuntimeSelect(rule.lang, codes);
    if (treeMaybe.has_value()) {
      Base::GenericParseTree<T> tree =
        std::get<Base::GenericParseTree<T>>(treeMaybe.value());


    } else {
      // Failed to build right side pattern.
    }
  }
};

template<Base::GPTMeta T>
StrategySet<T> ruleBreakDown(Rule<T> rule) {}

} // Rewrite
} // TransEngine

#endif /* STRATEGY_INL_H */
