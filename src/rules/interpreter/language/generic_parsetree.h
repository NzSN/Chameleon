
#ifndef GENERIC_PARSETREE_H
#define GENERIC_PARSETREE_H

#include "antlr4-runtime.h"
#include <typeinfo>
#include <memory>
#include <vector>

class GenericParseTree {
public:
  using Childs = std::vector<std::unique_ptr<GenericParseTree>>;
  using NodeType = std::type_info;

  GenericParseTree(antlr4::tree::ParseTree& tree):
    type_{typeid(tree)}, childs_{} {}

  bool operator==(GenericParseTree& other) {
    if (!(type_ == other.type_)) {
      return false;
    }

    for (auto& c: childs_) {

    }

    return true;
  }

private:
  const NodeType& type_;
  Childs childs_;
};

#endif /* GENERIC_PARSETREE_H */
