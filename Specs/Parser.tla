---- MODULE Parser ----
CONSTANT Source, AST, NULL
VARIABLE parser

TypeInvariant == Parser \in [rdy: {0,1},
                             src: Source \union {NULL},
                             ast: AST \union {NULL},
                             parse: [Source -> AST]]

Init == /\ TypeInvariant
        /\ parser.rdy = 1
        /\ parser.src = NULL
        /\ parser.ast = NULL

Parse(s) == /\ parser.rdy = 1
            /\ parser.src = NULL
            /\ parser.ast = NULL
            /\ parser' = [parser EXCEPT !.rdy = 0, !.source = s, !.ast = @.parse[@.src]]

\* We don't require reusability of parser.
GetAST == /\ parser.rdy = 0
          /\ parser.src # NULL
          /\ parser.ast # NULL

Next == (\exists s \in Source: Parse(s)) \/ GetAST
Spec == Init /\ [][Next]_parser
=======================
