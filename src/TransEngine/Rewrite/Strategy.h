#ifndef STRATEGY_H
#define STRATEGY_H

#include <type_traits>
#include <set>
#include <vector>
#include "Rule.h"
#include "Environment.h"
#include "Base/generic_parsetree.h"

namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
struct Rule;

template<Base::GPTMeta T>
struct Strategy;

template<Base::GPTMeta T>
using StrategyUnique = std::unique_ptr<Strategy<T>>;

template<Base::GPTMeta T>
using StrategySet = std::set<StrategyUnique<T>>;

template<Base::GPTMeta T>
using StrategySeq = std::vector<StrategyUnique<T>>;

template<Base::GPTMeta T>
struct StrategyBase {
  virtual ~StrategyBase() {}
  virtual Rule<T>& operator()(
    Rule<T>& rule, Environment<T>&) = 0;
};

template<Base::GPTMeta T>
struct Strategy: public StrategyBase<T> {

  Strategy() {}
  ~Strategy() {}
  Strategy(Rule<T> rule):
    bindedRule{rule} {}

  // If a strategy is binded with a Rule then
  // the binding rule will be used as parameter
  // while operator() is called.
  Rule<T> bindedRule;
};

// Break down a transform rule into Strategies
// due to this system use Strategy language
// low-level core language to describe transformations.
template<Base::GPTMeta T>
StrategySeq<T> ruleBreakDown(Rule<T>& rule);

} // Rewrite
} // TransEngine

#endif /* STRATEGY_H */
