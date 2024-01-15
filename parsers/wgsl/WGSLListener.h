
// Generated from ./WGSL.txt by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "WGSLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by WGSLParser.
 */
class  WGSLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterTemplate_args_start(WGSLParser::Template_args_startContext *ctx) = 0;
  virtual void exitTemplate_args_start(WGSLParser::Template_args_startContext *ctx) = 0;

  virtual void enterTemplate_args_end(WGSLParser::Template_args_endContext *ctx) = 0;
  virtual void exitTemplate_args_end(WGSLParser::Template_args_endContext *ctx) = 0;

  virtual void enterAdditive_operator(WGSLParser::Additive_operatorContext *ctx) = 0;
  virtual void exitAdditive_operator(WGSLParser::Additive_operatorContext *ctx) = 0;

  virtual void enterMultiplicative_operator(WGSLParser::Multiplicative_operatorContext *ctx) = 0;
  virtual void exitMultiplicative_operator(WGSLParser::Multiplicative_operatorContext *ctx) = 0;

  virtual void enterArgument_expression_list(WGSLParser::Argument_expression_listContext *ctx) = 0;
  virtual void exitArgument_expression_list(WGSLParser::Argument_expression_listContext *ctx) = 0;

  virtual void enterAssignment_statement(WGSLParser::Assignment_statementContext *ctx) = 0;
  virtual void exitAssignment_statement(WGSLParser::Assignment_statementContext *ctx) = 0;

  virtual void enterShift_expression_post_unary_expression(WGSLParser::Shift_expression_post_unary_expressionContext *ctx) = 0;
  virtual void exitShift_expression_post_unary_expression(WGSLParser::Shift_expression_post_unary_expressionContext *ctx) = 0;

  virtual void enterAttribute(WGSLParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(WGSLParser::AttributeContext *ctx) = 0;

  virtual void enterBitwise_expression_post_unary_expression(WGSLParser::Bitwise_expression_post_unary_expressionContext *ctx) = 0;
  virtual void exitBitwise_expression_post_unary_expression(WGSLParser::Bitwise_expression_post_unary_expressionContext *ctx) = 0;

  virtual void enterCase_selector(WGSLParser::Case_selectorContext *ctx) = 0;
  virtual void exitCase_selector(WGSLParser::Case_selectorContext *ctx) = 0;

  virtual void enterComponent_or_swizzle_specifier(WGSLParser::Component_or_swizzle_specifierContext *ctx) = 0;
  virtual void exitComponent_or_swizzle_specifier(WGSLParser::Component_or_swizzle_specifierContext *ctx) = 0;

  virtual void enterCompound_statement(WGSLParser::Compound_statementContext *ctx) = 0;
  virtual void exitCompound_statement(WGSLParser::Compound_statementContext *ctx) = 0;

  virtual void enterCore_lhs_expression(WGSLParser::Core_lhs_expressionContext *ctx) = 0;
  virtual void exitCore_lhs_expression(WGSLParser::Core_lhs_expressionContext *ctx) = 0;

  virtual void enterDiagnostic_control(WGSLParser::Diagnostic_controlContext *ctx) = 0;
  virtual void exitDiagnostic_control(WGSLParser::Diagnostic_controlContext *ctx) = 0;

  virtual void enterDiagnostic_rule_name(WGSLParser::Diagnostic_rule_nameContext *ctx) = 0;
  virtual void exitDiagnostic_rule_name(WGSLParser::Diagnostic_rule_nameContext *ctx) = 0;

  virtual void enterExpression(WGSLParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(WGSLParser::ExpressionContext *ctx) = 0;

  virtual void enterFloat_literal(WGSLParser::Float_literalContext *ctx) = 0;
  virtual void exitFloat_literal(WGSLParser::Float_literalContext *ctx) = 0;

  virtual void enterFor_init(WGSLParser::For_initContext *ctx) = 0;
  virtual void exitFor_init(WGSLParser::For_initContext *ctx) = 0;

  virtual void enterFor_update(WGSLParser::For_updateContext *ctx) = 0;
  virtual void exitFor_update(WGSLParser::For_updateContext *ctx) = 0;

  virtual void enterGlobal_decl(WGSLParser::Global_declContext *ctx) = 0;
  virtual void exitGlobal_decl(WGSLParser::Global_declContext *ctx) = 0;

  virtual void enterGlobal_directive(WGSLParser::Global_directiveContext *ctx) = 0;
  virtual void exitGlobal_directive(WGSLParser::Global_directiveContext *ctx) = 0;

  virtual void enterGlobal_value_decl(WGSLParser::Global_value_declContext *ctx) = 0;
  virtual void exitGlobal_value_decl(WGSLParser::Global_value_declContext *ctx) = 0;

  virtual void enterIdent(WGSLParser::IdentContext *ctx) = 0;
  virtual void exitIdent(WGSLParser::IdentContext *ctx) = 0;

  virtual void enterInt_literal(WGSLParser::Int_literalContext *ctx) = 0;
  virtual void exitInt_literal(WGSLParser::Int_literalContext *ctx) = 0;

  virtual void enterLhs_expression(WGSLParser::Lhs_expressionContext *ctx) = 0;
  virtual void exitLhs_expression(WGSLParser::Lhs_expressionContext *ctx) = 0;

  virtual void enterLiteral(WGSLParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(WGSLParser::LiteralContext *ctx) = 0;

  virtual void enterMember_ident(WGSLParser::Member_identContext *ctx) = 0;
  virtual void exitMember_ident(WGSLParser::Member_identContext *ctx) = 0;

  virtual void enterOptionally_typed_ident(WGSLParser::Optionally_typed_identContext *ctx) = 0;
  virtual void exitOptionally_typed_ident(WGSLParser::Optionally_typed_identContext *ctx) = 0;

  virtual void enterParam(WGSLParser::ParamContext *ctx) = 0;
  virtual void exitParam(WGSLParser::ParamContext *ctx) = 0;

  virtual void enterPrimary_expression(WGSLParser::Primary_expressionContext *ctx) = 0;
  virtual void exitPrimary_expression(WGSLParser::Primary_expressionContext *ctx) = 0;

  virtual void enterGreater_than(WGSLParser::Greater_thanContext *ctx) = 0;
  virtual void exitGreater_than(WGSLParser::Greater_thanContext *ctx) = 0;

  virtual void enterLess_than(WGSLParser::Less_thanContext *ctx) = 0;
  virtual void exitLess_than(WGSLParser::Less_thanContext *ctx) = 0;

  virtual void enterRelational_expression_post_unary_expression(WGSLParser::Relational_expression_post_unary_expressionContext *ctx) = 0;
  virtual void exitRelational_expression_post_unary_expression(WGSLParser::Relational_expression_post_unary_expressionContext *ctx) = 0;

  virtual void enterStatement(WGSLParser::StatementContext *ctx) = 0;
  virtual void exitStatement(WGSLParser::StatementContext *ctx) = 0;

  virtual void enterSwitch_clause(WGSLParser::Switch_clauseContext *ctx) = 0;
  virtual void exitSwitch_clause(WGSLParser::Switch_clauseContext *ctx) = 0;

  virtual void enterTemplate_arg_expression(WGSLParser::Template_arg_expressionContext *ctx) = 0;
  virtual void exitTemplate_arg_expression(WGSLParser::Template_arg_expressionContext *ctx) = 0;

  virtual void enterTemplate_elaborated_ident_post_ident(WGSLParser::Template_elaborated_ident_post_identContext *ctx) = 0;
  virtual void exitTemplate_elaborated_ident_post_ident(WGSLParser::Template_elaborated_ident_post_identContext *ctx) = 0;

  virtual void enterTranslation_unit(WGSLParser::Translation_unitContext *ctx) = 0;
  virtual void exitTranslation_unit(WGSLParser::Translation_unitContext *ctx) = 0;

  virtual void enterType_specifier(WGSLParser::Type_specifierContext *ctx) = 0;
  virtual void exitType_specifier(WGSLParser::Type_specifierContext *ctx) = 0;

  virtual void enterUnary_expression(WGSLParser::Unary_expressionContext *ctx) = 0;
  virtual void exitUnary_expression(WGSLParser::Unary_expressionContext *ctx) = 0;

  virtual void enterVariable_decl(WGSLParser::Variable_declContext *ctx) = 0;
  virtual void exitVariable_decl(WGSLParser::Variable_declContext *ctx) = 0;

  virtual void enterVariable_or_value_statement(WGSLParser::Variable_or_value_statementContext *ctx) = 0;
  virtual void exitVariable_or_value_statement(WGSLParser::Variable_or_value_statementContext *ctx) = 0;

  virtual void enterVariable_updating_statement(WGSLParser::Variable_updating_statementContext *ctx) = 0;
  virtual void exitVariable_updating_statement(WGSLParser::Variable_updating_statementContext *ctx) = 0;


};

