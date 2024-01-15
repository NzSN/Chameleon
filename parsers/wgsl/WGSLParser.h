
// Generated from ./WGSL.txt by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  WGSLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, WS = 62, 
    Positive = 63, Minus = 64, Star = 65, Dash = 66, MOD = 67, Left_angle = 68, 
    Right_angle = 69, Sigma_term = 70, Ident_pattern_token = 71, Bool_literal = 72, 
    Compound_assignment_operator = 73, Decimal_float_literal = 74, Decimal_int_literal = 75, 
    Hex_float_literal = 76, Hex_int_literal = 77, Greater_than_equal = 78, 
    Less_than_equal = 79, Shift_left = 80, Shift_right = 81, Break_statement = 82, 
    Continue_statement = 83, Severity_control_name = 84, Swizzle_name = 85
  };

  enum {
    RuleTemplate_args_start = 0, RuleTemplate_args_end = 1, RuleAdditive_operator = 2, 
    RuleMultiplicative_operator = 3, RuleArgument_expression_list = 4, RuleAssignment_statement = 5, 
    RuleShift_expression_post_unary_expression = 6, RuleAttribute = 7, RuleBitwise_expression_post_unary_expression = 8, 
    RuleCase_selector = 9, RuleComponent_or_swizzle_specifier = 10, RuleCompound_statement = 11, 
    RuleCore_lhs_expression = 12, RuleDiagnostic_control = 13, RuleDiagnostic_rule_name = 14, 
    RuleExpression = 15, RuleFloat_literal = 16, RuleFor_init = 17, RuleFor_update = 18, 
    RuleGlobal_decl = 19, RuleGlobal_directive = 20, RuleGlobal_value_decl = 21, 
    RuleIdent = 22, RuleInt_literal = 23, RuleLhs_expression = 24, RuleLiteral = 25, 
    RuleMember_ident = 26, RuleOptionally_typed_ident = 27, RuleParam = 28, 
    RulePrimary_expression = 29, RuleGreater_than = 30, RuleLess_than = 31, 
    RuleRelational_expression_post_unary_expression = 32, RuleStatement = 33, 
    RuleSwitch_clause = 34, RuleTemplate_arg_expression = 35, RuleTemplate_elaborated_ident_post_ident = 36, 
    RuleTranslation_unit = 37, RuleType_specifier = 38, RuleUnary_expression = 39, 
    RuleVariable_decl = 40, RuleVariable_or_value_statement = 41, RuleVariable_updating_statement = 42
  };

  explicit WGSLParser(antlr4::TokenStream *input);

  WGSLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~WGSLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class Template_args_startContext;
  class Template_args_endContext;
  class Additive_operatorContext;
  class Multiplicative_operatorContext;
  class Argument_expression_listContext;
  class Assignment_statementContext;
  class Shift_expression_post_unary_expressionContext;
  class AttributeContext;
  class Bitwise_expression_post_unary_expressionContext;
  class Case_selectorContext;
  class Component_or_swizzle_specifierContext;
  class Compound_statementContext;
  class Core_lhs_expressionContext;
  class Diagnostic_controlContext;
  class Diagnostic_rule_nameContext;
  class ExpressionContext;
  class Float_literalContext;
  class For_initContext;
  class For_updateContext;
  class Global_declContext;
  class Global_directiveContext;
  class Global_value_declContext;
  class IdentContext;
  class Int_literalContext;
  class Lhs_expressionContext;
  class LiteralContext;
  class Member_identContext;
  class Optionally_typed_identContext;
  class ParamContext;
  class Primary_expressionContext;
  class Greater_thanContext;
  class Less_thanContext;
  class Relational_expression_post_unary_expressionContext;
  class StatementContext;
  class Switch_clauseContext;
  class Template_arg_expressionContext;
  class Template_elaborated_ident_post_identContext;
  class Translation_unitContext;
  class Type_specifierContext;
  class Unary_expressionContext;
  class Variable_declContext;
  class Variable_or_value_statementContext;
  class Variable_updating_statementContext; 

  class  Template_args_startContext : public antlr4::ParserRuleContext {
  public:
    Template_args_startContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Left_angle();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Template_args_startContext* template_args_start();

  class  Template_args_endContext : public antlr4::ParserRuleContext {
  public:
    Template_args_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Right_angle();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Template_args_endContext* template_args_end();

  class  Additive_operatorContext : public antlr4::ParserRuleContext {
  public:
    Additive_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Positive();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Additive_operatorContext* additive_operator();

  class  Multiplicative_operatorContext : public antlr4::ParserRuleContext {
  public:
    Multiplicative_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Dash();
    antlr4::tree::TerminalNode *MOD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Multiplicative_operatorContext* multiplicative_operator();

  class  Argument_expression_listContext : public antlr4::ParserRuleContext {
  public:
    Argument_expression_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Argument_expression_listContext* argument_expression_list();

  class  Assignment_statementContext : public antlr4::ParserRuleContext {
  public:
    Assignment_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Compound_assignment_operator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Assignment_statementContext* assignment_statement();

  class  Shift_expression_post_unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Shift_expression_post_unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Multiplicative_operatorContext *> multiplicative_operator();
    Multiplicative_operatorContext* multiplicative_operator(size_t i);
    std::vector<Unary_expressionContext *> unary_expression();
    Unary_expressionContext* unary_expression(size_t i);
    std::vector<Additive_operatorContext *> additive_operator();
    Additive_operatorContext* additive_operator(size_t i);
    antlr4::tree::TerminalNode *Shift_left();
    antlr4::tree::TerminalNode *Shift_right();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Shift_expression_post_unary_expressionContext* shift_expression_post_unary_expression();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    Diagnostic_controlContext *diagnostic_control();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeContext* attribute();

  class  Bitwise_expression_post_unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Bitwise_expression_post_unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Unary_expressionContext *> unary_expression();
    Unary_expressionContext* unary_expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bitwise_expression_post_unary_expressionContext* bitwise_expression_post_unary_expression();

  class  Case_selectorContext : public antlr4::ParserRuleContext {
  public:
    Case_selectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Case_selectorContext* case_selector();

  class  Component_or_swizzle_specifierContext : public antlr4::ParserRuleContext {
  public:
    Component_or_swizzle_specifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_identContext *member_ident();
    Component_or_swizzle_specifierContext *component_or_swizzle_specifier();
    antlr4::tree::TerminalNode *Swizzle_name();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Component_or_swizzle_specifierContext* component_or_swizzle_specifier();

  class  Compound_statementContext : public antlr4::ParserRuleContext {
  public:
    Compound_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Compound_statementContext* compound_statement();

  class  Core_lhs_expressionContext : public antlr4::ParserRuleContext {
  public:
    Core_lhs_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Lhs_expressionContext *lhs_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Core_lhs_expressionContext* core_lhs_expression();

  class  Diagnostic_controlContext : public antlr4::ParserRuleContext {
  public:
    Diagnostic_controlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Severity_control_name();
    Diagnostic_rule_nameContext *diagnostic_rule_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Diagnostic_controlContext* diagnostic_control();

  class  Diagnostic_rule_nameContext : public antlr4::ParserRuleContext {
  public:
    Diagnostic_rule_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Ident_pattern_token();
    antlr4::tree::TerminalNode* Ident_pattern_token(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Diagnostic_rule_nameContext* diagnostic_rule_name();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Unary_expressionContext *> unary_expression();
    Unary_expressionContext* unary_expression(size_t i);
    Bitwise_expression_post_unary_expressionContext *bitwise_expression_post_unary_expression();
    std::vector<Relational_expression_post_unary_expressionContext *> relational_expression_post_unary_expression();
    Relational_expression_post_unary_expressionContext* relational_expression_post_unary_expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class  Float_literalContext : public antlr4::ParserRuleContext {
  public:
    Float_literalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Decimal_float_literal();
    antlr4::tree::TerminalNode *Hex_float_literal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Float_literalContext* float_literal();

  class  For_initContext : public antlr4::ParserRuleContext {
  public:
    For_initContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Template_elaborated_ident_post_identContext *template_elaborated_ident_post_ident();
    Argument_expression_listContext *argument_expression_list();
    Variable_or_value_statementContext *variable_or_value_statement();
    Variable_updating_statementContext *variable_updating_statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  For_initContext* for_init();

  class  For_updateContext : public antlr4::ParserRuleContext {
  public:
    For_updateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Template_elaborated_ident_post_identContext *template_elaborated_ident_post_ident();
    Argument_expression_listContext *argument_expression_list();
    Variable_updating_statementContext *variable_updating_statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  For_updateContext* for_update();

  class  Global_declContext : public antlr4::ParserRuleContext {
  public:
    Global_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentContext *> ident();
    IdentContext* ident(size_t i);
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);
    std::vector<Type_specifierContext *> type_specifier();
    Type_specifierContext* type_specifier(size_t i);
    Template_elaborated_ident_post_identContext *template_elaborated_ident_post_ident();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<ParamContext *> param();
    ParamContext* param(size_t i);
    Optionally_typed_identContext *optionally_typed_ident();
    Template_args_startContext *template_args_start();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    Template_args_endContext *template_args_end();
    Global_value_declContext *global_value_decl();
    std::vector<Member_identContext *> member_ident();
    Member_identContext* member_ident(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_declContext* global_decl();

  class  Global_directiveContext : public antlr4::ParserRuleContext {
  public:
    Global_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Severity_control_name();
    Diagnostic_rule_nameContext *diagnostic_rule_name();
    std::vector<antlr4::tree::TerminalNode *> Ident_pattern_token();
    antlr4::tree::TerminalNode* Ident_pattern_token(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_directiveContext* global_directive();

  class  Global_value_declContext : public antlr4::ParserRuleContext {
  public:
    Global_value_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Optionally_typed_identContext *optionally_typed_ident();
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_value_declContext* global_value_decl();

  class  IdentContext : public antlr4::ParserRuleContext {
  public:
    IdentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Ident_pattern_token();
    antlr4::tree::TerminalNode *Sigma_term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentContext* ident();

  class  Int_literalContext : public antlr4::ParserRuleContext {
  public:
    Int_literalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Decimal_int_literal();
    antlr4::tree::TerminalNode *Hex_int_literal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Int_literalContext* int_literal();

  class  Lhs_expressionContext : public antlr4::ParserRuleContext {
  public:
    Lhs_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Core_lhs_expressionContext *core_lhs_expression();
    Component_or_swizzle_specifierContext *component_or_swizzle_specifier();
    Lhs_expressionContext *lhs_expression();
    antlr4::tree::TerminalNode *Star();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Lhs_expressionContext* lhs_expression();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Bool_literal();
    Float_literalContext *float_literal();
    Int_literalContext *int_literal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LiteralContext* literal();

  class  Member_identContext : public antlr4::ParserRuleContext {
  public:
    Member_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Ident_pattern_token();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Member_identContext* member_ident();

  class  Optionally_typed_identContext : public antlr4::ParserRuleContext {
  public:
    Optionally_typed_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Type_specifierContext *type_specifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Optionally_typed_identContext* optionally_typed_ident();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Type_specifierContext *type_specifier();
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParamContext* param();

  class  Primary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Primary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Template_elaborated_ident_post_identContext *template_elaborated_ident_post_ident();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    LiteralContext *literal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Primary_expressionContext* primary_expression();

  class  Greater_thanContext : public antlr4::ParserRuleContext {
  public:
    Greater_thanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Right_angle();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Greater_thanContext* greater_than();

  class  Less_thanContext : public antlr4::ParserRuleContext {
  public:
    Less_thanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Left_angle();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Less_thanContext* less_than();

  class  Relational_expression_post_unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Relational_expression_post_unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Shift_expression_post_unary_expressionContext *> shift_expression_post_unary_expression();
    Shift_expression_post_unary_expressionContext* shift_expression_post_unary_expression(size_t i);
    Greater_thanContext *greater_than();
    Unary_expressionContext *unary_expression();
    antlr4::tree::TerminalNode *Greater_than_equal();
    Less_thanContext *less_than();
    antlr4::tree::TerminalNode *Less_than_equal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Relational_expression_post_unary_expressionContext* relational_expression_post_unary_expression();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Compound_statementContext *> compound_statement();
    Compound_statementContext* compound_statement(size_t i);
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);
    For_initContext *for_init();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    For_updateContext *for_update();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *Break_statement();
    std::vector<Switch_clauseContext *> switch_clause();
    Switch_clauseContext* switch_clause(size_t i);
    IdentContext *ident();
    Template_elaborated_ident_post_identContext *template_elaborated_ident_post_ident();
    Variable_or_value_statementContext *variable_or_value_statement();
    Variable_updating_statementContext *variable_updating_statement();
    antlr4::tree::TerminalNode *Continue_statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  Switch_clauseContext : public antlr4::ParserRuleContext {
  public:
    Switch_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Case_selectorContext *> case_selector();
    Case_selectorContext* case_selector(size_t i);
    Compound_statementContext *compound_statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Switch_clauseContext* switch_clause();

  class  Template_arg_expressionContext : public antlr4::ParserRuleContext {
  public:
    Template_arg_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Template_arg_expressionContext* template_arg_expression();

  class  Template_elaborated_ident_post_identContext : public antlr4::ParserRuleContext {
  public:
    Template_elaborated_ident_post_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Template_args_startContext *template_args_start();
    Template_arg_expressionContext *template_arg_expression();
    Template_args_endContext *template_args_end();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Template_elaborated_ident_post_identContext* template_elaborated_ident_post_ident();

  class  Translation_unitContext : public antlr4::ParserRuleContext {
  public:
    Translation_unitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Global_directiveContext *> global_directive();
    Global_directiveContext* global_directive(size_t i);
    std::vector<Global_declContext *> global_decl();
    Global_declContext* global_decl(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Translation_unitContext* translation_unit();

  class  Type_specifierContext : public antlr4::ParserRuleContext {
  public:
    Type_specifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Template_args_startContext *template_args_start();
    Template_arg_expressionContext *template_arg_expression();
    Template_args_endContext *template_args_end();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_specifierContext* type_specifier();

  class  Unary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Unary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_expressionContext *primary_expression();
    Component_or_swizzle_specifierContext *component_or_swizzle_specifier();
    Unary_expressionContext *unary_expression();
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Minus();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Unary_expressionContext* unary_expression();

  class  Variable_declContext : public antlr4::ParserRuleContext {
  public:
    Variable_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Optionally_typed_identContext *optionally_typed_ident();
    Template_args_startContext *template_args_start();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    Template_args_endContext *template_args_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Variable_declContext* variable_decl();

  class  Variable_or_value_statementContext : public antlr4::ParserRuleContext {
  public:
    Variable_or_value_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variable_declContext *variable_decl();
    ExpressionContext *expression();
    Optionally_typed_identContext *optionally_typed_ident();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Variable_or_value_statementContext* variable_or_value_statement();

  class  Variable_updating_statementContext : public antlr4::ParserRuleContext {
  public:
    Variable_updating_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Lhs_expressionContext *lhs_expression();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Compound_assignment_operator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Variable_updating_statementContext* variable_updating_statement();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

