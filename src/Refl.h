#ifndef REFL_H
#define REFL_H

#include <array>
#include <functional>
#include <any>
#include <optional>
#include <stdexcept>

namespace Utility {
namespace Refl {

#define Stringify(...) #__VA_ARGS__
constexpr const unsigned MAXIMUM_CLASSNAME = 256;
constexpr unsigned NUM_OF_REFLECTS = 100;

template<std::size_t N>
struct ConstStr {

  ConstStr() = default;

  template<std::size_t M>
  constexpr ConstStr(const char (&other)[M]) {
    if (N < M) {
      throw std::runtime_error("...");
    }

    reset();
    for (unsigned i = 0; i < M; ++i) {
      data[i] = other[i];
    }
  }

  template<std::size_t M>
  constexpr ConstStr& operator=(const char (&other)[M]) {
    if (N < M) {
      return *this;
    }

    reset();
    for (unsigned i = 0; i < M; ++i) {
      data[i] = other[i];
    }

    return *this;
  }

  constexpr void reset() {
    for (unsigned i = 0; i < N; ++i) {
      data[i] = 0;
    }
  }

  char data[N+1];
};

template<std::size_t N>
class Refl {
public:
  using Constructor = std::any (*)(std::optional<std::any>);
  struct TypeInfo {
    ConstStr<MAXIMUM_CLASSNAME> className;
    Constructor ctor;
  };

  template<std::size_t M>
  static constexpr bool addReflectType(
    const char (&name)[M], Constructor ctor) {

    if (!(idx < N)) {
      return false;
    }

    TypeInfo info{name, ctor};
    all[idx++] = info;
    return true;
  }

  template<typename T>
  static constexpr T reflect(std::string name) {
    return std::any_cast<T>(all[0].ctor(std::nullopt));
  }

private:
  static unsigned idx;
  static std::array<TypeInfo, N> all;
};

template<size_t N>
unsigned Refl<N>::idx = 0;

template<size_t N>
std::array<typename Refl<N>::TypeInfo, N>
Refl<N>::all = {};

using DefaultRefl = Refl<NUM_OF_REFLECTS>;

} // Refl
} // Utility

#endif /* REFL_H */
