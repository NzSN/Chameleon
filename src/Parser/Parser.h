
#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <string>
#include <vector>
#include "class_prop.h"
#include "Base/generic_parsetree_inl.h"

namespace Parser {

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

  template<bool IsOnHeap = false,
           typename = std::enable_if_t<!IsOnHeap>>
  static Base::GenericParseTree<A> parse(std::istream* input) {
    adapters_.emplace_back(lang, P::parse(input));
    return Base::GenericParseTree<A>::mapping(adapters_.back());
  }

  template<bool IsOnHeap = false,
           typename = std::enable_if_t<IsOnHeap>,
           int = 1>
  static std::unique_ptr<Base::GenericParseTree<A>>
  parse(std::istream* input) {
    adapters_.emplace_back(lang, P::parse(input));
    return Base::GenericParseTree<A>::template mapping<true>(adapters_.back());
  }


private:
  static std::vector<A> adapters_;

  UNINSTANTIALIZABLE(Parser);
};

} // Parser


#endif /* PARSER_H */
