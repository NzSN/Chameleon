#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include <optional>

#include "Base/generic_parsetree_inl.h"
#include "Term.h"

namespace TransEngine {

/* Environment is a collection of Variable bindings. */
template<Base::GPTMeta T>
class Environment {
public:
  using TermIdent = std::string;
  std::optional<Term<T>> operator[](const TermIdent& ident) {
    if (bindings.contains(ident)) {
      return bindings[ident];
    } else {
      return std::nullopt;
    }
  }

  bool contains(const TermIdent& ident) {
    return bindings.contains(ident);
  }

private:
  std::map<TermIdent, Term<T>> bindings;
};

} // TransEngine

#endif /* ENVIRONMENT_H */
