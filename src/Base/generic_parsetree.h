
#ifndef GENERIC_PARSETREE_H
#define GENERIC_PARSETREE_H

#include <type_traits>
#include <memory>
#include <ranges>
#include <tuple>
#include <vector>
#include <concepts>
#include <functional>

#include "Concepts/n_ary_tree.h"
#include "utility.h"
#include "TreeLayer.h"

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
    { t.getText() } -> std::same_as<std::string>;
    { t.setNode(t) } -> std::same_as<bool>;
};


/////////////////////////////////////////////////////////////////////////////
//                             GenericParseTree                            //
/////////////////////////////////////////////////////////////////////////////
template<GPTMeta T>
class GenericParseTree: public TreeLayer<GenericParseTree<T>> {
public:
  enum SUPPORTED_LANGUAGE {
    MINIMUM_LANG_INDEX = 0,
    TYPESCRIPT = 0,
    CPP = 1,
    // Testing purposes
    TESTLANG = 2,
    WGSL = 3,
    NUM_OF_LANG_SUPPORTED,
  };

  using Childs = std::vector<std::unique_ptr<GenericParseTree>>;
  using GPTIterator = Childs::iterator;

  // Terminal
  GenericParseTree(const T& meta):
    parent{nullptr}, metaRef{meta} {}
  GenericParseTree(const GenericParseTree& other):
    metaRef(other.metaRef) {

    for (auto& c: other.childs_) {
      this->addChild(
        std::make_unique<GenericParseTree>(*c));
    }
  }

  GenericParseTree& addChild(
    std::unique_ptr<GenericParseTree>&& child) {
    child->parent = this;
    childs_.push_back(std::move(child));
    return *childs_.back();
  }

  GenericParseTree* parent;

  Childs& getChildren() {
    return childs_;
  };

  std::optional<GenericParseTree*> getChild(int i) {
    if (childs_.size() < i) {
      return std::nullopt;
    } else {
      return childs_[i].get();
    }
  }

  bool operator==(const GenericParseTree& other) const;

  GenericParseTree* select(
    std::function<bool(GenericParseTree&)> predicate);

  void traverse(
    std::function<bool(GenericParseTree&)> proc);

  // This procedure require modification to
  // underlaying tree.
  // Only when T is NAryTree with setNode().
  bool setNode(const GenericParseTree& other)
    requires Concepts::NAryTree::NAryTree<T> &&
             requires(T t, const T arg) {
               { t.setNode(arg) } -> std::convertible_to<bool>;
             }
  {
    return const_cast<T&>(metaRef).setNode(other.getMeta());
  }

  // For convenience, GenericParseTree will require that
  //
  std::string getText() const {
    return const_cast<T&>(metaRef).getText();
  }

  SrcRange getPos() {
    return metaRef.sourceRange();
  }

  const T& getMeta() const {
    return metaRef;
  }

private:
  friend struct GenericParseTreeTest;
  const T& metaRef;

  Childs childs_;
};

} // Base

#endif /* GENERIC_PARSETREE_H */
