#ifndef WHERECLAUSEEXPRPARSING_INL_H
#define WHERECLAUSEEXPRPARSING_INL_H

#include <type_traits>
#include "WhereClauseExprParsing.h"

namespace TransEngine::Compiler::WhereClause {

using Expr_uptr = std::unique_ptr<Expression::Expr>;

#define DEFINE_PARSING_FUNCTION(EXPR_TYPE) \
  inline Expr_uptr to##EXPR_TYPE(P::CondExprContext* ctx)

#define CALL_PARSING_FUNCTION(EXPR_TYPE, CTX_PTR) \
  to##EXPR_TYPE(CTX_PTR)


/////////////////////////////////////////////////////////////////////////////
//                             Trans Functions                             //
/////////////////////////////////////////////////////////////////////////////
template<typename L>
Expr_uptr toLOGICAL_internal(P::CondExprContext* ctx)
  requires std::same_as<L, Expression::LogiOrExpr> ||
           std::same_as<L, Expression::LogiAndExpr>
{
  Expr_uptr expr_uptr;

  return std::make_unique<L>(
    toExpr(ctx->condExpr(0)), toExpr(ctx->condExpr(1)));
}

DEFINE_PARSING_FUNCTION(LOGICAL) {
  std::string OP = ctx->LOGICOP()->getText();
  if (OP == Expression::LOGI_OP_AND) {
    return toLOGICAL_internal<Expression::LogiAndExpr>(ctx);
  } else if (OP == Expression::LOGI_OP_OR){
    return toLOGICAL_internal<Expression::LogiOrExpr>(ctx);
  }

  return nullptr;
}

template<typename O>
#define REQUIREMENTS__(__E, __OP, __ENUM, __STR, __VT) \
  std::same_as<O, Expression::__E> ||
// Workaround to prevent syntax error in REQUIREMENTS__
#define REQUIREMENTS ORDER_EXPRS_LIST(REQUIREMENTS__) true

requires REQUIREMENTS

#undef REQUIREMENTS
#undef REQUIREMENTS__

Expr_uptr toORDER_internal(P::CondExprContext* ctx)
{
  Expr_uptr expr_uptr;

  return std::make_unique<O>(
    toExpr(ctx->condExpr(0)), toExpr(ctx->condExpr(1)));
}

DEFINE_PARSING_FUNCTION(ORDER) {

  std::string OP = ctx->ORDEROP()->getText();

#define TRANS_TO_EXPRS(__E, __OP, __ENUM, __STR, __VT) \
  if (OP == Expression::__STR) {                       \
    return toORDER_internal<Expression::__E>(ctx);     \
  }

  ORDER_EXPRS_LIST(TRANS_TO_EXPRS);
#undef TRANS_TO_EXPRS

  return nullptr;
}

DEFINE_PARSING_FUNCTION(TERM) {

  return nullptr;
}

DEFINE_PARSING_FUNCTION(CONSTANT) {
  return nullptr;
}

// Interface to outer world
inline Expr_uptr toExpr(P::CondExprContext* ctx) {

  if (ctx == nullptr)
    return nullptr;

  Expression::ExprType type = Expression::getExprType(ctx);

#define TRANS_EXPR(__E)                              \
  if (type == Expression::__E) {                     \
    return CALL_PARSING_FUNCTION(__E, ctx);          \
  }

  EXPR_LIST(TRANS_EXPR);
#undef HANDLE_EXPR

  return nullptr;
}

#undef DEFINE_PARSING_FUNCTION

} // TransEngine::Compiler::WhereClause

#endif /* WHERECLAUSEEXPRPARSING_INL_H */
