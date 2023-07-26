
#ifndef GENERIC_PARSETREE_H
#define GENERIC_PARSETREE_H

#include <typeinfo>
#include <ranges>
#include <tuple>
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>
#include "antlr4-runtime.h"
#include "rules/interpreter/utility.h"

namespace Rules::Interpreter::Language {

class GenericParseTree {
public:

  enum SUPPORTED_LANGUAGE {
    MINIMUM_LANG_INDEX = 0,
    TYPESCRIPT = 0,
    CPP = 1,
    NUM_OF_LANG_SUPPORTED,
  };

  using Childs = std::vector<GenericParseTree>;
  using NodeType = std::type_info;
  using CharPosition = std::tuple<int, int>;

  template<typename T>
  constexpr static auto getRow = std::get<0, T>;

  template<typename T>
  constexpr static auto getColumn = std::get<0, T>;

  GenericParseTree fromAntlr4(antlr4::tree::ParseTree& tree,
                              SUPPORTED_LANGUAGE lang);

  // The type_ field should be re-assign by a new
  // typeinfo in later construction.
  GenericParseTree(): type_{typeid(void)} {}
  // Terminal
  GenericParseTree(const NodeType& type):
    type_{type} {}

  GenericParseTree& addChild(const NodeType& type) {
    return this->childs_.emplace_back(type);
  };

  bool operator==(const GenericParseTree& other) const {

    // GenericParseTree is recursive type which requrie that
    // equality check should be recursive too.
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

  CharPosition getStartPos() const {
    return std::get<0>(positions);
  }

  CharPosition getEndPos() const {
    return std::get<1>(positions);
  }

private:
  const NodeType& type_;
  Childs childs_;
  // (pos of fisrt char, pos of last char)
  std::tuple<CharPosition, CharPosition> positions;
};

} // Rules::Interpreter::Language

#endif /* GENERIC_PARSETREE_H */
