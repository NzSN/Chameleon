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
       const std::string rTemplateArg,
       const int langArg):
    label(labelArg),
    leftSide(&leftSideArg),
    rTemplate(rTemplateArg),
    lang(langArg) {}

  const std::string label;
  const Pattern<T>* leftSide;

  Pattern<T>* buildRightSide(Environment<T>& env) {

  }

  const std::string rTemplate;
  const int lang;
  //const CondExpr cond;
};

} // Rewrite
} // TransEngine


#endif /* RULE_H */
