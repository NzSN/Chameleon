
#ifndef SIGMATERM_H
#define SIGMATERM_H

#include "Concepts/n_ary_tree.h"
#include "Base/generic_parsetree_inl.h"

namespace TransEngine {

template<Base::GPTMeta T>
struct SigmaTerm: public Base::GenericParseTree<T> {
  SigmaTerm(const Base::GenericParseTree<T>& t):
    Base::GenericParseTree<T>(t) {

    MAP_TO_TREE(t);
  }

private:
  DEFINE_AS_LAYER_OF_NARY_TREE(
    SigmaTerm, Base::GenericParseTree<T>,
    private);
};

template<Base::GPTMeta T>
struct Pattern: public Base::GenericParseTree<T> {
  Pattern(const Base::GenericParseTree<T>& t):
    Base::GenericParseTree<T>{t} {

    MAP_TO_TREE(t);
  }

  bool isTermVar() const {
    return isTermVar_;
  }

  std::string termID() const {
    return termID_;
  }

private:
  std::string termID_;
  bool isTermVar_;
  DEFINE_AS_LAYER_OF_NARY_TREE(
    Pattern, Base::GenericParseTree<T>,
    private);
};

} // TransEngine


#endif /* SIGMATERM_H */
