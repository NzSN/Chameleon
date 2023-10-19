#ifndef EXPRTREE_H
#define EXPRTREE_H

#include <memory>
#include <concepts>
#include <optional>
#include <type_traits>

namespace Utility {

template<
  typename OP,
  typename LEAF,
  typename R,
  typename = std::enable_if_t<std::is_invocable_r_v<R, OP, LEAF, LEAF>>,
  typename... ARGS>
class BinExprTree {
public:
  enum NodeType {
    OPERATOR,
    OPERAND
  };

  // nullopt indicate that evaluate is failed.
  std::optional<R> operator()(ARGS... args) {
    if (type_ == OPERATOR) {

      std::optional<R> loperand = std::nullopt;
      std::optional<R> roperand = std::nullopt;

      for (auto& [e, o]: {{lhs_, loperand}, {rhs_, roperand}}) {
        if (!e == nullptr) {
          o = (*e)(args...);
          if (!o.has_value()) {
            return std::nullopt;
          }
        }
      }

      return op_(loperand.value(), roperand.value());
    } if (type_ == OPERAND) {
      if (std::is_invocable_r_v<R, LEAF, ARGS...>) {
        return v_(args...);
      } else {
        /* The leaf is an first-order term, can only be
         * evaluated in another context, just return it. */
        if (!std::is_convertible_v<LEAF, R>) {
          return std::nullopt;
        } else {
          return v_;
      }
      }
    }
  };

private:
  NodeType type_;
  OP op_;
  LEAF v_;
  std::unique_ptr<BinExprTree> lhs_;
  std::unique_ptr<BinExprTree> rhs_;
};

} // Utility

#endif /* EXPRTREE_H */
