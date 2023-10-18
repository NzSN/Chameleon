
#ifndef TERM_H
#define TERM_H

#include <string>
#include "Base/generic_parsetree_inl.h"

template<Base::GPTMeta T>
class Term {
public:
  Term(std::string ident,
       Base::GenericParseTree<T> t);

  bool operator=(const Term& other) const {}
  bool operator=(const std::string& other) const {}
};

#endif /* TERM_H */
