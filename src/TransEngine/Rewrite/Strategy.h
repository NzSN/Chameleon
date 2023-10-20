#ifndef STRATEGY_H
#define STRATEGY_H

#include "Environment.h"
#include "Base/generic_parsetree.h"

namespace TransEngine {

template<Base::GPTMeta T>
struct Strategy {
  using UNUSED_V = int;
  virtual UNUSED_V operator()(
    UNUSED_V lhs, UNUSED_V rhs, Environment<T>*) = 0;
};

template<Base::GPTMeta T>
struct MatchStra: public Strategy<T> {
  using UNUSED_V = Strategy<T>::UNUSED_V;

  UNUSED_V operator()(
    UNUSED_V lhs, UNUSED_V rhs, Environment<T>* env) {

  }
};

} // TransEngine

#endif /* STRATEGY_H */
