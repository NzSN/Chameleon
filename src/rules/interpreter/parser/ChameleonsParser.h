
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
    RuleMigrate = 0, RuleMigrateRules = 1, RuleMigrateRule = 2, RuleOriginCode = 3, 
    RuleTargetCode = 4
  };

  explicit ChameleonsParser(antlr4::TokenStream *input);

  ChameleonsParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ChameleonsParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class MigrateContext;
  class MigrateRulesContext;
  class MigrateRuleContext;
  class OriginCodeContext;
  class TargetCodeContext; 

  class  MigrateContext : public antlr4::ParserRuleContext {
  public:
    MigrateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MigrateRulesContext *migrateRules();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MigrateContext* migrate();

  class  MigrateRulesContext : public antlr4::ParserRuleContext {
  public:
    MigrateRulesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MigrateRuleContext *migrateRule();
    MigrateRulesContext *migrateRules();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MigrateRulesContext* migrateRules();

  class  MigrateRuleContext : public antlr4::ParserRuleContext {
  public:
    MigrateRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> OPENBRACE();
    antlr4::tree::TerminalNode* OPENBRACE(size_t i);
    OriginCodeContext *originCode();
    std::vector<antlr4::tree::TerminalNode *> CLOSEBRACE();
    antlr4::tree::TerminalNode* CLOSEBRACE(size_t i);
    antlr4::tree::TerminalNode *TRANSFORM();
    TargetCodeContext *targetCode();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MigrateRuleContext* migrateRule();

  class  OriginCodeContext : public antlr4::ParserRuleContext {
  public:
    OriginCodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODEBYTES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginCodeContext* originCode();

  class  TargetCodeContext : public antlr4::ParserRuleContext {
  public:
    TargetCodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODEBYTES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TargetCodeContext* targetCode();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

