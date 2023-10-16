parser grammar ChameleonsParser;

options { tokenVocab=ChameleonsLexer; }

prog
    : rewriteRules
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
      WHERE condExprs
    ;

sourcePattern
    : CODEBYTES
    ;

targetPattern
    : CODEBYTES
    ;

condExprs
    : condExpr
    | condExpr LOGICOP condExprs
    ;

condExpr
    : TERM_VAR ORDEROP TERM_VAR
    | TERM_VAR ORDEROP NUMBER
    ;
