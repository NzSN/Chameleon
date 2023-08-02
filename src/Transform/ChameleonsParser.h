
// Generated from ChameleonsParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  ChameleonsParser : public antlr4::Parser {
public:
  enum {
    IDENTIFIER = 1, COLON = 2, OPENBRACE = 3, TRANSFORM = 4, WS = 5, CODEBYTES = 6, 
    CLOSEBRACE = 7
  };

  enum {
    RuleProg = 0, RuleRewriteRules = 1, RuleRewriteRule = 2, RuleSourcePattern = 3, 
    RuleTargetPattern = 4
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


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

