
#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <string>
#include <vector>
#include "class_prop.h"
#include "Base/generic_parsetree_inl.h"
#include "Base/Concepts/n_ary_tree.h"

#include "ExternalParser.h"

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
// ParseTree.
template<Base::isLangType L>
struct Parser {

  using Adapter = typename ParseArg<L>::Adapter;

  template<Concepts::NAryTree::NAryTree T,
           Base::ALLOC_STORAGE_DURATION Storage = Base::AUTOMATIC>
  requires Base::isAutoStorage<Storage>
  static T parse(std::istream* input) {
    adapters_.emplace_back(
      std::make_unique<Adapter>(
        L::typeEnum, ExternalParser<L>::parse(input)));
    return T::template mapping<Adapter, Base::AUTOMATIC>(*adapters_.back());
  }

  template<Concepts::NAryTree::NAryTree T,
           Base::ALLOC_STORAGE_DURATION Storage = Base::AUTOMATIC>
  requires Base::isDynamicStorage<Storage>
  static std::unique_ptr<T>
  parse(std::istream* input) {
    adapters_.emplace_back(
      std::make_unique<Adapter>(L::typeEnum,
                                ExternalParser<L>::parse(input)));
    return T::template mapping<Adapter, Base::DYNAMIC>(*adapters_.back());
  }

private:
  static std::vector<std::unique_ptr<Adapter>> adapters_;

  UNINSTANTIALIZABLE(Parser);
};

} // Parser


#endif /* PARSER_H */
