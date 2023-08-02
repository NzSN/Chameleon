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

namespace Utility {

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


template<std::derived_from<antlr4::Lexer> Lexer,
         std::derived_from<antlr4::Parser> Parser,
         typename Entry>
struct Antlr4ParseEnv {
  Antlr4ParseEnv(std::string sentences, Entry entry):
    inputStream{sentences},
    input{inputStream},
    tokens{&lexer},
    lexer{&input},
    parser{&tokens} {

    tree = (parser.*(entry))();
  }

  /* Caution: Order is important here, don't
   *          change the order of those declarations
   *          unless you know what you are doing. */
  std::istringstream inputStream;
  antlr4::ANTLRInputStream input;
  antlr4::CommonTokenStream tokens;
  Lexer lexer;
  Parser parser;
  antlr4::tree::ParseTree* tree;
};

template<typename T>
const auto& zip_vector =
  zip<T, std::vector<std::tuple<T, T>>, const std::vector<T>&>;

template<std::derived_from<antlr4::Lexer> Lexer,
         std::derived_from<antlr4::Parser> Parser,
         typename Entry>
using Antlr4ParseEnvUniquePtr = std::unique_ptr<Antlr4ParseEnv<Lexer, Parser, Entry>>;

template<std::derived_from<antlr4::Lexer> Lexer,
         std::derived_from<antlr4::Parser> Parser,
         typename Entry>
Antlr4ParseEnvUniquePtr<Lexer, Parser, Entry>
Antlr4_GenParseTree(std::string sentences, Entry entry) {
  return std::make_unique<
    Antlr4ParseEnv<Lexer, Parser, Entry>>(sentences, entry);
}

} // Utility

#endif /* UTILITY_H */
