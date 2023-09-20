---- MODULE Parser ----
CONSTANT
    \* Our Parser will bridge it's implementation
    \* to existing Parser, e.g, Antlr4 or Treesitter.
    ExternalParser,
    Sources,
    PT_Nodes,
    ExternalTree,

    \* Tree's CONSTANTS
    NULL,
    ET_CONVERT

LOCAL INSTANCE Tree WITH NULL <- NULL, ET <- ExternalTree,
    ET_CONVERT <- ET_CONVERT

\* Assume that BridgedParser is in set of function
\* that transform Source to ExternalTree
ASSUME ExternalParser \in [Sources -> ExternalTree]

(*--algorithm Parse
variables source \in Sources, externalTree, tree;

define
  Parser(p) == [Source -> Tree(PT_Nodes)]
end define;

begin
  \* First transform source code into ExternalTree
  externalTree := ExternalParser[source];

  \* Convert ExternalTree to Tree the defined in Chameleon
  tree := Convert(externalTree)
end algorithm; *)
\* BEGIN TRANSLATION (chksum(pcal) = "749e7f72" /\ chksum(tla) = "62fa1265")
CONSTANT defaultInitValue VARIABLES source, externalTree, tree, pc

(* define statement *)
Parser(p) == [Source -> Tree(PT_Nodes)]


vars == << source, externalTree, tree, pc >>

Init == (* Global variables *)
        /\ source \in Sources
        /\ externalTree = defaultInitValue
        /\ tree = defaultInitValue
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ externalTree' = ExternalParser[source]
         /\ tree' = Convert(externalTree')
         /\ pc' = "Done"
         /\ UNCHANGED source

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 

=======================
