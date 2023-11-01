
#ifndef SIGMATERM_H
#define SIGMATERM_H

#include <string>

#include "Rewrite/Term.h"
#include "utility.h"
#include "Concepts/n_ary_tree.h"
#include "Base/generic_parsetree_inl.h"

namespace TransEngine {

template<Base::GPTMeta T>
struct Pattern: public Base::GenericParseTree<T> {
  using TermID = std::string;

  Pattern(const Base::GenericParseTree<T>& t):
    Base::GenericParseTree<T>{t},
    termID_{const_cast<Pattern*>(this)->getText()} {

    MAP_TO_TREE(t);
  }

  bool isTermVar() const {
    return Utility::isTermVar(
      const_cast<Pattern*>(this)->getText());
  }

  std::string termID() const {
    return termID_;
  }

  std::vector<Pattern*> termVars() {
    std::vector<Pattern*> vars =
      Concepts::NAryTree::search<Pattern>(
        *this,
        [](const Pattern& p) {
          return p.isTermVar();
        });

    return vars;
  }

  bool bind(Rewrite::Term<T> term) {
    if (!this->isTermVar()) {
      // Only nodes represent a TermVar
      // able to bind to a term.
      return false;
    }

    if (parent == nullptr) {
      /* Ignored case */
    } else {
      const_cast<Base::GenericParseTree<T>*>(this->lowerLayer)
        ->setNode(term.tree.get());
    }

    return true;
  }

private:
  std::string termID_;
  DEFINE_AS_LAYER_OF_NARY_TREE(
    Pattern, Base::GenericParseTree<T>,
    private);
};

} // TransEngine


#endif /* SIGMATERM_H */
