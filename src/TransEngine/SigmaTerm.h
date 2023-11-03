
#ifndef SIGMATERM_H
#define SIGMATERM_H

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
  using Children = std::vector<Pattern>;

  Pattern(const Pattern& other):
    meta_{other.meta_}, children_{other.children_} {}
  Pattern(const T& meta):
    // Prevent copy children from GenericParseTree,
    // Pattern will build it's own children.
    meta_{meta} {}

  bool isTermVar() const {
    return Utility::isTermVar(
      const_cast<T&>(meta_).getText());
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
    } else {
      const_cast<T&>(meta_).setNode(
        term.tree.get().getMeta().clone());
    }

    return true;
  }

  std::vector<Pattern>& getChildren() {
    return children_;
  };

  std::optional<Pattern> getChild(int i) {
    if (children_.size() < i) {
      return std::nullopt;
    } else {
      return children_[i];
    }
  }

  const T& getMeta() const {
    return meta_;
  }

  Pattern* parent;

  Pattern& addChild(Pattern t) {
    return children_.emplace_back(t);
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
