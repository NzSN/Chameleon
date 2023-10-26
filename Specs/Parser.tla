---- MODULE Parser ----
CONSTANTS NULL, Sentence, parseF
VARIABLES parser

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

TypeInvariant ==
    /\ parser = [rdy |-> 1,
                 sentence |-> NULL,
                 ast |-> NULL]

Init == /\ TypeInvariant
        /\ parser.rdy = 1
        /\ parser.sentence = NULL
        /\ parser.ast = NULL
        /\ parseF \in [Sentence -> TreeSamples]

Parsing(sentence) ==
    /\ parser.rdy = 1
    /\ parser.ast = NULL
    /\ parser.sentence = NULL
    /\ parser' = [parser EXCEPT
                  !.rdy = 0,
                  !.sentence = sentence,
                  !.ast = parseF[sentence]]

ParseDone ==
    /\ parser.rdy = 0
    /\ parser.sentence # NULL
    /\ parser.ast # NULL
    /\ UNCHANGED <<parser>>

Next == \E s \in Sentence: Parsing(s) \/ ParseDone

Spec == Init /\ [][Next]_<<parser>>

=======================
