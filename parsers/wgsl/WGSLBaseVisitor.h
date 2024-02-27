
// Generated from ./WGSL.txt by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "WGSLVisitor.h"


/**
 * This class provides an empty implementation of WGSLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  WGSLBaseVisitor : public WGSLVisitor {
public:

  virtual std::any visitTemplate_args_start(WGSLParser::Template_args_startContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplate_args_end(WGSLParser::Template_args_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditive_operator(WGSLParser::Additive_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicative_operator(WGSLParser::Multiplicative_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_expression_list(WGSLParser::Argument_expression_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment_statement(WGSLParser::Assignment_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShift_expression_post_unary_expression(WGSLParser::Shift_expression_post_unary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute(WGSLParser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitwise_expression_post_unary_expression(WGSLParser::Bitwise_expression_post_unary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCase_selector(WGSLParser::Case_selectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComponent_or_swizzle_specifier(WGSLParser::Component_or_swizzle_specifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompound_statement(WGSLParser::Compound_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCore_lhs_expression(WGSLParser::Core_lhs_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDiagnostic_control(WGSLParser::Diagnostic_controlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDiagnostic_rule_name(WGSLParser::Diagnostic_rule_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(WGSLParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloat_literal(WGSLParser::Float_literalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_init(WGSLParser::For_initContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_update(WGSLParser::For_updateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobal_decl(WGSLParser::Global_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobal_directive(WGSLParser::Global_directiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobal_value_decl(WGSLParser::Global_value_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdent(WGSLParser::IdentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInt_literal(WGSLParser::Int_literalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLhs_expression(WGSLParser::Lhs_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(WGSLParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMember_ident(WGSLParser::Member_identContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptionally_typed_ident(WGSLParser::Optionally_typed_identContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(WGSLParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_expression(WGSLParser::Primary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGreater_than(WGSLParser::Greater_thanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLess_than(WGSLParser::Less_thanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelational_expression_post_unary_expression(WGSLParser::Relational_expression_post_unary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(WGSLParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitch_clause(WGSLParser::Switch_clauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplate_arg_expression(WGSLParser::Template_arg_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplate_elaborated_ident_post_ident(WGSLParser::Template_elaborated_ident_post_identContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTranslation_unit(WGSLParser::Translation_unitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_specifier(WGSLParser::Type_specifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_expression(WGSLParser::Unary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_decl(WGSLParser::Variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_or_value_statement(WGSLParser::Variable_or_value_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_updating_statement(WGSLParser::Variable_updating_statementContext *ctx) override {
    return visitChildren(ctx);
  }


};

