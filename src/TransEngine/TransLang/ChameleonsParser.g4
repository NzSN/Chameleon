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
    : IDENTIFIER COLON OPENBRACE sourcePattern CLOSEBRACE TRANSFORM OPENBRACE targetPattern CLOSEBRACE
    ;

sourcePattern
    : CODEBYTES
    ;

targetPattern
    : CODEBYTES
    ;
