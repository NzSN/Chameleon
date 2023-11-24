parser grammar ChameleonsParser;

options { tokenVocab=ChameleonsLexer; }

prog
    : targetSection
      ruleSection
    | targetSection
      ruleSection
      strategySection;

targetSection
    : TARGET_TAG IDENTIFIER;
ruleSection
    : RULE_TAG rewriteRules
    ;
// Optional section
strategySection
    : STRATEGY_TAG
    ;

rewriteRules
    : rewriteRule
    | rewriteRule rewriteRules
    ;

rewriteRule
    : IDENTIFIER COLON
      OPENBRACE sourcePattern CLOSEBRACE
      TRANSFORM
      OPENBRACE targetPattern CLOSEBRACE
    | IDENTIFIER COLON
      OPENBRACE sourcePattern CLOSEBRACE
      TRANSFORM
      OPENBRACE targetPattern CLOSEBRACE
      WHERE whereExprs
    ;

sourcePattern
    : CODEBYTES
    ;

targetPattern
    : CODEBYTES
    ;

whereExprs
    : condExprs
    | condExprs whereExprs
    ;

condExprs
    : condExpr WHERE_EXPR_SEPERATOR
    | condExpr condExprs
    ;

condExpr
    : condExpr ORDEROP condExpr
    | condExpr LOGICOP condExpr
    | callExpr
    | assignExpr
    | term
    | STRING
    ;

term
    : WHERE_IDENTIFIER
    ;

assignExpr
    : WHERE_IDENTIFIER ASSIGN condExpr
    ;

callExpr
    : WHERE_IDENTIFIER LBRACE arguments RBRACE
    ;

arguments
    : WHERE_IDENTIFIER
    | WHERE_IDENTIFIER COMMA arguments
    ;
