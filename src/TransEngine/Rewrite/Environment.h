#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>
#include <stdexcept>
#include <optional>

#include "Base/generic_parsetree_inl.h"
#include "Term.h"

namespace TransEngine {
namespace Rewrite {

// INVARIANT:
//  1.For all a,b in TermIdent, if both a and b are binded
//    then a != b. (TermIdent Uniqueness)
template<Base::GPTMeta T>
class Bindings {
public:
  // Identifier of a term in bindings is determined
  // by Transform Rules. For example, there is a rule:
  // {| a + 1 |} => {| a * 1 |}
  //
  // This rule binds terms that match with left side
  // pattern to identifier "a".
  using TermIdent = std::string;

  void bind(const TermIdent& ident, Term<T> term) {
    bindings_.insert_or_assign(ident, term);
  }

  const Term<T> operator[](const TermIdent& ident) const {
    if (bindings_.contains(ident)) {
      return std::get<1>(*bindings_.find(ident));
    } else {
      throw std::overflow_error(
        "No term is binding to " + ident + ".");
    }
  }

  bool isBinded(const TermIdent& ident) const {
    return bindings_.contains(ident);
  }

  void unbind(const TermIdent& ident) {
    if (bindings_.contains(ident)) {
      bindings_.erase(ident);
    }
  }

private:
  std::unordered_map<TermIdent, Term<T>> bindings_;
};

/* Environment is a collection of Variable bindings. */
template<Base::GPTMeta T>
class Environment {
public:
  Environment():
    targetTerm_{nullptr}, matchTerm_{nullptr} {}

  Base::GenericParseTree<T>* targetTerm() {
    return targetTerm_;
  }

  void setTargetTerm(Base::GenericParseTree<T>* t) {
    targetTerm_ = t;
  }

  Base::GenericParseTree<T>* matchTerm() {
    return matchTerm_;
  }

  void setMatchTerm(Base::GenericParseTree<T>* t) {
    matchTerm_ = t;
  }

  Bindings<T>& bindings() {
    return bindings_;
  }
private:
  Base::GenericParseTree<T>* targetTerm_;
  Base::GenericParseTree<T>* matchTerm_;
  Bindings<T> bindings_;
};


} // Rewrite
} // TransEngine

#endif /* ENVIRONMENT_H */
