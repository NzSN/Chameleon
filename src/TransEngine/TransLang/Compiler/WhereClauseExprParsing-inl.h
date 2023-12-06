#ifndef WHERECLAUSEEXPRPARSING_INL_H
#define WHERECLAUSEEXPRPARSING_INL_H

#include <vector>
#include <type_traits>
#include "Refl.h"
#include "WhereClauseExprParsing.h"

#include "TransEngine/TransLang/ChameleonsParser.h"

namespace TransEngine::Compiler::WhereClause {

using Expr_uptr = std::unique_ptr<Expression::Expr>;

#define DEFINE_PARSING_FUNCTION(EXPR_TYPE)                            \
  /* Make sure type of EXPR_TYPE is Expression::ExprTYpe */           \
  template<Expression::ExprType T = Expression::EXPR_TYPE>            \
  inline Expr_uptr to##EXPR_TYPE(P::CondExprContext* ctx)

#define CALL_PARSING_FUNCTION(EXPR_TYPE, CTX_PTR) \
  to##EXPR_TYPE(CTX_PTR)

#define PENDING_TO_IMPL throw std::runtime_error(\
    std::string(__FUNCTION__) + "() IS NOT IMPLEMENT (" \
    __FILE__ + ":" + std::to_string(__LINE__) + ")" )

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

  return toExpr(ctx->condExpr(0)), toExpr(ctx->condExpr(1));
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

// An expression that reference to Term reside
// in Environment.
DEFINE_PARSING_FUNCTION(TERM) {
  if (!ctx->term()) { return nullptr; }

  std::string identifier;
  if (ctx->term()->WHERE_IDENTIFIER()) {
    identifier = ctx->term()->WHERE_IDENTIFIER()->getText();
  }

  return std::make_unique<Expression::TermRef>(
    identifier);
}

DEFINE_PARSING_FUNCTION(CONSTANT) {
  PENDING_TO_IMPL;
}

// Currently, Chameleon functions are
// operators of Term.
DEFINE_PARSING_FUNCTION(CALL) {
  if (!ctx->callExpr()) { return nullptr; }

  std::string functionId = ctx->callExpr()
                              ->WHERE_IDENTIFIER()
                              ->getSymbol()
                              ->getText();

  // Get the function object.
  std::optional<Utility::Var> v = Utility::Reflection::construct("functionId");
  if (!v.has_value()) {
    return nullptr;
  }
  std::unique_ptr<Expression::Function> f{
    v.value().convert<Expression::Function>()};

  // Next to get all of its arguments.
  std::vector<std::unique_ptr<Expression::Expr>> args;
  if (!ctx->callExpr()->arguments()) {
    // Empty arguments
    return std::make_unique<Expression::Call>(
      std::move(f), std::move(args));
  } else {
    // Currently, Functioin is just an operator of Term.
    // So type of all arguments are TermRef.
    ChameleonsParser::ArgumentsContext* arguments =
      ctx->callExpr()->arguments();

    while (arguments) {
      std::unique_ptr<Expression::Expr> arg =
        std::make_unique<Expression::TermRef>(
          arguments->WHERE_IDENTIFIER()->getText());

      args.push_back(std::move(arg));

      arguments = arguments->arguments();
    }

    return std::make_unique<Expression::Call>(
      std::move(f), std::move(args));
  }
}

DEFINE_PARSING_FUNCTION(ASSIGNMENT) {
  if (!ctx->assignExpr()) { return nullptr; }

  ChameleonsParser::AssignExprContext* assignCtx = ctx->assignExpr();

  // Buildup a TermRef as left hand side expression
  std::string leftTermID = assignCtx->WHERE_IDENTIFIER()->getText();
  std::unique_ptr<Expression::TermRef> leftExpr =
    std::make_unique<Expression::TermRef>(
      assignCtx->WHERE_IDENTIFIER()->getText());

  std::unique_ptr<Expression::Expr> rightExpr =
    toExpr(assignCtx->condExpr());

  return std::make_unique<Expression::Assignment>(
    std::move(leftExpr), std::move(rightExpr));
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
