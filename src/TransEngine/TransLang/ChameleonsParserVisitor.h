
// Generated from ./ChameleonsParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "ChameleonsParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ChameleonsParser.
 */
class  ChameleonsParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ChameleonsParser.
   */
    virtual std::any visitProg(ChameleonsParser::ProgContext *context) = 0;

    virtual std::any visitTargetSection(ChameleonsParser::TargetSectionContext *context) = 0;

    virtual std::any visitRuleSection(ChameleonsParser::RuleSectionContext *context) = 0;

    virtual std::any visitStrategySection(ChameleonsParser::StrategySectionContext *context) = 0;

    virtual std::any visitRewriteRules(ChameleonsParser::RewriteRulesContext *context) = 0;

    virtual std::any visitRewriteRule(ChameleonsParser::RewriteRuleContext *context) = 0;

    virtual std::any visitSourcePattern(ChameleonsParser::SourcePatternContext *context) = 0;

    virtual std::any visitTargetPattern(ChameleonsParser::TargetPatternContext *context) = 0;

    virtual std::any visitWhereExprs(ChameleonsParser::WhereExprsContext *context) = 0;

    virtual std::any visitCondExprs(ChameleonsParser::CondExprsContext *context) = 0;

    virtual std::any visitCondExpr(ChameleonsParser::CondExprContext *context) = 0;

    virtual std::any visitCallExpr(ChameleonsParser::CallExprContext *context) = 0;

    virtual std::any visitArguments(ChameleonsParser::ArgumentsContext *context) = 0;


};

