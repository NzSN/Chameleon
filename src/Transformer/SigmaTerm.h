
#ifndef SIGMATERM_H
#define SIGMATERM_H

#include "Concepts/n_ary_tree.h"
#include "Base/generic_parsetree_inl.h"

namespace Transformer {

template<Base::GPTMeta T>
struct SigmaTerm: public Base::GenericParseTree<T> {
  SigmaTerm(const T& meta):
    Base::GenericParseTree<T>(meta) {}

private:
  LAYER_OF_NARY_TREE(SigmaTerm, Base::GenericParseTree<T>);
};

template<Base::GPTMeta T>
struct Pattern: public Base::GenericParseTree<T> {
  Pattern(const T& meta):
    Base::GenericParseTree<T>(meta) {
    buildLayer(*this);
  }

  bool isTermVar;

private:
  LAYER_OF_NARY_TREE(Pattern, Base::GenericParseTree<T>);
};

} // Transformer


#endif /* SIGMATERM_H */
