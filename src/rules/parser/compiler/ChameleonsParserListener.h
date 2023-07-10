
// Generated from ChameleonsParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "ChameleonsParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ChameleonsParser.
 */
class  ChameleonsParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterMigrate(ChameleonsParser::MigrateContext *ctx) = 0;
  virtual void exitMigrate(ChameleonsParser::MigrateContext *ctx) = 0;

  virtual void enterMigrateRules(ChameleonsParser::MigrateRulesContext *ctx) = 0;
  virtual void exitMigrateRules(ChameleonsParser::MigrateRulesContext *ctx) = 0;

  virtual void enterMigrateRule(ChameleonsParser::MigrateRuleContext *ctx) = 0;
  virtual void exitMigrateRule(ChameleonsParser::MigrateRuleContext *ctx) = 0;

  virtual void enterOriginCode(ChameleonsParser::OriginCodeContext *ctx) = 0;
  virtual void exitOriginCode(ChameleonsParser::OriginCodeContext *ctx) = 0;

  virtual void enterTargetCode(ChameleonsParser::TargetCodeContext *ctx) = 0;
  virtual void exitTargetCode(ChameleonsParser::TargetCodeContext *ctx) = 0;


};

