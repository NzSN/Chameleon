
// Generated from ./ChameleonsParser.g4 by ANTLR 4.13.1

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

  virtual void enterRewriteRules(ChameleonsParser::RewriteRulesContext * /*ctx*/) override { }
  virtual void exitRewriteRules(ChameleonsParser::RewriteRulesContext * /*ctx*/) override { }

  virtual void enterRewriteRule(ChameleonsParser::RewriteRuleContext * /*ctx*/) override { }
  virtual void exitRewriteRule(ChameleonsParser::RewriteRuleContext * /*ctx*/) override { }

  virtual void enterSourcePattern(ChameleonsParser::SourcePatternContext * /*ctx*/) override { }
  virtual void exitSourcePattern(ChameleonsParser::SourcePatternContext * /*ctx*/) override { }

  virtual void enterTargetPattern(ChameleonsParser::TargetPatternContext * /*ctx*/) override { }
  virtual void exitTargetPattern(ChameleonsParser::TargetPatternContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

