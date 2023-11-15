#ifndef CONDEXPR_H
#define CONDEXPR_H

#include <vector>

#include "Environment.h"
#include "Base/generic_parsetree.h"
#include "ExprTree.h"

#include "TransEngine/SigmaTerm.h"


namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
class CondExpr {
public:

  bool operator()(Environment<T>* env) {}

private:
  using PatternOP =
    std::function<bool(
      TransEngine::Pattern<T>&,
      TransEngine::Pattern<T>&)>;

  Utility::BinExprTree<
    TransEngine::Pattern<T>,
    TransEngine::Pattern<T>,
    PatternOP,
    Environment<T>*>
  cond;
};

} // Rewrite
} // TransEngine

#endif /* CONDEXPR_H */
