#ifndef WHERECLAUSEEXPRPARSING_INL_H
#define WHERECLAUSEEXPRPARSING_INL_H

#include <type_traits>
#include "WhereClauseExprParsing.h"

namespace TransEngine::Compiler::WhereClause {

template<Base::GPTMeta T>
using Expr_uptr = std::unique_ptr<Expression::Expr<T>>;

/////////////////////////////////////////////////////////////////////////////
//                             Trans Functions                             //
/////////////////////////////////////////////////////////////////////////////
template<Base::GPTMeta T,
         typename L>
Expr_uptr<T> toLOGICAL_internal(P::CondExprContext* ctx)
  requires std::same_as<L, Expression::LogiOrExpr<T>> ||
           std::same_as<L, Expression::LogiAndExpr<T>>
{
  Expr_uptr<T> expr_uptr;

  return std::make_unique<L>(
    toExpr<T>(ctx->condExpr(0)), toExpr<T>(ctx->condExpr(1)));
}

template<Base::GPTMeta T>
Expr_uptr<T> toLOGICAL(P::CondExprContext* ctx) {
  std::string OP = ctx->LOGICOP()->getText();
  if (OP == Expression::LOGI_OP_AND) {
    return toLOGICAL_internal<T, Expression::LogiAndExpr<T>>(ctx);
  } else if (OP == Expression::LOGI_OP_OR){
    return toLOGICAL_internal<T, Expression::LogiOrExpr<T>>(ctx);
  }
}

template<Base::GPTMeta T, typename O>
#define REQUIREMENTS__(__E, __OP, __ENUM, __STR) \
  std::same_as<O, Expression::__E<T>> ||
// Workaround to prevent syntax error in REQUIREMENTS__
#define REQUIREMENTS ORDER_EXPRS_LIST(REQUIREMENTS__) true

requires REQUIREMENTS

#undef REQUIREMENTS
#undef REQUIREMENTS__

Expr_uptr<T> toORDER_internal(P::CondExprContext* ctx)
{
  Expr_uptr<T> expr_uptr;

  return std::make_unique<O>(
    toExpr<T>(ctx->condExpr(0)), toExpr<T>(ctx->condExpr(1)));
}

template<Base::GPTMeta T>
Expr_uptr<T> toORDER(P::CondExprContext* ctx) {

  std::string OP = ctx->ORDEROP()->getText();

#define TRANS_TO_EXPRS(__E, __OP, __ENUM, __STR)               \
  if (OP == Expression::__STR) {                               \
    return toORDER_internal<T, Expression::__E<T>>(ctx);   \
  }

  ORDER_EXPRS_LIST(TRANS_TO_EXPRS);
#undef TRANS_TO_EXPRS

  return nullptr;
}

template<Base::GPTMeta T>
Expr_uptr<T> toTERM(P::CondExprContext* ctx) {

  return nullptr;
}

template<Base::GPTMeta T>
Expr_uptr<T> toNUMBER(P::CondExprContext* ctx) {
  return nullptr;
}

// Interface to outer world
template<Base::GPTMeta T>
Expr_uptr<T> toExpr(P::CondExprContext* ctx) {

  if (ctx == nullptr)
    return nullptr;

  Expression::ExprType type = Expression::getExprType(ctx);

#define TRANS_EXPR(__E)                         \
    if (type == Expression::__E) {              \
      return to##__E<T>(ctx);                   \
    }

  EXPR_LIST(TRANS_EXPR);
#undef HANDLE_EXPR

  return nullptr;
}

} // TransEngine::Compiler::WhereClause

#endif /* WHERECLAUSEEXPRPARSING_INL_H */
