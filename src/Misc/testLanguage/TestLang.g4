grammar TestLang;
prog:   expr ;
expr:   expr ('*'|'/') expr
    |   expr ('+'|'-') expr
    |   INT
    |   PLACEHOLDER
    |   '(' expr ')'
    ;
NEWLINE : [\r\n]+ ;
INT     : [0-9]+ ;
PLACEHOLDER: [a-z];
