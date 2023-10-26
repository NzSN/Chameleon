---- MODULE ParserMain ----
EXTENDS Parser

LOCAL INSTANCE Naturals
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

ParseFunc[s \in Sentence] ==
    LET T == CHOOSE t \in TreeSamples: TRUE
    IN T

SentenceConst == 1..3
Parser == [rdy |-> 1, sentence |-> NULL, ast |-> NULL]
===========================
