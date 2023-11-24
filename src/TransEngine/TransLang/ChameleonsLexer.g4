lexer grammar ChameleonsLexer;

TARGET_TAG: 'TARGET:';
RULE_TAG: 'RULES:';
STRATEGY_TAG: 'STRATEGIES';
WHERE: 'where' -> mode(WHERE_CLAUSE);
IDENTIFIER
    : [a-zA-Z][a-zA-Z0-9]*
    ;
COLON: ':';
OPENBRACE: '{|' -> mode(PROGRAM);
TRANSFORM: '=>';
WS: [ \t\r\n]+ -> skip;

// -------------------------- Program ----------------------------
mode PROGRAM;
CODEBYTES
    : ((~[|])|'\\|')+
    ;
CLOSEBRACE: '|}' -> mode(DEFAULT_MODE);
//----------------------------------------------------------------

// -------------------------- Where Clause -----------------------
mode WHERE_CLAUSE;
WHERE_EXPR_SEPERATOR: ';';

LOGICOP: ('AND' | 'OR' | 'NOT');
ORDEROP: ('=' | '<' | '>' | '<=' | '>=');

ASSIGN: ':=';

LBRACE: '(';
RBRACE: ')';

COMMA: ',';

STRING: '"' [a-zA-Z0-9 ]+ '"';
TERM_VAR: [a-zA-Z]+;
WS_WHERE: [ \t\r\n]+ -> skip;
//----------------------------------------------------------------
