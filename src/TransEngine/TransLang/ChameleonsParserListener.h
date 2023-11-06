
// Generated from ./ChameleonsParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "ChameleonsParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ChameleonsParser.
 */
class  ChameleonsParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(ChameleonsParser::ProgContext *ctx) = 0;
  virtual void exitProg(ChameleonsParser::ProgContext *ctx) = 0;

  virtual void enterTargetSection(ChameleonsParser::TargetSectionContext *ctx) = 0;
  virtual void exitTargetSection(ChameleonsParser::TargetSectionContext *ctx) = 0;

  virtual void enterRuleSection(ChameleonsParser::RuleSectionContext *ctx) = 0;
  virtual void exitRuleSection(ChameleonsParser::RuleSectionContext *ctx) = 0;

  virtual void enterStrategySection(ChameleonsParser::StrategySectionContext *ctx) = 0;
  virtual void exitStrategySection(ChameleonsParser::StrategySectionContext *ctx) = 0;

  virtual void enterRewriteRules(ChameleonsParser::RewriteRulesContext *ctx) = 0;
  virtual void exitRewriteRules(ChameleonsParser::RewriteRulesContext *ctx) = 0;

  virtual void enterRewriteRule(ChameleonsParser::RewriteRuleContext *ctx) = 0;
  virtual void exitRewriteRule(ChameleonsParser::RewriteRuleContext *ctx) = 0;

  virtual void enterSourcePattern(ChameleonsParser::SourcePatternContext *ctx) = 0;
  virtual void exitSourcePattern(ChameleonsParser::SourcePatternContext *ctx) = 0;

  virtual void enterTargetPattern(ChameleonsParser::TargetPatternContext *ctx) = 0;
  virtual void exitTargetPattern(ChameleonsParser::TargetPatternContext *ctx) = 0;

  virtual void enterCondExprs(ChameleonsParser::CondExprsContext *ctx) = 0;
  virtual void exitCondExprs(ChameleonsParser::CondExprsContext *ctx) = 0;

  virtual void enterCondExpr(ChameleonsParser::CondExprContext *ctx) = 0;
  virtual void exitCondExpr(ChameleonsParser::CondExprContext *ctx) = 0;


};

