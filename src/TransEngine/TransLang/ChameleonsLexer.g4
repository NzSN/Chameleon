lexer grammar ChameleonsLexer;

IDENTIFIER
    : [a-zA-Z][a-zA-Z0-9]*
    ;
COLON: ':';
OPENBRACE: '{|' -> mode(PROGRAM);
BEGIN_TERM: '%' -> mode(TERM);
TRANSFORM: '=>';
WS: [ \t\r\n]+ -> skip;

// ------------------------- Command -----------------------------
mode TERM;
TERM_VAR: [a-zA-Z][a-zA-Z0-9]*;
TERM_FUN: [a-zA-Z][a-zA-Z0-9]*();
END_TERM: '%' -> mode(DEFAULT_MODE);

// ---------------------------------------------------------------


// -------------------------- Program ----------------------------
mode PROGRAM;
CODEBYTES
    : ((~[|])|'\\|')+
    ;
CLOSEBRACE: '|}' -> mode(DEFAULT_MODE);
//------------------------------------------------------------------
