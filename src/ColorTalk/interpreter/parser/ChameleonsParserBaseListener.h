
// Generated from ChameleonsParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "ChameleonsParserListener.h"


/**
 * This class provides an empty implementation of ChameleonsParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ChameleonsParserBaseListener : public ChameleonsParserListener {
public:

  virtual void enterMigrate(ChameleonsParser::MigrateContext * /*ctx*/) override { }
  virtual void exitMigrate(ChameleonsParser::MigrateContext * /*ctx*/) override { }

  virtual void enterMigrateRules(ChameleonsParser::MigrateRulesContext * /*ctx*/) override { }
  virtual void exitMigrateRules(ChameleonsParser::MigrateRulesContext * /*ctx*/) override { }

  virtual void enterMigrateRule(ChameleonsParser::MigrateRuleContext * /*ctx*/) override { }
  virtual void exitMigrateRule(ChameleonsParser::MigrateRuleContext * /*ctx*/) override { }

  virtual void enterOriginCode(ChameleonsParser::OriginCodeContext * /*ctx*/) override { }
  virtual void exitOriginCode(ChameleonsParser::OriginCodeContext * /*ctx*/) override { }

  virtual void enterTargetCode(ChameleonsParser::TargetCodeContext * /*ctx*/) override { }
  virtual void exitTargetCode(ChameleonsParser::TargetCodeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

