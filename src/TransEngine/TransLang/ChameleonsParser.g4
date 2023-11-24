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
    | TERM_VAR
    | STRING
    ;

callExpr
    : IDENTIFIER LBRACE arguments RBRACE
    ;

arguments
    : TERM_VAR
    | TERM_VAR COMMA arguments
    ;
