
#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <string>
#include "Base/generic_parsetree_inl.h"

namespace Parser {

template<typename T, typename O>
concept ExtParser = requires(T t, std::istream input) {
  { T::parse(input) } -> std::same_as<O>;
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
// so will be wrap by ExtNode and then mapping to
// GenericParseTree.
template<typename ExtNode,
         ExtParser<ExtNode> P,
         NodeAdapter<ExtNode> A,
         int lang>
class Parser {
public:
  static Base::GenericParseTree<ExtNode> parse(std::istream input) {
    return Base::GenericParseTree<A>(
      A{lang, P::parse(input)});
  }

private:
  Parser() = default;
};

} // Parser


#endif /* PARSER_H */
