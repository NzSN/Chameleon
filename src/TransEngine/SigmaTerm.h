
#ifndef SIGMATERM_H
#define SIGMATERM_H

#include <memory>
#include <iostream>
#include <string>

#include "Rewrite/Term.h"
#include "utility.h"
#include "Concepts/n_ary_tree.h"
#include "Base/generic_parsetree.h"

#include "Base/TreeLayer.h"

namespace TransEngine {

template<Base::GPTMeta T>
struct Pattern: public TreeLayer<Pattern<T>> {
  using TermID = std::string;
  using Children = std::vector<std::unique_ptr<Pattern>>;

  Pattern(const Pattern& other):
    meta_{other.meta_} {}
  Pattern(const T& meta):
    // Prevent copy children from GenericParseTree,
    // Pattern will build it's own children.
    meta_{meta} {}

  ~Pattern() {}

  bool isTermVar() const {
    // FIXME: Temporary workaround to recognize
    //        TermVar.
    switch (meta_.lang()) {
      case Base::GenericParseTree<int>::TESTLANG:
        return Utility::isTermVar(
          const_cast<T&>(meta_).getText());
      case Base::GenericParseTree<int>::WGSL:
        // Chec
        return true;
    default:
      return false;
    }
  }

  std::string termID() const {
    return const_cast<T&>(meta_).tree()->getText();
  }

  std::vector<Pattern*> termVars() {
    std::vector<Pattern*> vars =
      Concepts::NAryTree::search<Pattern>(
        *this,
        [](const Pattern& p) {
          return p.isTermVar();
        });

    return vars;
  }

  bool bind(Rewrite::Term<T> term) {
    if (!this->isTermVar()) {
      // Only nodes represent a TermVar
      // able to bind to a term.
      return false;
    }

    if (parent == nullptr) {
      /* Ignored case */
      return false;
    } else {
      const_cast<T&>(meta_).setNode(
        *(term.tree.get().getMeta().clone()));
    }

    return true;
  }

  Children& getChildren() {
    return children_;
  };

  std::optional<Pattern*> getChild(int i) {
    if (children_.size() < i) {
      return std::nullopt;
    } else {
      return children_[i].get();
    }
  }

  const T& getMeta() const {
    return meta_;
  }

  Pattern* parent;

  Pattern& addChild(std::unique_ptr<Pattern>&& child) {
    children_.push_back(std::move(child));
    return *children_.back();
  }

  Pattern* withoutHeader() {
    T* afterHeader = const_cast<T&>(meta_).withoutHeader();
    if (afterHeader == nullptr) {
      return nullptr;
    }

    std::vector<Pattern*> result =
      Concepts::NAryTree::search<Pattern>(
        *this,
        [afterHeader](const Pattern& t) {
          return &t.meta_ == afterHeader;
        });

    if (result.size() > 1 || result.size() == 0) {
      return nullptr;
    }

    return result[0];
  }

private:
  const T& meta_;
  Children children_;
};

} // TransEngine


#endif /* SIGMATERM_H */
