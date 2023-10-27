
#ifndef SIGMATERM_H
#define SIGMATERM_H

#include "utility.h"
#include "Concepts/n_ary_tree.h"
#include "Base/generic_parsetree_inl.h"

namespace TransEngine {

template<Base::GPTMeta T>
struct Pattern: public Base::GenericParseTree<T> {
  Pattern(const Base::GenericParseTree<T>& t):
    Base::GenericParseTree<T>{t} {

    MAP_TO_TREE(t);
  }

  bool isTermVar() const {
    return Utility::isTermVar(
      const_cast<Pattern*>(this)->getText());
  }

  std::string termID() const {
    return termID_;
  }

private:
  std::string termID_;
  DEFINE_AS_LAYER_OF_NARY_TREE(
    Pattern, Base::GenericParseTree<T>,
    private);
};

} // TransEngine


#endif /* SIGMATERM_H */
