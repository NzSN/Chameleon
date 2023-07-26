#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <tuple>
#include <optional>
#include <concepts>
#include <ranges>

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

    auto iter_l = std::begin(l);
    auto iter_r = std::begin(r);

    RT zipped{};

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

} // Rules::Interpreter::Utility

#endif /* UTILITY_H */
