parser grammar Chameleons

migrateDesc
    : migrateRules
    ;

migrateRules
    : migrateRule
    | migrateRule migrateRules
    ;

migrateRule
    : ruleIdentifier colon openBrace originCode closeBrace semanticEquivalent openBrace targetCode closeBrace
    ;

originCode
    :
    ;

targetCode
    :
    ;
