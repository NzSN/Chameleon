
// Generated from TestLang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "TestLangListener.h"


/**
 * This class provides an empty implementation of TestLangListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  TestLangBaseListener : public TestLangListener {
public:

  virtual void enterProg(TestLangParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(TestLangParser::ProgContext * /*ctx*/) override { }

  virtual void enterExpr(TestLangParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(TestLangParser::ExprContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

