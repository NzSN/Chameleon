#ifndef RULE_H
#define RULE_H

#include "Base/generic_parsetree.h"
#include "TransEngine/SigmaTerm.h"
#include "CondExpr.h"

namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
class Rule {
public:
  Base::GenericParseTree<T> operator()(Base::GenericParseTree<T>&);
private:
  std::string label;
  Pattern<T> leftSide;
  Pattern<T> rightSide;
  CondExpr cond;
};

} // Rewrite
} // TransEngine


#endif /* RULE_H */
