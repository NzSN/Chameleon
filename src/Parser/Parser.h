
#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <string>
#include <vector>
#include "class_prop.h"
#include "Base/generic_parsetree_inl.h"
#include "Concepts/n_ary_tree.h"

namespace Parser {

enum TREE_PROP {
  TREE_INDEPENDENT
};

template<typename T, typename O>
concept ExtParser = requires(T t, std::istream *s) {
  { T::parse(s) } -> std::same_as<O>;
};

template<typename T, typename N>
concept NodeAdapter =
  Base::GPTMappable<T> &&
  requires(T t, int lang, N n) {
    { T(lang, n) } -> std::same_as<T>;
  };

// ExtParser is responsible for transform source
// into ParseTree. Those tree unable to directly
// used by Analyzer and Transformer in Chameleons
// so will be wrap by NodeAdapter and then mapping to
// GenericParseTree.
template<typename ExtNode,
         ExtParser<ExtNode> P,
         NodeAdapter<ExtNode> A,
         int lang>
struct Parser {

  template<Concepts::NAryTree::NAryTree T,
           Base::ALLOC_STORAGE_DURATION Storage = Base::AUTOMATIC>
  requires Base::isAutoStorage<Storage>
  static T parse(std::istream* input) {
    adapters_.emplace_back(
      std::make_unique<A>(lang, P::parse(input)));
    return T::template mapping<A, Base::AUTOMATIC>(*adapters_.back());
  }

  template<Concepts::NAryTree::NAryTree T,
           Base::ALLOC_STORAGE_DURATION Storage = Base::AUTOMATIC>
  requires Base::isDynamicStorage<Storage>
  static std::unique_ptr<T>
  parse(std::istream* input) {
    adapters_.emplace_back(
      std::make_unique<A>(lang, P::parse(input)));
    return T::template mapping<A, Base::DYNAMIC>(*adapters_.back());
  }

private:
  static std::vector<std::unique_ptr<A>> adapters_;

  UNINSTANTIALIZABLE(Parser);
};

} // Parser


#endif /* PARSER_H */
