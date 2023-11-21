#ifndef WHERECLAUSEEXPRPARSING_INL_H
#define WHERECLAUSEEXPRPARSING_INL_H

#include <type_traits>
#include "WhereClauseExprParsing.h"

namespace TransEngine::Compiler::WhereClause {

template<Base::GPTMeta T>
using Expr_uptr = std::unique_ptr<Expression::Expr<T>>;

template<Base::GPTMeta T,
         typename L>
Expr_uptr<T> toLogicalExpr(P::CondExprContext* ctx)
  requires std::same_as<L, Expression::LogiOrExpr<T>> ||
           std::same_as<L, Expression::LogiAndExpr<T>>
{
  Expr_uptr<T> expr_uptr;

  return std::make_unique<L>(
    toExpr<T>(ctx->condExpr(0)), toExpr<T>(ctx->condExpr(1)));
}

template<Base::GPTMeta T,
         typename O>
Expr_uptr<T> toOrderExpr(P::CondExprContext* ctx)
  requires std::same_as<O, Expression::Equal<T>> ||
           std::same_as<O, Expression::Equal<T>> ||
           std::same_as<O, Expression::Equal<T>> ||
           std::same_as<O, Expression::Equal<T>> ||
           std::same_as<O, Expression::Equal<T>>
{
  Expr_uptr<T> expr_uptr;

  return std::make_unique<O>(
    toExpr<T>(ctx->condExpr(0)), toExpr<T>(ctx->condExpr(1)));
}

template<Base::GPTMeta T>
Expr_uptr<T> toExpr(P::CondExprContext* ctx) {
  switch (getExprType(ctx)) {
  case LOGICAL:
    if (ctx->LOGICOP()->getText() == "AND") {
      return toLogicalExpr<T, Expression::LogiAndExpr<T>>(ctx);
    } else {
      return toLogicalExpr<T, Expression::LogiOrExpr<T>>(ctx);
    }
    break;
  case ORDER:
    break;
  case TERM:
    break;
  case NUMBER:
    break;
  default:
    return nullptr;
  }


}

} // TransEngine::Compiler::WhereClause

#endif /* WHERECLAUSEEXPRPARSING_INL_H */
