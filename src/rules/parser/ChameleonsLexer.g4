lexer grammar ChameleonsLexer;

IDENTIFIER
    : [a-zA-Z][a-zA-Z0-9]*
    ;
COLON: ':';
OPENBRACE: '{' -> mode(PROGRAM);
TRANSFORM: '=>';
WS: [ \t\r\n]+ -> skip;

mode PROGRAM;
CODEBYTES
    : ((~[{}])|'\\{'|'\\}')+
    ;
CLOSEBRACE: '}' -> mode(DEFAULT_MODE);
