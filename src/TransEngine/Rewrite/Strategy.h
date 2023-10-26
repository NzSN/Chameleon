#ifndef STRATEGY_H
#define STRATEGY_H

#include <set>
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
using StrategySet = std::set<Strategy<T>>;

template<Base::GPTMeta T>
struct Strategy {
  using UNUSED_V = int;
  virtual UNUSED_V operator()(
    Rule<T>& rule, Environment<T>*) = 0;
};

// Break down a transform rule into Strategies
// due to this system use Strategy language
// low-level core language to describe transformations.
template<Base::GPTMeta T>
StrategySet<T> ruleBreakDown(Rule<T> rule);

} // Rewrite
} // TransEngine

#endif /* STRATEGY_H */
