#ifndef WHERECLAUSEEXPRPARSING_INL_H
#define WHERECLAUSEEXPRPARSING_INL_H

#include <type_traits>
#include "WhereClauseExprParsing.h"

namespace TransEngine::Compiler::WhereClause {

template<Base::GPTMeta T>
using Expr_uptr = std::unique_ptr<Expression::Expr<T>>;

template<Base::GPTMeta T,
         typename L>
Expr_uptr<T> toLogicalExpr_internal(P::CondExprContext* ctx)
  requires std::same_as<L, Expression::LogiOrExpr<T>> ||
           std::same_as<L, Expression::LogiAndExpr<T>>
{
  Expr_uptr<T> expr_uptr;

  return std::make_unique<L>(
    toExpr<T>(ctx->condExpr(0)), toExpr<T>(ctx->condExpr(1)));
}

template<Base::GPTMeta T>
Expr_uptr<T> toLogicalExpr(P::CondExprContext* ctx) {
  std::string OP = ctx->LOGICOP()->getText();
  if (OP == LOGI_OP_AND) {
    return toLogicalExpr_internal<T, Expression::LogiAndExpr<T>>(ctx);
  } else if (OP == LOGI_OP_OR){
    return toLogicalExpr_internal<T, Expression::LogiOrExpr<T>>(ctx);
  }
}

template<Base::GPTMeta T,
         typename O>
Expr_uptr<T> toOrderExpr_internal(P::CondExprContext* ctx)
  requires std::same_as<O, Expression::Equal<T>> ||
           std::same_as<O, Expression::LessThan<T>> ||
           std::same_as<O, Expression::LessEqual<T>> ||
           std::same_as<O, Expression::GreaterThan<T>> ||
           std::same_as<O, Expression::GreaterEqual<T>>
{
  Expr_uptr<T> expr_uptr;

  return std::make_unique<O>(
    toExpr<T>(ctx->condExpr(0)), toExpr<T>(ctx->condExpr(1)));
}

template<Base::GPTMeta T>
Expr_uptr<T> toOrderExpr(P::CondExprContext* ctx) {
  std::string OP = ctx->LOGICOP()->getText();
  if (OP == ORDER_OP_EQ) {
    return toOrderExpr_internal<
      T, Expression::Equal<T>>(ctx);
  } else if (OP == ORDER_OP_LESSTHAN) {
    return toOrderExpr_internal<
      T, Expression::LessThan<T>>(ctx);
  } else if (OP == ORDER_OP_LESSEQUAL) {
    return toOrderExpr_internal<
      T, Expression::LessEqual<T>>(ctx);
  } else if (OP == ORDER_OP_GREATERTHAN) {
    return toOrderExpr_internal<
      T, Expression::GreaterThan<T>>(ctx);
  } else if (OP == ORDER_OP_GREATEREQUAL) {
    return toOrderExpr_internal<
      T, Expression::GreaterEqual<T>>(ctx);
  }

  return nullptr;
}

template<Base::GPTMeta T>
Expr_uptr<T> toExpr(P::CondExprContext* ctx) {

  if (ctx == nullptr)
    return nullptr;

  switch (getExprType(ctx)) {
  case LOGICAL:
    return toLogicalExpr<T>(ctx);
  case ORDER:
    return toOrderExpr<T>(ctx);
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
