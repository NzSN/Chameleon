---- MODULE Parser ----
CONSTANT Source, AST, NULL

(*--algorithm Parser
variables parser, source \in Source, ast \in AST;

define
  TypeInvariant == parser \in [rdy: {0,1},
                               src: Source \union {NULL},
                               ast: AST \union {NULL},
                               parse: [Source -> AST]]
end define;

begin
  if parser.rdy = 1 /\
     parser.src = NULL /\
     parser.ast = NULL then

    parser.src := source;
    parser.ast := parser.parse[source];
    parser.rdy := 0;
  elsif parser.rdy = 0 /\
        parser.src /= NULL /\
        parser.ast /\ NULL then

    \* We don't require parser reset to initial state
    \* which imply that we don't require reusability for
    \* Parser.
    ast := parser.ast;

  end if;
end algorithm; *)
\* BEGIN TRANSLATION (chksum(pcal) = "e1e35d14" /\ chksum(tla) = "6ca7e0ad")
CONSTANT defaultInitValue
VARIABLES parser, source, ast, pc

(* define statement *)
TypeInvariant == parser \in [rdy: {0,1},
                             src: Source \union {NULL},
                             ast: AST \union {NULL},
                             parse: [Source -> AST]]


vars == << parser, source, ast, pc >>

Init == (* Global variables *)
        /\ parser = defaultInitValue
        /\ source \in Source
        /\ ast \in AST
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ IF parser.rdy = 1 /\
               parser.src = NULL /\
               parser.ast = NULL
               THEN /\ parser' = [parser EXCEPT !.src = source]
                    /\ pc' = "Lbl_2"
                    /\ ast' = ast
               ELSE /\ IF parser.rdy = 0 /\
                          parser.src /= NULL /\
                          parser.ast /\ NULL
                          THEN /\ ast' = parser.ast
                          ELSE /\ TRUE
                               /\ ast' = ast
                    /\ pc' = "Done"
                    /\ UNCHANGED parser
         /\ UNCHANGED source

Lbl_2 == /\ pc = "Lbl_2"
         /\ parser' = [parser EXCEPT !.ast = parser.parse[source]]
         /\ pc' = "Lbl_3"
         /\ UNCHANGED << source, ast >>

Lbl_3 == /\ pc = "Lbl_3"
         /\ parser' = [parser EXCEPT !.rdy = 0]
         /\ pc' = "Done"
         /\ UNCHANGED << source, ast >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1 \/ Lbl_2 \/ Lbl_3
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 

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
