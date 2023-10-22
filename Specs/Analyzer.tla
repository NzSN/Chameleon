---- MODULE Analyzer ----
CONSTANTS NULL

LOCAL INSTANCE TLC
LOCAL INSTANCE AnalyzerDefines WITH NULL <- NULL
LOCAL INSTANCE AnalyzerAlgo WITH
    NULL <- NULL, Nodes <- (DOMAIN TreeSamples)

LOCAL AnalyzerDef == [rdy: {0,1}, ast: {NULL}, info: {NULL}]

(*--algorithm Analyzer
variables analyzer \in AnalyzerDef, ast \in TreeSamples, info;

define
  TypeInvariant == analyzer \in AnalyzerDef
end define;

begin
  if analyzer.rdy = 1 /\
     analyzer.info = NULL /\
     analyzer.ast = NULL then

    analyzer.rdy := 0;
    analyzer.ast := ast;
    analyzer.info := Analyze(ast);

  elsif analyzer.rdy = 0 /\
        analyzer.ast /= NULL /\
        analyzer.info /= NULL then
    info := analyzer.info;
  end if;

end algorithm; *)
\* BEGIN TRANSLATION (chksum(pcal) = "2fd0b303" /\ chksum(tla) = "335db649")
CONSTANT defaultInitValue
VARIABLES analyzer, ast, info, pc

(* define statement *)
TypeInvariant == analyzer \in AnalyzerDef


vars == << analyzer, ast, info, pc >>

Init == (* Global variables *)
        /\ analyzer \in AnalyzerDef
        /\ ast \in TreeSamples
        /\ info = defaultInitValue
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ IF analyzer.rdy = 1 /\
               analyzer.info = NULL /\
               analyzer.ast = NULL
               THEN /\ analyzer' = [analyzer EXCEPT !.rdy = 0]
                    /\ pc' = "Lbl_2"
                    /\ info' = info
               ELSE /\ IF analyzer.rdy = 0 /\
                          analyzer.ast /= NULL /\
                          analyzer.info /= NULL
                          THEN /\ info' = analyzer.info
                          ELSE /\ TRUE
                               /\ info' = info
                    /\ pc' = "Done"
                    /\ UNCHANGED analyzer
         /\ ast' = ast

Lbl_2 == /\ pc = "Lbl_2"
         /\ analyzer' = [analyzer EXCEPT !.ast = ast]
         /\ pc' = "Lbl_3"
         /\ UNCHANGED << ast, info >>

Lbl_3 == /\ pc = "Lbl_3"
         /\ analyzer' = [analyzer EXCEPT !.info = Analyze(ast)]
         /\ pc' = "Done"
         /\ UNCHANGED << ast, info >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1 \/ Lbl_2 \/ Lbl_3
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 


=========================
