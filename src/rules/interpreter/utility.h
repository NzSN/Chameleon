#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <tuple>
#include <optional>
#include <concepts>
#include <ranges>

namespace Rules::Interpreter::Utility {

template<typename T, typename E>
concept RangeAndPusable = std::ranges::range<T> && requires(T t, E e) {
  t.push_back(e);
};

template<typename E, RangeAndPusable<E> T, RangeAndPusable<E> RT>
RT zip_vec(T l, T r) {
    if (l.size() != r.size()) {
        return std::nullopt;
    }

    auto iter_l = std::begin(l);
    auto iter_r = std::begin(r);

    RT zipped{};

    do {
        zipped.push_back({*iter_l, *iter_r});

        iter_l++;
        iter_r++;
    } while (iter_l != std::end(l) && iter_r != std::end(r));

    return zipped;
}

} // Rules::Interpreter::Utility

#endif /* UTILITY_H */
