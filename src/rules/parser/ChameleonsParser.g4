parser grammar ChameleonsParser;

tokens { IDENTIFIER, CODEBYTES, COLON, OPENBRACE, CLOSEBRACE, TRANSFORM }

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
