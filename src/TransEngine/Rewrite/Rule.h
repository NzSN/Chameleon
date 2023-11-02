#ifndef RULE_H
#define RULE_H

#include <memory>

#include "Base/generic_parsetree.h"
#include "TransEngine/SigmaTerm.h"
//#include "CondExpr.h"
#include "Environment.h"

namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
struct Rule {
  Rule(std::string labelArg,
       const Pattern<T>& leftSideArg,
       const Pattern<T>& rightSideArg,
       const int langArg):
    label(labelArg),
    leftSide(&leftSideArg),
    rightSide(&rightSideArg),
    lang(langArg) {}

  const std::string label;
  const Pattern<T>* leftSide;
  const Pattern<T>* rightSide;

  const int lang;
  //const CondExpr cond;
};

} // Rewrite
} // TransEngine


#endif /* RULE_H */
