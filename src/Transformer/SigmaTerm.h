
#ifndef SIGMATERM_H
#define SIGMATERM_H

#include "Base/generic_parsetree_inl.h"

namespace Transformer {

template<Base::GPTMeta T>
struct SigmaTerm: public Base::GenericParseTree<T> {
  SigmaTerm(const T& meta):
    Base::GenericParseTree<T>(meta) {}
};

template<Base::GPTMeta T>
struct Pattern: public Base::GenericParseTree<T> {
public:
  Pattern(const T& meta):
    Base::GenericParseTree<T>(meta) {}

  bool match(const Pattern& other) const {
  }

  bool isTermVar;
};

} // Transformer


#endif /* SIGMATERM_H */
