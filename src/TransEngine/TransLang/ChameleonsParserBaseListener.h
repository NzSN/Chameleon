
// Generated from ./ChameleonsParser.g4 by ANTLR 4.13.0

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

  virtual void enterProg(ChameleonsParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(ChameleonsParser::ProgContext * /*ctx*/) override { }

  virtual void enterTargetSection(ChameleonsParser::TargetSectionContext * /*ctx*/) override { }
  virtual void exitTargetSection(ChameleonsParser::TargetSectionContext * /*ctx*/) override { }

  virtual void enterRuleSection(ChameleonsParser::RuleSectionContext * /*ctx*/) override { }
  virtual void exitRuleSection(ChameleonsParser::RuleSectionContext * /*ctx*/) override { }

  virtual void enterStrategySection(ChameleonsParser::StrategySectionContext * /*ctx*/) override { }
  virtual void exitStrategySection(ChameleonsParser::StrategySectionContext * /*ctx*/) override { }

  virtual void enterRewriteRules(ChameleonsParser::RewriteRulesContext * /*ctx*/) override { }
  virtual void exitRewriteRules(ChameleonsParser::RewriteRulesContext * /*ctx*/) override { }

  virtual void enterRewriteRule(ChameleonsParser::RewriteRuleContext * /*ctx*/) override { }
  virtual void exitRewriteRule(ChameleonsParser::RewriteRuleContext * /*ctx*/) override { }

  virtual void enterSourcePattern(ChameleonsParser::SourcePatternContext * /*ctx*/) override { }
  virtual void exitSourcePattern(ChameleonsParser::SourcePatternContext * /*ctx*/) override { }

  virtual void enterTargetPattern(ChameleonsParser::TargetPatternContext * /*ctx*/) override { }
  virtual void exitTargetPattern(ChameleonsParser::TargetPatternContext * /*ctx*/) override { }

  virtual void enterWhereExprs(ChameleonsParser::WhereExprsContext * /*ctx*/) override { }
  virtual void exitWhereExprs(ChameleonsParser::WhereExprsContext * /*ctx*/) override { }

  virtual void enterCondExprs(ChameleonsParser::CondExprsContext * /*ctx*/) override { }
  virtual void exitCondExprs(ChameleonsParser::CondExprsContext * /*ctx*/) override { }

  virtual void enterCondExpr(ChameleonsParser::CondExprContext * /*ctx*/) override { }
  virtual void exitCondExpr(ChameleonsParser::CondExprContext * /*ctx*/) override { }

  virtual void enterCallExpr(ChameleonsParser::CallExprContext * /*ctx*/) override { }
  virtual void exitCallExpr(ChameleonsParser::CallExprContext * /*ctx*/) override { }

  virtual void enterArguments(ChameleonsParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(ChameleonsParser::ArgumentsContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

