
#ifndef GENERIC_PARSETREE_H
#define GENERIC_PARSETREE_H

#include <typeinfo>
#include <ranges>
#include <tuple>
#include <memory>
#include <vector>
#include <functional>

#include "antlr4-runtime.h"
#include "rules/interpreter/utility.h"

namespace Rules::Interpreter::Language {

class GenericParseTree {
public:
  using Childs = std::vector<std::unique_ptr<GenericParseTree>>;
  using NodeType = std::type_info;

  GenericParseTree(antlr4::tree::ParseTree& tree);

  bool operator==(GenericParseTree& other) {

    std::function<bool(GenericParseTree& l,
                       GenericParseTree& r)>
      equality_check;
    equality_check = [&equality_check](GenericParseTree& l, GenericParseTree& r) {
      // Check node type
      if (!(l.type_ == r.type_)) {
        return false;
      }

      // Check equality of childs
      if (l.childs_.size() != r.childs_.size()) {
        return false;
      } else {
        auto zipped = Utility::zip_vec(l.childs_, r.childs_);
        if (!zipped.has_value()) { return false; }
        for (auto& [thisChilds, otherChilds]: zipped.value()) {
          if (!equality_check(*thisChilds, *otherChilds)) {
            return false;
          }
        }
        return true;
      }
    };

    return equality_check(*this, other);
  }

private:
  const NodeType& type_;
  Childs childs_;
};

} // Rules::Interpreter::Language

#endif /* GENERIC_PARSETREE_H */
