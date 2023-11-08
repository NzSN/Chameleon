
// Generated from ./ChameleonsParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  ChameleonsParser : public antlr4::Parser {
public:
  enum {
    TARGET_TAG = 1, RULE_TAG = 2, STRATEGY_TAG = 3, WHERE = 4, LOGICOP = 5, 
    ORDEROP = 6, NUMBER = 7, IDENTIFIER = 8, COLON = 9, OPENBRACE = 10, 
    TERM_VAR = 11, TRANSFORM = 12, WS = 13, CODEBYTES = 14, CLOSEBRACE = 15
  };

  enum {
    RuleProg = 0, RuleTargetSection = 1, RuleRuleSection = 2, RuleStrategySection = 3, 
    RuleRewriteRules = 4, RuleRewriteRule = 5, RuleSourcePattern = 6, RuleTargetPattern = 7, 
    RuleCondExprs = 8, RuleCondExpr = 9
  };

  explicit ChameleonsParser(antlr4::TokenStream *input);

  ChameleonsParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ChameleonsParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgContext;
  class TargetSectionContext;
  class RuleSectionContext;
  class StrategySectionContext;
  class RewriteRulesContext;
  class RewriteRuleContext;
  class SourcePatternContext;
  class TargetPatternContext;
  class CondExprsContext;
  class CondExprContext; 

  class  ProgContext : public antlr4::ParserRuleContext {
  public:
    ProgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TargetSectionContext *targetSection();
    RuleSectionContext *ruleSection();
    StrategySectionContext *strategySection();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgContext* prog();

  class  TargetSectionContext : public antlr4::ParserRuleContext {
  public:
    TargetSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TARGET_TAG();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TargetSectionContext* targetSection();

  class  RuleSectionContext : public antlr4::ParserRuleContext {
  public:
    RuleSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE_TAG();
    RewriteRulesContext *rewriteRules();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RuleSectionContext* ruleSection();

  class  StrategySectionContext : public antlr4::ParserRuleContext {
  public:
    StrategySectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRATEGY_TAG();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StrategySectionContext* strategySection();

  class  RewriteRulesContext : public antlr4::ParserRuleContext {
  public:
    RewriteRulesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RewriteRuleContext *rewriteRule();
    RewriteRulesContext *rewriteRules();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RewriteRulesContext* rewriteRules();

  class  RewriteRuleContext : public antlr4::ParserRuleContext {
  public:
    RewriteRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> OPENBRACE();
    antlr4::tree::TerminalNode* OPENBRACE(size_t i);
    SourcePatternContext *sourcePattern();
    std::vector<antlr4::tree::TerminalNode *> CLOSEBRACE();
    antlr4::tree::TerminalNode* CLOSEBRACE(size_t i);
    antlr4::tree::TerminalNode *TRANSFORM();
    TargetPatternContext *targetPattern();
    antlr4::tree::TerminalNode *WHERE();
    CondExprsContext *condExprs();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RewriteRuleContext* rewriteRule();

  class  SourcePatternContext : public antlr4::ParserRuleContext {
  public:
    SourcePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODEBYTES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SourcePatternContext* sourcePattern();

  class  TargetPatternContext : public antlr4::ParserRuleContext {
  public:
    TargetPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODEBYTES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TargetPatternContext* targetPattern();

  class  CondExprsContext : public antlr4::ParserRuleContext {
  public:
    CondExprsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CondExprContext *condExpr();
    antlr4::tree::TerminalNode *LOGICOP();
    CondExprsContext *condExprs();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CondExprsContext* condExprs();

  class  CondExprContext : public antlr4::ParserRuleContext {
  public:
    CondExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TERM_VAR();
    antlr4::tree::TerminalNode* TERM_VAR(size_t i);
    antlr4::tree::TerminalNode *ORDEROP();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CondExprContext* condExpr();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

