#ifndef CONDEXPR_H
#define CONDEXPR_H

#include <vector>

#include "Environment.h"
#include "Base/generic_parsetree.h"
#include "Expr/Expr.h"

#include "TransEngine/SigmaTerm.h"


namespace TransEngine {
namespace Rewrite {

template<Base::GPTMeta T>
class CondExpr {
public:

  bool operator()(Environment<T>* env);

private:
  Expression::Expr<T> condExpr;
};

} // Rewrite
} // TransEngine

#endif /* CONDEXPR_H */
