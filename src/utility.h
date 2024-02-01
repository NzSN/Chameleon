#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <tuple>
#include <optional>
#include <concepts>
#include <ranges>
#include <concepts>
#include <functional>
#include <type_traits>

#include "Base/langs.h"
#include "antlr4-runtime.h"

#include "Base/config.h"

namespace Utility {

struct CallAtExit {
  CallAtExit(std::function<void()> f) {
    f_ = f;
  }

  ~CallAtExit() {
    f_();
  }

private:
  std::function<void()> f_;
};

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
    inputSStream{sentences},
    inputStream{inputSStream},
    input{inputSStream},
    tokens{&lexer},
    lexer{&input},
    parser{&tokens} {

    tree = (parser.*(entry))();
  }

  Antlr4ParseEnv(std::istream& istream, Entry entry):
    inputStream(istream),
    input{inputStream},
    tokens{&lexer},
    lexer{&input},
    parser{&tokens} {

    tree = (parser.*(entry))();
  }

  /* Caution: Order is important here, don't
   *          change the order of those declarations
   *          unless you know what you are doing. */
  std::istringstream inputSStream;
  std::istream& inputStream;
  antlr4::ANTLRInputStream input;
  antlr4::CommonTokenStream tokens;
  Lexer lexer;
  Parser parser;
  // This object is managed by Parser
  // so it's already owned.
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

template<std::derived_from<antlr4::Lexer> Lexer,
         std::derived_from<antlr4::Parser> Parser,
         typename Entry>
Antlr4ParseEnvUniquePtr<Lexer, Parser, Entry>
Antlr4_GenParseTree(std::istream& stream, Entry entry) {
  return std::make_unique<
    Antlr4ParseEnv<Lexer, Parser, Entry>>(stream, entry);
}


std::string testLangRandomExpr(unsigned numOfOperands);

std::string gen_random(const int len);


// Type-Erasure Wrapper
struct TypeErasureWrapper {
  template<typename _Ty>
  TypeErasureWrapper(_Ty src): _inner(new inner<_Ty>(std::forward<_Ty>(src))) {}

  struct inner_base {
    using ptr = std::unique_ptr<inner_base>;
    virtual ~inner_base() {}
  };
  template<typename _Ty> struct inner: inner_base {
    inner(_Ty& newval): _value(newval) {}
    inner(_Ty&& newval): _value(std::move(newval)) {}
  private:
    _Ty _value;
  };

private:
  typename inner_base::ptr _inner;
};

// Wrapper to hold all heap allocated resources that
// used by Environment.
struct HeapResourceHolder: public Utility::TypeErasureWrapper {
  template<typename T>
  HeapResourceHolder(T& t):
    Utility::TypeErasureWrapper{t} {}
  template<typename T>
  HeapResourceHolder(T&& t):
    Utility::TypeErasureWrapper{std::move(t)} {}
};

} // Utility

/////////////////////////////////////////////////////////////////////////////
//                               Type Traits                               //
/////////////////////////////////////////////////////////////////////////////
namespace Utility {

template<typename T>
struct is_derefable {
  template<typename U>
  static constexpr std::true_type check(decltype(&U::operator*));

  template<typename>
  static constexpr std::false_type check(...);

  typedef decltype(check<T>(0)) type;

  static constexpr bool value = type::value;
};

template<typename T>
struct is_arrow {
  template<typename U>
  static constexpr std::true_type check(decltype(&U::operator->));

  template<typename>
  static constexpr std::false_type check(...);

  typedef decltype(check<T>(0)) type;

  static constexpr bool value = type::value;
};

template<typename T>
concept Hashable = requires(T a) {
  { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

} // Utility

/////////////////////////////////////////////////////////////////////////////
//                              Code Snippets                              //
/////////////////////////////////////////////////////////////////////////////
namespace Utility {} // Utility


/////////////////////////////////////////////////////////////////////////////
//                            Category Concepts                            //
/////////////////////////////////////////////////////////////////////////////

namespace Utility {

template<template<typename X> class F, typename T>
struct Functor {
  Functor(T a_): a{a_} {}

  virtual std::function<F<T>(F<T>)>
  operator()(std::function<T(T)> f) const = 0;

  T a;
};
} // Utility

/////////////////////////////////////////////////////////////////////////////
//                                  CONFIG                                 //
/////////////////////////////////////////////////////////////////////////////
namespace Utility {

template<typename T>
struct TypeMapping {
  using type = T;
};


} // Utility

///////////////////////////////////////////////////////////////////////////////
//                             Compile Time Stuff                            //
///////////////////////////////////////////////////////////////////////////////
namespace Utility {

template<typename T, typename F>
requires std::invocable<F, T>
void for_loop(F f) {}

template<typename T, typename F, T arg, T... args>
requires std::invocable<F, T>
void for_loop(F f) {
  f(arg);
  for_loop<T, F, args...>(f);
}

template<typename T, template<T t> typename F>
void for_loop() {}

template<typename T, template<T t> typename F, T arg, T... args>
void for_loop() {
  F<arg>();
  for_loop<T, F, args...>();
}

} // Utility

#endif /* UTILITY_H */
