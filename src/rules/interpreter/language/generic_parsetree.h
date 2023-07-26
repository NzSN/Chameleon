
#ifndef GENERIC_PARSETREE_H
#define GENERIC_PARSETREE_H

#include <typeinfo>
#include <ranges>
#include <tuple>
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>

//#include "antlr4-runtime.h"
#include "rules/interpreter/utility.h"

namespace Rules::Interpreter::Language {

class GenericParseTree {
public:
  using Childs = std::vector<GenericParseTree>;
  using NodeType = std::type_info;

  // GenericParseTree(antlr4::tree::ParseTree& tree) {};

  // Terminal
  GenericParseTree(const NodeType& type):
    type_{type} {}

  GenericParseTree& addChild(const NodeType& type) {
    return this->childs_.emplace_back(type);
  };

  bool operator==(const GenericParseTree& other) const {

    std::function<bool(const GenericParseTree& l,
                       const GenericParseTree& r)>
      equality_check = [&equality_check](
        const GenericParseTree& l, const GenericParseTree& r) {
        // Check node type
        if (!(l.type_ == r.type_)) {
          return false;
        }

        // Check equality of childs
        if (l.childs_.size() != r.childs_.size()) {
          return false;
        } else {
          // Terminal
          if (l.childs_.size() == 0) {
            return true;
          }

          auto zipped = Utility::zip_vector<GenericParseTree>(
            l.childs_, r.childs_);
          if (zipped.size() == 0) { return false; }

          for (auto& [thisChilds, otherChilds]: zipped) {
            if (!equality_check(thisChilds, otherChilds)) {
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
