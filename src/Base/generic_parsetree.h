
#ifndef GENERIC_PARSETREE_H
#define GENERIC_PARSETREE_H

#include <ranges>
#include <tuple>
#include <vector>
#include <concepts>
#include <functional>

#include "Language/language.h"
#include "Concepts/n_ary_tree.h"
#include "utility.h"

namespace Base {

/////////////////////////////////////////////////////////////////////////////
//                                 Concepts                                //
/////////////////////////////////////////////////////////////////////////////
template<typename T>
concept GPTMeta = std::equality_comparable<T>;

using CharPosition = std::tuple<int, int>;
using SrcRange = std::tuple<CharPosition, CharPosition>;
template<typename T>
concept GPTMappable =
  GPTMeta<T> &&
  Concepts::NAryTree::NAryTree<T> &&
  requires(T t) {
    // Source information
    { t.sourceRange() } -> std::same_as<SrcRange>;
};


/////////////////////////////////////////////////////////////////////////////
//                             GenericParseTree                            //
/////////////////////////////////////////////////////////////////////////////
template<GPTMeta T>
class GenericParseTree {
public:
  enum SUPPORTED_LANGUAGE {
    MINIMUM_LANG_INDEX = 0,
    TYPESCRIPT = 0,
    CPP = 1,
    // Testing purposes
    TESTLANG = 2,
    NUM_OF_LANG_SUPPORTED,
  };

  using Childs = std::vector<GenericParseTree>;
  using GPTIterator = Childs::iterator;

  // Terminal
  GenericParseTree(T* meta):
    meta_{meta}, metaRef{&meta} {}
  GenericParseTree(const T& meta):
    meta_{&meta}, metaRef{meta} {}

  GenericParseTree& addChild(GenericParseTree type) {
    return childs_.emplace_back(type);
  };

  std::vector<GenericParseTree>& getChildren() {
    return childs_;
  };

  std::optional<GenericParseTree&> getChild(int i) {
    if (childs_.size() < i) {
      return std::nullopt;
    } else {
      return childs_[i];
    }
  }

  bool operator==(const GenericParseTree& other) const;

  GenericParseTree* select(
    std::function<bool(GenericParseTree&)> predicate);

  void traverse(
    std::function<bool(GenericParseTree&)> proc);

  CharPosition getStartPos() const {
    return std::get<0>(positions);
  }

  CharPosition getEndPos() const {
    return std::get<1>(positions);
  }

  std::string getText() {
    if (meta_ == nullptr) return {};
    return const_cast<T*>(meta_)->tree()->getText();
  }

  // Chameleons are based on exist parsers. Exist parsers
  // don't use GenericParseTree, so we have to provide a generic
  // way to allow mapping between parsetree generated by exist
  // parsers and GenericParseTree.
  //
  // You can treat mapping as a functor mapping between
  // GenericParseTree and another ParseTree.
  template<bool IsOnHeap = false,
           typename = std::enable_if_t<!IsOnHeap>>
  static GenericParseTree<T> mapping(const T& o)
  requires GPTMappable<T>;

  template<bool IsOnHeap = false,
           typename = std::enable_if_t<IsOnHeap>,
           int = 1>
  static std::unique_ptr<GenericParseTree<T>>
  mapping(const T& o)
  requires GPTMappable<T>;


private:
  friend struct GenericParseTreeTest;
  // GenericParseTree does not owning resource
  // of a specific tree which contain metainfo
  // of sentence, just let the type to be T* .
  const T* meta_;
  const T& metaRef;

  Childs childs_;
  // (pos of fisrt char, pos of last char)
  SrcRange positions;
};

} // Base

#endif /* GENERIC_PARSETREE_H */
