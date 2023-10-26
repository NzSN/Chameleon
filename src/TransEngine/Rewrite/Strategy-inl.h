#ifndef STRATEGY_INL_H
#define STRATEGY_INL_H

#include "Strategy.h"

namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
struct MatchStra: public Strategy<T> {
  using UNUSED_V = Strategy<T>::UNUSED_V;

  UNUSED_V operator()(
    Rule<T>& rule, Environment<T>* env) {

  }
};

template<Base::GPTMeta T>
StrategySet<T> ruleBreakDown(Rule<T> rule) {

}

} // Rewrite
} // TransEngine

#endif /* STRATEGY_INL_H */
