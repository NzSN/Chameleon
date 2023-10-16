
// Generated from ./ChameleonsParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  ChameleonsParser : public antlr4::Parser {
public:
  enum {
    WHERE = 1, LOGICOP = 2, ORDEROP = 3, NUMBER = 4, IDENTIFIER = 5, COLON = 6, 
    OPENBRACE = 7, TERM_VAR = 8, TRANSFORM = 9, WS = 10, CODEBYTES = 11, 
    CLOSEBRACE = 12
  };

  enum {
    RuleProg = 0, RuleRewriteRules = 1, RuleRewriteRule = 2, RuleSourcePattern = 3, 
    RuleTargetPattern = 4, RuleCondExprs = 5, RuleCondExpr = 6
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
    RewriteRulesContext *rewriteRules();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgContext* prog();

  class  RewriteRulesContext : public antlr4::ParserRuleContext {
  public:
    RewriteRulesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RewriteRuleContext *rewriteRule();
    RewriteRulesContext *rewriteRules();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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
   
  };

  RewriteRuleContext* rewriteRule();

  class  SourcePatternContext : public antlr4::ParserRuleContext {
  public:
    SourcePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODEBYTES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SourcePatternContext* sourcePattern();

  class  TargetPatternContext : public antlr4::ParserRuleContext {
  public:
    TargetPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODEBYTES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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
   
  };

  CondExprContext* condExpr();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

