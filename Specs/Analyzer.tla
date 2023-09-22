---- MODULE Analyzer ----
CONSTANT NULL

LOCAL INSTANCE TLC
LOCAL INSTANCE Tree WITH NULL <- NULL


(*--algorithm Analyze
variables
  node_ids,
  node_types,
  node_values,
  parsetree,
  analyze,
  infos;

define
  Node == {[ID |-> ident, Type |-> type, Value |-> value,
            \* Property to control traverse action
            State |-> {"Pending", "Processing", "Done"}]:
           ident \in node_ids, type \in node_types, value \in node_values}

  \* Analyze the tree which root
  \* node as parameter.
  Analyze(node) ==


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
