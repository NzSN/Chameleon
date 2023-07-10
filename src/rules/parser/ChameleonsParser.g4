parser grammar ChameleonsParser;

options { tokenVocab=ChameleonsLexer; }

migrate
    : migrateRules
    ;

migrateRules
    : migrateRule
    | migrateRule migrateRules
    ;

migrateRule
    : IDENTIFIER COLON OPENBRACE originCode CLOSEBRACE TRANSFORM OPENBRACE targetCode CLOSEBRACE
    ;

originCode
    : CODEBYTES
    ;

targetCode
    : CODEBYTES
    ;
