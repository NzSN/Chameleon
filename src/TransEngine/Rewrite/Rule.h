#ifndef RULE_H
#define RULE_H

#include <memory>

#include "Base/generic_parsetree.h"
#include "TransEngine/SigmaTerm.h"
#include "CondExpr.h"
#include "Environment.h"

namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
struct Rule {
  Rule():
    label{}, leftSide{nullptr},
    rightSide{nullptr}, lang{}  {}

  Rule(std::string labelArg,
       Pattern<T>& leftSideArg,
       Pattern<T>& rightSideArg,
       const int langArg):
    label(labelArg),
    leftSide(&leftSideArg),
    rightSide(&rightSideArg),
    lang(langArg) {}

  ~Rule() {}

  Rule(std::string labelArg,
       std::shared_ptr<Pattern<T>> leftSideArg,
       std::shared_ptr<Pattern<T>> rightSideArg,
       const int langArg):
    label{labelArg},
    leftSide_shared{leftSideArg},
    rightSide_shared{rightSideArg},
    lang{langArg} {

    leftSide = leftSide_shared.get();
    rightSide = rightSide_shared.get();
  }

  Rule(const Rule& other):
    label{other.label},

    leftSide_shared{other.leftSide_shared},
    rightSide_shared{other.rightSide_shared},

    leftSide{other.leftSide},
    rightSide{other.rightSide},

    lang{other.lang} {}

  void setCond(CondExpr<T>& cond_) {
    cond.push_back(cond_);
  }

  const std::string label;

  std::shared_ptr<Pattern<T>> leftSide_shared;
  std::shared_ptr<Pattern<T>> rightSide_shared;

  Pattern<T>* leftSide;
  Pattern<T>* rightSide;

  const int lang;

  std::vector<CondExpr<T>> cond;
};

} // Rewrite
} // TransEngine


#endif /* RULE_H */
