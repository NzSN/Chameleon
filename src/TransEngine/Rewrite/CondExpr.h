#ifndef CONDEXPR_H
#define CONDEXPR_H

#include <vector>

#include "Environment.h"
#include "Base/generic_parsetree.h"
#include "ExprTree.h"


namespace TransEngine {
namespace Rewrite {

class CondExpr {
public:
  template<Base::GPTMeta T>
  bool operator()(Environment<T>* env) {}

private:
  // FIXME: Determination the content of
  //        condition expression.
  // Utility::BinExprTree<
  // typename R,
  // typename LEAF,
  // typename OP,
  // Environment<T>*> cond;
};

} // Rewrite
} // TransEngine

#endif /* CONDEXPR_H */
