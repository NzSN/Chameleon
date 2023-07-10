lexer grammar ChameleonsLexer;

IDENTIFIER
    : [a-zA-Z][a-zA-Z0-9]*
    ;

CODEBYTES
    : ([^{}]|('\\' '}'))+
    ;

COLON: ':';
OPENBRACE: '{';
CLOSEBRACE: '}';
TRANSFORM: '=>';
