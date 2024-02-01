#ifndef WHERECLAUSEEXPR_H
#define WHERECLAUSEEXPR_H

#include "TransEngine/Rewrite/Expr/Expr.h"
#include "../ChameleonsLexer.h"
#include "../ChameleonsParser.h"

using P = ChameleonsParser;

namespace TransEngine::Compiler::WhereClause {

std::unique_ptr<Expression::Expr> toExpr(P::CondExprContext* ctx);


} // TransEngine::Compiler::WhereClause



#endif /* WHERECLAUSEEXPR_H */
