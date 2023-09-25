---- MODULE Analyzer ----
CONSTANT NULL, node_ids, node_types, node_values

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE Tree WITH NULL <- NULL
LOCAL INSTANCE AnalyzerDefines WITH
  node_ids <- node_ids,
  node_types <- node_types,
  node_values <- node_values

(*--algorithm Analyze
variables
  parsetree,
  analyze;

define

  AnalyzeImpls ==
    [Tree(ParseTreeNodes) \X ParseTreeNodes ->
     {[tree |-> t, info |-> i, status |-> s]:
        t \in Tree(ParseTreeNodes),
        i \in ParsedData,
        s \in ParseTreeNodesStatus} \union {NULL}]

  \* Return NULL if failed to analyzing.
  ASSUME analyze \in AnalyzeImpls

  LOCAL DoAnalyze(T) ==
    LET
      rootNode == GetRoot(T)
      Analyzing[tree \in Tree(ParseTreeNodes),
                node_ \in ParseTreeNodes] ==
        LET result == analyze[T, node_]

            AnalyzingChildren[T \in Tree(ParseTreeNodes),
                              node__ \in ParseTreeNodes,
                              idx \in Nat] ==
              IF idx < NumOfChild(T, node__)
              THEN LET current_result == Analyzing[T, GetChild(T, node__, idx)]
                       remains == AnalyzingChildren[T, nodes__, idx+1]
                   IN  IF remains /= NULL
                       THEN MergeDatas[current_result, remains]
                       ELSE NULL
              ELSE NULL

        IN  IF IsAnalyzing[result[status]]
            \* Some of children still unanalyzed.
            THEN
              IF NumOfChild(tree, node_) > 0
              THEN LET result_children == AnalyzingChildren(tree, node_, 1)
                   IN  IF result_children /= NULL
                       THEN MergeDatas[result, result_children]
                       ELSE Assert(FALSE, "Failed to parse children")
              ELSE Assert(FALSE, "Failed to analyze node")
            ELSE
              IF IsAnalyzeFinished[result[status]]
              THEN result[info]
              ELSE Assert(FALSE, "Failed to analyze node")

  \* Analyze the tree which root
  \* node as parameter.
  Analyze(T) ==
    IF node \in Nodes
    THEN DoAnalyze(T)
    \* Invalid node
    ELSE NULL

  ASSUME parsetree \in Tree(Node)
end define;

begin
  \* Algorithm

end algorithm; *)
\* BEGIN TRANSLATION (chksum(pcal) = "2de0fdbd" /\ chksum(tla) = "c46cb130")
CONSTANT defaultInitValue
VARIABLES node_ids, node_types, node_values, parsetree, analyze, infos, pc

(* define statement *)
Node == {[ID |-> ident, Type |-> type, Value |-> value,

          State |-> {"Pending", "Processing", "Done"}]:
         ident \in node_ids, type \in node_types, value \in node_values}

ASSUME parsetree \in Tree(Node)


vars == << node_ids, node_types, node_values, parsetree, analyze, infos, pc
        >>

Init == (* Global variables *)
        /\ node_ids = defaultInitValue
        /\ node_types = defaultInitValue
        /\ node_values = defaultInitValue
        /\ parsetree = defaultInitValue
        /\ analyze = defaultInitValue
        /\ infos = defaultInitValue
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ LET root == GetRoot(parsetree) IN
              parsetree' = root
         /\ pc' = "Done"
         /\ UNCHANGED << node_ids, node_types, node_values, analyze, infos >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION

========================
