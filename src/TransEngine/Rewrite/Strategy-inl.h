#ifndef STRATEGY_INL_H
#define STRATEGY_INL_H

#include <iostream>
#include <plog/Log.h>
#include <stdexcept>
#include <algorithm>


#include "Term.h"
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
  MatchStra() = default;
  MatchStra(Rule<T> r): Strategy<T>{r} {}

  ~MatchStra() {}
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
    Algorithms::patternMatchingTermCapture<T>(
      *rule.leftSide->lowerAsPossible(),
      *env.targetTerm(),
      &env)
      .and_then([&](auto tree) -> std::optional<Base::GenericParseTree<T> *>{
          // Setup the term that have matched, so conseque
          // straties able to apply changed.
          env.setMatchTerm(tree);
          return tree;
        })
      .or_else([&] -> std::optional<Base::GenericParseTree<T> *> {
          // Reset all bindings otherwise
          // INVARIANT break which will
          // cause dirty bindings to allow
          // ill-formed rule to perform.
          env.bindings().clear();
          return std::nullopt;
        });

    return rule;
  }
};

struct FAILED_TO_EVALUATE_WHERE: public std::exception {
  ~FAILED_TO_EVALUATE_WHERE() {}
  const char* what() const noexcept {
    return "Failed to evaluaate where expressions";
  }
};

// Where clause to control side effects that happened
// during Match Strategy.
template<Base::GPTMeta T>
struct WhereStra: public Strategy<T> {
  WhereStra() = default;
  WhereStra(Rule<T> r): Strategy<T>{r} {}

  // Evaluate all expression within where clause.
  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    bool success = std::all_of(rule.cond.begin(),
                               rule.cond.end(),
                               [&env](auto& cond) {
                                 return cond(&env);
                               });
    if (!success) {
      // Clear side effects make by MatchStrategy.
      env.bindings().clear();
      env.setMatchTerm(nullptr);
    }
    return rule;
  }
};

// Build right side pattern on Environment<T>::buildTerm_
template<Base::GPTMeta T>
struct BuildStra: public Strategy<T> {
  BuildStra() = default;
  BuildStra(Rule<T> r): Strategy<T>{r} {}

  ~BuildStra() {}
  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    // Make sure there are matches need to be tramsform
    if (!env.matchTerm()) {
      return rule;
    }

    std::unique_ptr<T> metaCopy = rule.rightSide->getMeta().clone();

    // Try to replace all TermVars with terms have
    // binded.
    std::unique_ptr<Pattern<T>>
      copy = Pattern<T>::template mapping<T, Utility::DYNAMIC>(*metaCopy);
    std::vector<Pattern<T>*> vars = copy->termVars();
    for (auto v: vars) {
      // Perform replacement onto Pattern
      Term<T> term = env.bindings()[v->termID()];
      v->bind(term);
    }

    if (env.matchTerm()->parent != nullptr) {
        // Replace the matched tree with the tree the
        // just builded.
      env.matchTerm()->setNode(
        *Base::GenericParseTree<T>
        ::template mapping<T, Utility::DYNAMIC>(*metaCopy));

      return rule;
    } else {
      // The entire tree is required to be
      // replaced.
      //
      // TODO: Case that need to replace the whole
      //       match term.
      std::unreachable();
    }
  }
};

// Without Where clause
template<Base::GPTMeta T>
StrategySeq<T> ruleBreakDown(Rule<T>& rule) {
  // A rule is breakdown into Strategy language:
  //   match(r); where(r) /* Optional */; build(r);
  StrategySeq<T> seq;
  seq.emplace_back(
    std::make_unique<MatchStra<T>>(rule));

  if (rule.cond.size() > 0) {
    // Where Strategy
    seq.emplace_back(
      std::make_unique<WhereStra<T>>(rule));
  }

  seq.emplace_back(
    std::make_unique<BuildStra<T>>(rule));

  return seq;
}

} // Rewrite
} // TransEngine

#endif /* STRATEGY_INL_H */
