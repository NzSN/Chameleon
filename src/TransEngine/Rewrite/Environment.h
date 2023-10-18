#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include "Base/generic_parsetree_inl.h"
#include "Term.h"

namespace TransEngine {

/* Environment is a collection of Variable bindings. */
template<Base::GPTMeta T>
class Environment {
public:
  using TermIdent = std::string;

private:
  std::map<TermIdent, Base::GenericParseTree<T>> bindings;
};

} // TransEngine

#endif /* ENVIRONMENT_H */
