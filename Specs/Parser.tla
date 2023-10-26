---- MODULE Parser ----
CONSTANTS NULL, Sentence
VARIABLES ast, sentence, parser, parseF

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

TypeInvariant ==
    /\ parser = [rdy |-> 1, sentence |-> NULL, ast |-> NULL]
    /\ sentence \in Sentence
    /\ ast = NULL

Init == /\ TypeInvariant
        /\ parser.rdy = 1
        /\ parser.sentence = NULL
        /\ parser.ast = NULL
        /\ parseF \in [Sentence -> TreeSamples]
        /\ sentence \in Sentence

Parsing ==
    /\ parser.rdy = 1
    /\ parser.ast = NULL
    /\ parser.sentence = NULL
    /\ parser' = [parser EXCEPT
                  !.rdy = 0,
                  !.sentence = sentence,
                  !.ast = parseF[sentence]]
    /\ UNCHANGED <<ast, sentence, parseF>>

RcvAst ==
    /\ parser.rdy = 0
    /\ parser.sentence # NULL
    /\ parser.ast # NULL
    /\ ast' = parser.ast
    /\ ast' \in TreeSamples
    /\ UNCHANGED <<sentence, parser, parseF>>

Next == Parsing \/ RcvAst

Spec == Init /\ [][Next]_<<parser, sentence, parser, parseF>>

=======================
