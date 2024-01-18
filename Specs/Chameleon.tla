----- MODULE Chameleon -----
CONSTANTS NULL, Rule, ParseTree, RuleConfig
VARIABLES parser, transformer, state


LOCAL INSTANCE TLC
LOCAL INSTANCE Naturals
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

Sentence == 1..3

\* Definition of states
INIT         == 0
PARSING      == 1
PARSED       == 2
TRANSFORMING == 3
TRANSFORMED  == 4

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
  ParseTree <- ParseTree,
  RuleConfig <- RuleConfig

TypeInvariant ==
    /\ state = INIT
    /\ parser = [rdy |-> 1, sentence |-> NULL, ast |-> NULL]
    /\ ParserInst!TypeInvariant

Init == /\ TypeInvariant
        /\ ParserInst!Init
        /\ TransformerInst!Init

Parsing == /\ \E s \in Sentence: ParserInst!Parsing(s)
           /\ state = INIT
           /\ state' = PARSING
           /\ UNCHANGED <<transformer>>

ParseDone == /\ ParserInst!ParseDone
             /\ state = PARSING
             /\ state' = PARSED
             /\ UNCHANGED <<transformer>>

Transforming ==
  /\ \E config \in RuleConfig:
    TransformerInst!Transforming(parser.ast, config)
  /\ state = PARSED
  /\ state' = TRANSFORMING
  /\ UNCHANGED <<parser>>

TransDone ==
  /\ TransformerInst!TransDone
  /\ transformer.out \in ParseTree
  /\ state = TRANSFORMING
  /\ state' = TRANSFORMED
  /\ UNCHANGED <<parser, transformer>>

DONE ==
  /\ state = TRANSFORMED
  /\ UNCHANGED <<parser, transformer, state>>

Next == \/ Parsing
        \/ ParseDone
        \/ Transforming
        \/ TransDone
        \/ DONE

Spec == Init /\ [][Next]_<<parser, transformer, state>>
==========================
