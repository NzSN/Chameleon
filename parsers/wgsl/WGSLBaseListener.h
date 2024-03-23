
// Generated from ./WGSL.txt by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "WGSLListener.h"


/**
 * This class provides an empty implementation of WGSLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  WGSLBaseListener : public WGSLListener {
public:

  virtual void enterTemplate_args_start(WGSLParser::Template_args_startContext * /*ctx*/) override { }
  virtual void exitTemplate_args_start(WGSLParser::Template_args_startContext * /*ctx*/) override { }

  virtual void enterTemplate_args_end(WGSLParser::Template_args_endContext * /*ctx*/) override { }
  virtual void exitTemplate_args_end(WGSLParser::Template_args_endContext * /*ctx*/) override { }

  virtual void enterAdditive_operator(WGSLParser::Additive_operatorContext * /*ctx*/) override { }
  virtual void exitAdditive_operator(WGSLParser::Additive_operatorContext * /*ctx*/) override { }

  virtual void enterMultiplicative_operator(WGSLParser::Multiplicative_operatorContext * /*ctx*/) override { }
  virtual void exitMultiplicative_operator(WGSLParser::Multiplicative_operatorContext * /*ctx*/) override { }

  virtual void enterArgument_expression_list(WGSLParser::Argument_expression_listContext * /*ctx*/) override { }
  virtual void exitArgument_expression_list(WGSLParser::Argument_expression_listContext * /*ctx*/) override { }

  virtual void enterAssignment_statement(WGSLParser::Assignment_statementContext * /*ctx*/) override { }
  virtual void exitAssignment_statement(WGSLParser::Assignment_statementContext * /*ctx*/) override { }

  virtual void enterShift_expression_post_unary_expression(WGSLParser::Shift_expression_post_unary_expressionContext * /*ctx*/) override { }
  virtual void exitShift_expression_post_unary_expression(WGSLParser::Shift_expression_post_unary_expressionContext * /*ctx*/) override { }

  virtual void enterAttribute(WGSLParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(WGSLParser::AttributeContext * /*ctx*/) override { }

  virtual void enterBitwise_expression_post_unary_expression(WGSLParser::Bitwise_expression_post_unary_expressionContext * /*ctx*/) override { }
  virtual void exitBitwise_expression_post_unary_expression(WGSLParser::Bitwise_expression_post_unary_expressionContext * /*ctx*/) override { }

  virtual void enterCase_selector(WGSLParser::Case_selectorContext * /*ctx*/) override { }
  virtual void exitCase_selector(WGSLParser::Case_selectorContext * /*ctx*/) override { }

  virtual void enterComponent_or_swizzle_specifier(WGSLParser::Component_or_swizzle_specifierContext * /*ctx*/) override { }
  virtual void exitComponent_or_swizzle_specifier(WGSLParser::Component_or_swizzle_specifierContext * /*ctx*/) override { }

  virtual void enterCompound_statement(WGSLParser::Compound_statementContext * /*ctx*/) override { }
  virtual void exitCompound_statement(WGSLParser::Compound_statementContext * /*ctx*/) override { }

  virtual void enterCore_lhs_expression(WGSLParser::Core_lhs_expressionContext * /*ctx*/) override { }
  virtual void exitCore_lhs_expression(WGSLParser::Core_lhs_expressionContext * /*ctx*/) override { }

  virtual void enterDiagnostic_control(WGSLParser::Diagnostic_controlContext * /*ctx*/) override { }
  virtual void exitDiagnostic_control(WGSLParser::Diagnostic_controlContext * /*ctx*/) override { }

  virtual void enterDiagnostic_rule_name(WGSLParser::Diagnostic_rule_nameContext * /*ctx*/) override { }
  virtual void exitDiagnostic_rule_name(WGSLParser::Diagnostic_rule_nameContext * /*ctx*/) override { }

  virtual void enterExpression(WGSLParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(WGSLParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterFloat_literal(WGSLParser::Float_literalContext * /*ctx*/) override { }
  virtual void exitFloat_literal(WGSLParser::Float_literalContext * /*ctx*/) override { }

  virtual void enterFor_init(WGSLParser::For_initContext * /*ctx*/) override { }
  virtual void exitFor_init(WGSLParser::For_initContext * /*ctx*/) override { }

  virtual void enterFor_update(WGSLParser::For_updateContext * /*ctx*/) override { }
  virtual void exitFor_update(WGSLParser::For_updateContext * /*ctx*/) override { }

  virtual void enterGlobal_decl(WGSLParser::Global_declContext * /*ctx*/) override { }
  virtual void exitGlobal_decl(WGSLParser::Global_declContext * /*ctx*/) override { }

  virtual void enterGlobal_directive(WGSLParser::Global_directiveContext * /*ctx*/) override { }
  virtual void exitGlobal_directive(WGSLParser::Global_directiveContext * /*ctx*/) override { }

  virtual void enterGlobal_value_decl(WGSLParser::Global_value_declContext * /*ctx*/) override { }
  virtual void exitGlobal_value_decl(WGSLParser::Global_value_declContext * /*ctx*/) override { }

  virtual void enterIdent(WGSLParser::IdentContext * /*ctx*/) override { }
  virtual void exitIdent(WGSLParser::IdentContext * /*ctx*/) override { }

  virtual void enterInt_literal(WGSLParser::Int_literalContext * /*ctx*/) override { }
  virtual void exitInt_literal(WGSLParser::Int_literalContext * /*ctx*/) override { }

  virtual void enterLhs_expression(WGSLParser::Lhs_expressionContext * /*ctx*/) override { }
  virtual void exitLhs_expression(WGSLParser::Lhs_expressionContext * /*ctx*/) override { }

  virtual void enterLiteral(WGSLParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(WGSLParser::LiteralContext * /*ctx*/) override { }

  virtual void enterMember_ident(WGSLParser::Member_identContext * /*ctx*/) override { }
  virtual void exitMember_ident(WGSLParser::Member_identContext * /*ctx*/) override { }

  virtual void enterOptionally_typed_ident(WGSLParser::Optionally_typed_identContext * /*ctx*/) override { }
  virtual void exitOptionally_typed_ident(WGSLParser::Optionally_typed_identContext * /*ctx*/) override { }

  virtual void enterParam(WGSLParser::ParamContext * /*ctx*/) override { }
  virtual void exitParam(WGSLParser::ParamContext * /*ctx*/) override { }

  virtual void enterPrimary_expression(WGSLParser::Primary_expressionContext * /*ctx*/) override { }
  virtual void exitPrimary_expression(WGSLParser::Primary_expressionContext * /*ctx*/) override { }

  virtual void enterGreater_than(WGSLParser::Greater_thanContext * /*ctx*/) override { }
  virtual void exitGreater_than(WGSLParser::Greater_thanContext * /*ctx*/) override { }

  virtual void enterLess_than(WGSLParser::Less_thanContext * /*ctx*/) override { }
  virtual void exitLess_than(WGSLParser::Less_thanContext * /*ctx*/) override { }

  virtual void enterRelational_expression_post_unary_expression(WGSLParser::Relational_expression_post_unary_expressionContext * /*ctx*/) override { }
  virtual void exitRelational_expression_post_unary_expression(WGSLParser::Relational_expression_post_unary_expressionContext * /*ctx*/) override { }

  virtual void enterStatement(WGSLParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(WGSLParser::StatementContext * /*ctx*/) override { }

  virtual void enterSwitch_clause(WGSLParser::Switch_clauseContext * /*ctx*/) override { }
  virtual void exitSwitch_clause(WGSLParser::Switch_clauseContext * /*ctx*/) override { }

  virtual void enterTemplate_arg_expression(WGSLParser::Template_arg_expressionContext * /*ctx*/) override { }
  virtual void exitTemplate_arg_expression(WGSLParser::Template_arg_expressionContext * /*ctx*/) override { }

  virtual void enterTemplate_elaborated_ident_post_ident(WGSLParser::Template_elaborated_ident_post_identContext * /*ctx*/) override { }
  virtual void exitTemplate_elaborated_ident_post_ident(WGSLParser::Template_elaborated_ident_post_identContext * /*ctx*/) override { }

  virtual void enterTranslation_unit(WGSLParser::Translation_unitContext * /*ctx*/) override { }
  virtual void exitTranslation_unit(WGSLParser::Translation_unitContext * /*ctx*/) override { }

  virtual void enterType_specifier(WGSLParser::Type_specifierContext * /*ctx*/) override { }
  virtual void exitType_specifier(WGSLParser::Type_specifierContext * /*ctx*/) override { }

  virtual void enterUnary_expression(WGSLParser::Unary_expressionContext * /*ctx*/) override { }
  virtual void exitUnary_expression(WGSLParser::Unary_expressionContext * /*ctx*/) override { }

  virtual void enterVariable_decl(WGSLParser::Variable_declContext * /*ctx*/) override { }
  virtual void exitVariable_decl(WGSLParser::Variable_declContext * /*ctx*/) override { }

  virtual void enterVariable_or_value_statement(WGSLParser::Variable_or_value_statementContext * /*ctx*/) override { }
  virtual void exitVariable_or_value_statement(WGSLParser::Variable_or_value_statementContext * /*ctx*/) override { }

  virtual void enterVariable_updating_statement(WGSLParser::Variable_updating_statementContext * /*ctx*/) override { }
  virtual void exitVariable_updating_statement(WGSLParser::Variable_updating_statementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

