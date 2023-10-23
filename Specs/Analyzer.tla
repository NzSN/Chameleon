---- MODULE Analyzer ----
EXTENDS Sequences, Naturals, FiniteSets
CONSTANTS NULL
VARIABLES analyzer, ast, info

LOCAL INSTANCE TLC
LOCAL INSTANCE AnalyzerDefines WITH NULL <- NULL
LOCAL INSTANCE AnalyzerAlgo WITH
    NULL <- NULL, Nodes <- (DOMAIN TreeSamples)

LOCAL AnalyzerDef == [rdy: {0,1}, ast: {NULL}, info: {NULL}]

TypeInvariant == /\ analyzer \in AnalyzerDef
                 /\ ast \in TreeSamples
                 /\ info = <<>>

Init == /\ TypeInvariant
        /\ analyzer.rdy = 1
        /\ analyzer.info = NULL
        /\ analyzer.ast = NULL

Parsing == /\ analyzer.rdy = 1
           /\ analyzer.info = NULL
           /\ analyzer.ast = NULL
           /\ analyzer' = [analyzer EXCEPT
                           !.rdy = 0,
                           !.ast = ast,
                           !.info = Analyze(ast)]
           /\ UNCHANGED <<ast, info>>

RcvInfo == /\ analyzer.rdy = 0
           /\ analyzer.ast # NULL
           /\ analyzer.info # NULL
           /\ info' = <<analyzer.info>>
           /\ UNCHANGED <<ast, analyzer>>

Next == Parsing \/ RcvInfo

Spec == Init /\ [][Next]_<<analyzer, info, ast>>


=========================
