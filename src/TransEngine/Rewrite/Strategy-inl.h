#ifndef STRATEGY_INL_H
#define STRATEGY_INL_H

#include <iostream>
#include <plog/Log.h>
#include <stdexcept>
#include <algorithm>


#include "utility.h"
#include "Term.h"
#include "Strategy.h"
#include "Parser/Parser-inl.h"
#include "TransEngine/PatternMatching.h"

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace TransEngine {
namespace Rewrite {

// PRECONDITION:
//   1.*Environment<T>::targetTerm_ in ParseTree<T>
//   2.Cardinality of Environment<T>::bindings_ is 0.
// POSTCONDITION(success):
//   1.Environment<T>::matchTerm_ != nullptr
//   2.Cardinality of Environment<T>::bindings_ should be
//     bigger than 0 if there are TermVar in left side pattern.
// otherwise left the Environment UNCHANGED.

template<Base::Layer T>
Environment<T>::MatchTerms toEnvMatchs(
  std::vector<Algorithms::Match<T>>& matchs) {

  typename Environment<T>::MatchTerms terms{};

  for (auto& match: matchs) {
    Bindings<T> bindings;
    for (auto& var: match.termVars) {
      if (bindings.isBinded(std::get<0>(var))) {
        // WARNING
      }
      bindings.bind(std::get<0>(var), std::get<1>(var));
    }
    terms.push_back(
      std::make_tuple(match.matched, std::move(bindings)));
  }

  return terms;
}

template<Base::Layer T>
struct MatchMultiStra: public Strategy<T> {
  MatchMultiStra() = default;
  MatchMultiStra(Rule<T> r): Strategy<T>{r} {}

  ~MatchMultiStra() {}
  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    if (env.targetTerm() == nullptr) {
      throw std::runtime_error(
        "TargetTerm not found by MatchStra Object");
    }
    if (env.bindings().size() > 0) {
      throw std::runtime_error(
        "Some dirty bindings remains in Environment.");
    }

    std::vector<Algorithms::Match<T>> matchs =
      Algorithms::patternMatchingTermCaptureMulti(
        *rule.leftSide->lowerAsPossible(),
        *env.targetTerm());
    env.setMatchTerms(toEnvMatchs(matchs));

    return rule;
  }
};

struct FAILED_TO_EVALUATE_WHERE: public std::exception {
  ~FAILED_TO_EVALUATE_WHERE() {}
  const char* what() const noexcept {
    return "Failed to evaluaate where expressions";
  }
};

template<Base::Layer T>
struct WhereMultiStra: public Strategy<T> {
  WhereMultiStra() = default;
  WhereMultiStra(Rule<T> r): Strategy<T>{r} {}

  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    std::vector<typename Environment<T>::MatchTerms::iterator>
      fails;

    // Apply predicate or side effects to all
    // matches.
    for (auto it = env.matchTerms().begin();
       it != env.matchTerms().end(); ++it) {

      env.setCurrentTerm(*it);

      bool success = std::all_of(rule.cond.begin(), rule.cond.end(),
        [&env](auto& cond) {
          return cond(&env);
        });

      if (!success) {
        // Clear side effects make by MatchStrategy.
        fails.push_back(it);
      }
    }

    for (auto it: fails) {
      env.matchTerms().erase(it);
    }

    // FIXME: Currently, only where clause use environment to
    //        hold resources. So clear resources here is fine
    //        but it may be an invalid oepration in the future.
    return rule;
  }
};

template<Base::Layer T>
struct BuildMultiStra: public Strategy<T> {
  BuildMultiStra() = default;
  BuildMultiStra(Rule<T> r): Strategy<T>{r} {}

  ~BuildMultiStra() {}
  Rule<T>& operator()(Rule<T>& rule, Environment<T>& env) {
    Utility::CallAtExit guard{[&env] {
      env.clearResource();
    }};

    // Make sure there are matches need to be tramsform
    if (env.matchTerms().size() == 0) {
      return rule;
    }

    // Sort MatchTerms in ascending order.
    env.template sortMatchTerms<false>(
      [&](const Environment<T>::MatchTerm& lhs,
         const Environment<T>::MatchTerm& rhs) {

        auto* lTree = env.getTree(lhs);
        auto* rTree = env.getTree(rhs);

      return lTree->getDepth() < rTree->getDepth();
    });

    // Iterate over all MatchTerms
    for (auto& term: env.matchTerms()) {
      env.setCurrentTerm(term);

      // Try to replace all TermVars with terms have
      // binded.
      std::unique_ptr<Pattern<T>>
        copy = rule.rightSide->clone();
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
          *Base::ParseTree<T>
           ::template mapping<T, Base::DYNAMIC>(copy->getMetaMut()));
      } else {
        // The entire tree is required to be
        // replaced.
        //
        // TODO: Case that need to replace the whole
        //       match term.
        std::unreachable();
      }
    }

    return rule;
  }
};

template<Base::Layer T>
using MatchStra = MatchMultiStra<T>;
template<Base::Layer T>
using WhereStra = WhereMultiStra<T>;
template<Base::Layer T>
using BuildStra = BuildMultiStra<T>;

// Without Where clause
template<Base::Layer T>
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
