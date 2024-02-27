
// Generated from ./WGSL.txt by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "WGSLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by WGSLParser.
 */
class  WGSLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by WGSLParser.
   */
    virtual std::any visitTemplate_args_start(WGSLParser::Template_args_startContext *context) = 0;

    virtual std::any visitTemplate_args_end(WGSLParser::Template_args_endContext *context) = 0;

    virtual std::any visitAdditive_operator(WGSLParser::Additive_operatorContext *context) = 0;

    virtual std::any visitMultiplicative_operator(WGSLParser::Multiplicative_operatorContext *context) = 0;

    virtual std::any visitArgument_expression_list(WGSLParser::Argument_expression_listContext *context) = 0;

    virtual std::any visitAssignment_statement(WGSLParser::Assignment_statementContext *context) = 0;

    virtual std::any visitShift_expression_post_unary_expression(WGSLParser::Shift_expression_post_unary_expressionContext *context) = 0;

    virtual std::any visitAttribute(WGSLParser::AttributeContext *context) = 0;

    virtual std::any visitBitwise_expression_post_unary_expression(WGSLParser::Bitwise_expression_post_unary_expressionContext *context) = 0;

    virtual std::any visitCase_selector(WGSLParser::Case_selectorContext *context) = 0;

    virtual std::any visitComponent_or_swizzle_specifier(WGSLParser::Component_or_swizzle_specifierContext *context) = 0;

    virtual std::any visitCompound_statement(WGSLParser::Compound_statementContext *context) = 0;

    virtual std::any visitCore_lhs_expression(WGSLParser::Core_lhs_expressionContext *context) = 0;

    virtual std::any visitDiagnostic_control(WGSLParser::Diagnostic_controlContext *context) = 0;

    virtual std::any visitDiagnostic_rule_name(WGSLParser::Diagnostic_rule_nameContext *context) = 0;

    virtual std::any visitExpression(WGSLParser::ExpressionContext *context) = 0;

    virtual std::any visitFloat_literal(WGSLParser::Float_literalContext *context) = 0;

    virtual std::any visitFor_init(WGSLParser::For_initContext *context) = 0;

    virtual std::any visitFor_update(WGSLParser::For_updateContext *context) = 0;

    virtual std::any visitGlobal_decl(WGSLParser::Global_declContext *context) = 0;

    virtual std::any visitGlobal_directive(WGSLParser::Global_directiveContext *context) = 0;

    virtual std::any visitGlobal_value_decl(WGSLParser::Global_value_declContext *context) = 0;

    virtual std::any visitIdent(WGSLParser::IdentContext *context) = 0;

    virtual std::any visitInt_literal(WGSLParser::Int_literalContext *context) = 0;

    virtual std::any visitLhs_expression(WGSLParser::Lhs_expressionContext *context) = 0;

    virtual std::any visitLiteral(WGSLParser::LiteralContext *context) = 0;

    virtual std::any visitMember_ident(WGSLParser::Member_identContext *context) = 0;

    virtual std::any visitOptionally_typed_ident(WGSLParser::Optionally_typed_identContext *context) = 0;

    virtual std::any visitParam(WGSLParser::ParamContext *context) = 0;

    virtual std::any visitPrimary_expression(WGSLParser::Primary_expressionContext *context) = 0;

    virtual std::any visitGreater_than(WGSLParser::Greater_thanContext *context) = 0;

    virtual std::any visitLess_than(WGSLParser::Less_thanContext *context) = 0;

    virtual std::any visitRelational_expression_post_unary_expression(WGSLParser::Relational_expression_post_unary_expressionContext *context) = 0;

    virtual std::any visitStatement(WGSLParser::StatementContext *context) = 0;

    virtual std::any visitSwitch_clause(WGSLParser::Switch_clauseContext *context) = 0;

    virtual std::any visitTemplate_arg_expression(WGSLParser::Template_arg_expressionContext *context) = 0;

    virtual std::any visitTemplate_elaborated_ident_post_ident(WGSLParser::Template_elaborated_ident_post_identContext *context) = 0;

    virtual std::any visitTranslation_unit(WGSLParser::Translation_unitContext *context) = 0;

    virtual std::any visitType_specifier(WGSLParser::Type_specifierContext *context) = 0;

    virtual std::any visitUnary_expression(WGSLParser::Unary_expressionContext *context) = 0;

    virtual std::any visitVariable_decl(WGSLParser::Variable_declContext *context) = 0;

    virtual std::any visitVariable_or_value_statement(WGSLParser::Variable_or_value_statementContext *context) = 0;

    virtual std::any visitVariable_updating_statement(WGSLParser::Variable_updating_statementContext *context) = 0;


};

