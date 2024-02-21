#ifndef STRATEGY_H
#define STRATEGY_H

#include <set>
#include <vector>
#include "Rule.h"
#include "Environment.h"
#include "Base/generic_parsetree.h"

namespace Chameleon {
namespace TransEngine {
namespace Rewrite {

template<Base::Layer T>
struct Rule;

template<Base::Layer T>
struct Strategy;

template<Base::Layer T>
using StrategyUnique = std::unique_ptr<Strategy<T>>;

template<Base::Layer T>
using StrategySet = std::set<StrategyUnique<T>>;

template<Base::Layer T>
using StrategySeq = std::vector<StrategyUnique<T>>;

template<Base::Layer T>
struct StrategyBase {
  virtual ~StrategyBase() {}
  virtual Rule<T>& operator()(
    Rule<T>& rule, Environment<T>&) = 0;
};

template<Base::Layer T>
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
template<Base::Layer T>
StrategySeq<T> ruleBreakDown(Rule<T>& rule);

} // Rewrite
} // TransEngine
} // Chameleon

#endif /* STRATEGY_H */
