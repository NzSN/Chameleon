#ifndef WHERECLAUSEEXPR_H
#define WHERECLAUSEEXPR_H

#include "TransEngine/Rewrite/Rule.h"
#include "TransEngine/Rewrite/Expr/Expr.h"
#include "../ChameleonsLexer.h"
#include "../ChameleonsParser.h"

using P = ChameleonsParser;

namespace TransEngine::Compiler::WhereClause {

enum ExprType {
  ERROR_TYPE,
  LOGICAL,
  ORDER,
  TERM,
  NUMBER,
  TYPE_COUNT,
};

enum OrderExprType {
  EQUAL,
  LESS,
  LESS_EQUAL,
  GREATER,
  GREATER_EQUAL,
};

// Logical operator
constexpr char LOGI_OP_AND[]  = "AND";
constexpr char LOGI_OP_OR[] = "OR";

// Order operator
constexpr char ORDER_OP_EQ[] = "=";
constexpr char ORDER_OP_LESSTHAN[] = "<";
constexpr char ORDER_OP_LESSEQUAL[] = "<=";
constexpr char ORDER_OP_GREATERTHAN[] = ">";
constexpr char ORDER_OP_GREATEREQUAL[] = ">=";

inline ExprType getExprType(P::CondExprContext* ctx) {
  if (ctx->LOGICOP() != nullptr) {
    return LOGICAL;
  }

  if (ctx->ORDEROP() != nullptr) {
    return ORDER;
  }

  if (ctx->TERM_VAR() != nullptr) {
    return TERM;
  }

  if (ctx->NUMBER() != nullptr) {
    return NUMBER;
  }

  return ERROR_TYPE;
}

template<Base::GPTMeta T>
std::unique_ptr<Expression::Expr<T>>
toExpr(P::CondExprContext* ctx);


} // TransEngine::Compiler::WhereClause



#endif /* WHERECLAUSEEXPR_H */
