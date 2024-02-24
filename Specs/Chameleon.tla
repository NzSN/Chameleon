----- MODULE Chameleon -----
CONSTANTS NULL, Sentence, Rule, ParseTree, RuleConfig, ParseFunc
VARIABLES parser, transformer, state

LOCAL INSTANCE TLC
LOCAL INSTANCE Naturals

\* Definition of states
INIT         == 0
PARSING      == 1
PARSED       == 2
TRANSFORMING == 3
TRANSFORMED  == 4

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

Parsing ==
  \E s \in Sentence:
  /\ ParserInst!Parsing(s)
  /\ state = INIT
  /\ state' = PARSING
  /\ UNCHANGED <<transformer>>

ParseDone == /\ ParserInst!ParseDone
             /\ state = PARSING
             /\ state' = PARSED
             /\ UNCHANGED <<transformer>>

Transforming ==
  /\ \E config \in RuleConfig:
     \E t \in ParseTree:
    TransformerInst!Transforming(t, config)
  /\ state = PARSED
  /\ state' = TRANSFORMING
  /\ UNCHANGED <<parser>>

TransDone ==
  /\ TransformerInst!TransDone(transformer.out, transformer.config)
  /\ transformer.out \in ParseTree
  /\ state = TRANSFORMING
  /\ state' = TRANSFORMED
  /\ UNCHANGED <<parser, transformer>>

DONE ==
  /\ state = TRANSFORMED
  /\ UNCHANGED <<parser, transformer, state>>

Next ==
  \/ Parsing
  \/ ParseDone
  \/ Transforming
  \/ TransDone
  \/ DONE

Spec ==
  /\ Init
  /\ [][Next]_<<parser, transformer, state>>
==========================
