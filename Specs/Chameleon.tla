----- MODULE Chameleon -----
CONSTANTS NULL, RuleConfig, Rule
VARIABLES parser, analyzer, transformer, state


LOCAL INSTANCE TLC
LOCAL INSTANCE Naturals
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

Sentence == 1..3

ParseFunc[s \in Sentence] == CHOOSE t \in TreeSamples: TRUE

ParserInst == INSTANCE Parser WITH
  NULL <- NULL,
  \* Type of Sentence of
  Sentence <- Sentence,
  parseF <- ParseFunc,
  parser <- parser

AnalyzerInst == INSTANCE Analyzer WITH
  NULL <- NULL,
  analyzer <- analyzer

TransformerInst == INSTANCE Transformer WITH
  NULL <- NULL,
  RuleConfig <- RuleConfig,
  Rule <- Rule,
  transformer <- transformer


TypeInvariant ==
    /\ state = 0
    /\ parser = [rdy |-> 1, sentence |-> NULL, ast |-> NULL]
    /\ analyzer = [rdy |-> 1, ast |-> NULL, info |-> NULL]
    /\ ParserInst!TypeInvariant
    /\ AnalyzerInst!TypeInvariant

Init == /\ TypeInvariant
        /\ ParserInst!Init
        /\ AnalyzerInst!Init
        /\ TransformerInst!Init

Parsing == /\ \E s \in Sentence: ParserInst!Parsing(s)
           /\ state = 0
           /\ state' = 1
           /\ UNCHANGED <<analyzer, transformer>>

ParseDone == /\ ParserInst!ParseDone
              /\ state = 1
              /\ state' = 2
              /\ UNCHANGED <<analyzer, transformer>>

Analyzing == /\ AnalyzerInst!Analyzing(parser.ast)
             /\ state = 2
             /\ state' = 3
             /\ UNCHANGED <<parser, transformer>>

AnalyzeDone == /\ AnalyzerInst!AnalyzeDone
                /\ state = 3
                /\ state' = 4
                /\ UNCHANGED <<parser, transformer>>

ParseRuleConfig ==
  /\ \E config \in RuleConfig: TransformerInst!ParseRuleConfig(config)
  /\ state = 4
  /\ state' = 5
  /\ UNCHANGED <<parser, analyzer>>

Transforming ==
  /\ TransformerInst!Transforming(analyzer.info, parser.ast)
  /\ state = 5
  /\ state' = 6
  /\ UNCHANGED <<parser, analyzer>>

TransDone ==
  /\ TransformerInst!TransDone
  /\ state = 6
  /\ UNCHANGED <<parser, analyzer, state>>

Next == \/ Parsing \/ ParseDone \/ Analyzing \/ AnalyzeDone
        \/ ParseRuleConfig \/ Transforming \/ TransDone

Spec == Init /\ [][Next]_<<parser, analyzer, transformer, state>>
==========================
