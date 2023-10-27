#ifndef STRATEGY_H
#define STRATEGY_H

#include <set>
#include <vector>
#include "Rule.h"
#include "Environment.h"
#include "Base/generic_parsetree.h"

namespace TransEngine {
namespace Rewrite {

using UNUSED_V = int;

template<Base::GPTMeta T>
struct Rule;

template<Base::GPTMeta T>
struct Strategy;

template<Base::GPTMeta T>
using StrategySet = std::set<Strategy<T>>;

template<Base::GPTMeta T>
using StrategySeq = std::vector<Strategy<T>>;

template<Base::GPTMeta T>
struct Strategy {
  virtual UNUSED_V operator()(
    Rule<T>& rule, Environment<T>&) = 0;
};

// Break down a transform rule into Strategies
// due to this system use Strategy language
// low-level core language to describe transformations.
template<Base::GPTMeta T>
StrategySeq<T> ruleBreakDown(Rule<T> rule);

} // Rewrite
} // TransEngine

#endif /* STRATEGY_H */
