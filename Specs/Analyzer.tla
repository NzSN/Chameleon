---- MODULE Analyzer ----
EXTENDS Sequences, Naturals, FiniteSets
CONSTANTS NULL
VARIABLES analyzer

LOCAL INSTANCE TLC
LOCAL INSTANCE TreeSamples WITH NULL <- NULL
LOCAL INSTANCE AnalyzerAlgo WITH
    NULL <- NULL, Nodes <- (DOMAIN TreeSamples)

TypeInvariant ==
    /\ analyzer = [rdy |-> 1, ast |-> NULL, info |-> NULL]

Init == /\ TypeInvariant
        /\ analyzer.rdy = 1
        /\ analyzer.info = NULL
        /\ analyzer.ast = NULL

Analyzing(ast) ==
    /\ ast \in TreeSamples
    /\ analyzer.rdy = 1
    /\ analyzer.info = NULL
    /\ analyzer.ast = NULL
    /\ analyzer' = [analyzer EXCEPT
                    !.rdy = 0,
                    !.ast = ast,
                    !.info = Analyze(ast)]

AnalyzeDone == /\ analyzer.rdy = 0
           /\ analyzer.ast # NULL
           /\ analyzer.info # NULL
           /\ UNCHANGED <<analyzer>>

Next == \E t \in TreeSamples: Analyzing(t) \/ AnalyzeDone

Spec == Init /\ [][Next]_<<analyzer>>


=========================
