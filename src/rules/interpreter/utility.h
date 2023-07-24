#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <tuple>
#include <optional>

namespace Rules::Interpreter::Utility {

template<typename T1, typename T2>
std::optional<std::vector<std::tuple<T1, T2>>>
zip_vec(std::vector<T1>& l, std::vector<T2>& r) {
    if (l.size() != r.size()) {
        return std::nullopt;
    }

    auto iter_l = std::begin(l);
    auto iter_r = std::begin(r);

    std::vector<std::tuple<T1, T2>> zipped{};

    do {
        zipped.push_back({*iter_l, *iter_r});

        iter_l++;
        iter_r++;
    } while (iter_l != std::end(l) && iter_r != std::end(r));

    return zipped;
}

} // Rules::Interpreter::Utility

#endif /* UTILITY_H */
