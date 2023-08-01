#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <tuple>
#include <optional>
#include <concepts>
#include <ranges>
#include <concepts>
#include <functional>

#include "antlr4-runtime.h"

namespace Rules::Interpreter::Utility {

template<typename T, typename E>
concept RangeTuple = std::ranges::range<T> &&
  requires(T t, std::tuple<E, E> pair) {
    t.push_back(pair);
};

template<typename T, typename E>
concept Range = std::ranges::range<T>;

template<typename E, RangeTuple<E> RT, Range<E> T>
RT zip(T l, T r) {
  if (l.size() != r.size()) {
    return RT{};
  }

  RT zipped{};
  auto iter_l = std::begin(l);
  auto iter_r = std::begin(r);

  while (iter_l != std::end(l)) {
    zipped.push_back({*iter_l, *iter_r});

    ++iter_l;
    ++iter_r;
  }

    return zipped;
}

template<typename T>
const auto& zip_vector =
  zip<T, std::vector<std::tuple<T, T>>, const std::vector<T>&>;

template<std::derived_from<antlr4::Lexer> Lexer,
         std::derived_from<antlr4::Parser> Parser,
         typename Entry>
std::string Antlr4_GenParseTree(
  std::string sentences, Entry entry) {

  std::stringstream ss(sentences);
  antlr4::ANTLRInputStream input(ss);
  Lexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  Parser parser(&tokens);

  antlr4::tree::ParseTree* tree = (parser.*(entry))();
  return tree->toStringTree(&parser);
}

} // Rules::Interpreter::Utility

#endif /* UTILITY_H */
