----- MODULE Chameleon -----
CONSTANTS NULL
VARIABLES parser, analyzer


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

TypeInvariant ==
    /\ parser = [rdy |-> 1, sentence |-> NULL, ast |-> NULL]
    /\ ParserInst!TypeInvariant
    /\ analyzer = [rdy |-> 1, ast |-> NULL, info |-> NULL]

Init == /\ TypeInvariant
        /\ ParserInst!Init
        /\ AnalyzerInst!Init

Parsing == /\ \E s \in Sentence: ParserInst!Parsing(s)
           /\ UNCHANGED analyzer

ParsedDone == /\ ParserInst!ParsedDone
              /\ UNCHANGED analyzer

Analyzing == /\ AnalyzerInst!Analyzing(parser.ast)
             /\ UNCHANGED parser

AnalyzedDone == /\ AnalyzerInst!AnalyzedDone
                /\ PrintT(analyzer)
                /\ UNCHANGED parser

Next == Parsing \/ ParsedDone \/ Analyzing \/ AnalyzedDone

Spec == Init /\ [][Next]_<<parser, analyzer>>
==========================
