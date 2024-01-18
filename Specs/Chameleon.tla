----- MODULE Chameleon -----
CONSTANTS NULL, Rule, ParseTree
VARIABLES parser, transformer, state


LOCAL INSTANCE TLC
LOCAL INSTANCE Naturals
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

Sentence == 1..3

ParseFunc[s \in Sentence] == CHOOSE t \in ParseTree: TRUE

ParserInst == INSTANCE Parser WITH
  NULL <- NULL,
  \* Type of Sentence of
  Sentence <- Sentence,
  parseF <- ParseFunc,
  parser <- parser,
  ParseTree <- ParseTree

TransformerInst == INSTANCE Transformer WITH
  NULL <- NULL,
  Rule <- Rule,
  transformer <- transformer,
  ParseTree <- ParseTree


TypeInvariant ==
    /\ state = 0
    /\ parser = [rdy |-> 1, sentence |-> NULL, ast |-> NULL]
    /\ ParserInst!TypeInvariant

Init == /\ TypeInvariant
        /\ ParserInst!Init
        /\ TransformerInst!Init

Parsing == /\ \E s \in Sentence: ParserInst!Parsing(s)
           /\ state = 0
           /\ state' = 1
           /\ UNCHANGED <<transformer>>

ParseDone == /\ ParserInst!ParseDone
              /\ state = 1
              /\ state' = 2
              /\ UNCHANGED <<transformer>>

Transforming ==
  /\ \E rule \in Rule:
    TransformerInst!Transforming(parser.ast, rule)
  /\ state = 2
  /\ state' = 3
  /\ UNCHANGED <<parser>>

TransDone ==
  /\ TransformerInst!TransDone
  /\ state = 3
  /\ UNCHANGED <<parser, state, transformer>>

Next == \/ Parsing
        \/ ParseDone
        \/ Transforming
        \/ TransDone

Spec == Init /\ [][Next]_<<parser, transformer, state>>
==========================
