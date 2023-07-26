
#ifndef GENERIC_PARSETREE_H
#define GENERIC_PARSETREE_H

#include <typeinfo>
#include <ranges>
#include <tuple>
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>
#include <concepts>
#include "antlr4-runtime.h"
#include "ColorTalk/interpreter/utility.h"

namespace Rules::Interpreter::Language {

template<std::equality_comparable T>
class GenericParseTree {
public:

  enum SUPPORTED_LANGUAGE {
    MINIMUM_LANG_INDEX = 0,
    TYPESCRIPT = 0,
    CPP = 1,
    NUM_OF_LANG_SUPPORTED,
  };

  using Childs = std::vector<GenericParseTree>;
  using CharPosition = std::tuple<int, int>;
  using GPTIterator = Childs::iterator;

  template<typename POS = int>
  constexpr static auto getRow = std::get<0, POS>;

  template<typename POS = int>
  constexpr static auto getColumn = std::get<0, POS>;

  GenericParseTree fromAntlr4(antlr4::tree::ParseTree& tree,
                              SUPPORTED_LANGUAGE lang);

  // Terminal
  GenericParseTree(T type):
    type_{type} {}

  GenericParseTree& addChild(T type) {
    return childs_.emplace_back(type);
  };

  GPTIterator childs() const {
    return std::begin(childs_);
  }

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

  GenericParseTree* select(
    std::function<bool(GenericParseTree&)> predicate) {

    GenericParseTree* tree = NULL;
    traverse([&](GenericParseTree& node) {
      if (predicate(node)) {
        tree = &node;
        return false;
      } else {
        return true;
      }
    });

    return tree;
  }

  void traverse(
    std::function<bool(GenericParseTree&)> proc) {

    if (!proc(*this)) return;
    for (auto& c: childs_) {
      c.traverse(proc);
    }
  }

  CharPosition getStartPos() const {
    return std::get<0>(positions);
  }

  CharPosition getEndPos() const {
    return std::get<1>(positions);
  }

private:
  friend struct GenericParseTreeTest;
  T type_;
  Childs childs_;
  // (pos of fisrt char, pos of last char)
  std::tuple<CharPosition, CharPosition> positions;
};

} // Rules::Interpreter::Language

#endif /* GENERIC_PARSETREE_H */
