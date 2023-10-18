#ifndef CONDEXPR_H
#define CONDEXPR_H

#include "Environment.h"
#include "Base/generic_parsetree.h"

namespace TransEngine {
namespace Rewrite {

class CondExpr {
public:
  template<Base::GPTMeta T>
  bool operator()(Environment<T>* env) {}

private:

};

} // Rewrite
} // TransEngine

#endif /* CONDEXPR_H */
