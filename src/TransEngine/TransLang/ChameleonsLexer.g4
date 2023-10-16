lexer grammar ChameleonsLexer;

WHERE: 'where';
LOGICOP: ('AND' | 'OR' | 'NOT');
ORDEROP: ('=' | '<' | '>' | '<=' | '>=');
NUMBER: [0-9]+;
IDENTIFIER
    : [a-zA-Z][a-zA-Z0-9]*
    ;
COLON: ':';
OPENBRACE: '{|' -> mode(PROGRAM);
TERM_VAR: '%' [a-zA-Z]+;
TRANSFORM: '=>';
WS: [ \t\r\n]+ -> skip;

// -------------------------- Program ----------------------------
mode PROGRAM;
CODEBYTES
    : ((~[|])|'\\|')+
    ;
CLOSEBRACE: '|}' -> mode(DEFAULT_MODE);
//----------------------------------------------------------------
