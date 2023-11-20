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
    | condExpr LOGICOP condExprs
    ;

condExpr
    : TERM_VAR ORDEROP TERM_VAR
    | TERM_VAR ORDEROP NUMBER
    ;
