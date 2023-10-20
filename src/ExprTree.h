#ifndef EXPRTREE_H
#define EXPRTREE_H

#include <memory>
#include <concepts>
#include <optional>
#include <type_traits>
#include <tuple>

namespace Utility {
namespace {template<
  typename V,
  typename R,
  typename... ARGS,
  typename = std::enable_if_t<std::is_invocable_r_v<R, V, ARGS...>>>
R evaluate(V v, ARGS... args) {
  return v(args...);
}

template<
  typename V,
  typename R,
  typename... ARGS,
  typename = std::enable_if_t<!std::is_invocable_r_v<R, V, ARGS...>>,
  int = 0>
R evaluate(V v, ARGS... args) {
  return v;
}
}

template<typename T, typename R, typename... ARGS>
concept NullaryOrPrimitive =
  std::is_fundamental_v<T> ||
  requires(T t, ARGS... args) {
  { t(args...) } -> std::same_as<R>;
  };

template<typename T, typename ARG, typename... ARGS>
concept BinOP =
  requires(T t,
           std::optional<ARG> arg1,
           std::optional<ARG> arg2,
           ARGS... args) {
  { t(arg1, arg2, args...) } -> std::same_as<ARG>;
};

template<
  typename R,
  typename LEAF,
  typename OP,
  typename... ARGS>
requires BinOP<OP, R, ARGS...> &&
         NullaryOrPrimitive<LEAF, R, ARGS...>

class BinExprTree {
public:
  enum NodeType {
    OPERATOR,
    OPERAND
  };

  using T_OP__ = std::unique_ptr<OP>;
  using T_CHILD__ = std::unique_ptr<BinExprTree>;

  BinExprTree() = default;
  BinExprTree(NodeType type, LEAF v):
    type_{type}, op_{nullptr},
    v_{v}, lhs_{nullptr}, rhs_{nullptr} {}
  BinExprTree(NodeType type, std::unique_ptr<OP> op):
    type_{type}, op_{std::move(op)},
    v_{}, lhs_{nullptr}, rhs_{nullptr} {}

  void setL(std::unique_ptr<BinExprTree> t) {
    lhs_ = std::move(t);
  }
  void setR(std::unique_ptr<BinExprTree> t) {
    rhs_ = std::move(t);
  }

  // nullopt indicate that evaluate is failed.
  std::optional<R> operator()(ARGS... args) {
    if (type_ == OPERATOR) {

      std::optional<R> loperand = std::nullopt;
      std::optional<R> roperand = std::nullopt;

      auto t1 = std::tie(lhs_, loperand);
      auto t2 = std::tie(rhs_, roperand);
      for (auto& [e, o]: {t1, t2}) {
        if (!(e == nullptr)) {
          std::optional<R> tmp = (*e)(args...);
          if (!tmp.has_value()) {
            return std::nullopt;
          } else {
            o = tmp;
          }
        }
      }

      if (!loperand.has_value() && !roperand.has_value()) {
        return std::nullopt;
      }

      return (*op_)(loperand, roperand, args...);
    } else {
      if (!std::is_convertible_v<LEAF, R>) {
        return std::nullopt;
      } else {
        return evaluate<LEAF,R>(v_, args...);
      }
    }
  }

private:
  NodeType type_;
  std::unique_ptr<OP> op_;
  LEAF v_;
  std::unique_ptr<BinExprTree> lhs_;
  std::unique_ptr<BinExprTree> rhs_;
};

} // Utility

#endif /* EXPRTREE_H */
