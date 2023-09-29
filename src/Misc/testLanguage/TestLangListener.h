
// Generated from TestLang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "TestLangParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by TestLangParser.
 */
class  TestLangListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(TestLangParser::ProgContext *ctx) = 0;
  virtual void exitProg(TestLangParser::ProgContext *ctx) = 0;

  virtual void enterExpr(TestLangParser::ExprContext *ctx) = 0;
  virtual void exitExpr(TestLangParser::ExprContext *ctx) = 0;


};

