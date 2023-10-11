---- MODULE AnalyzerMain ----
EXTENDS Sequences, Naturals
CONSTANT NULL

LOCAL INSTANCE FiniteSets
LOCAL INSTANCE TLC

NodeIDS == 1..5
NodeTypes == {"PROG", "STMT", "DEFINE"}
NodeValues == 1..2 \union {NULL}

LOCAL INSTANCE AnalyzerDefines WITH
    node_ids <- NodeIDS,
    node_types <- NodeTypes,
    node_values <- NodeValues
LOCAL INSTANCE Tree WITH NULL <- NULL

LOCAL CODOMAIN(f) ==
    {f[x]: x \in DOMAIN f}

\* Thise sample exptected to be FALSE
TreeSample ==
  LET rootNode == ParseTreeNode[1, "PROG", NULL]
      node1 == ParseTreeNode[2, "STMT", NULL]
      node2 == ParseTreeNode[3, "DEFINE", 1]
      node3 == ParseTreeNode[4, "STMT", NULL]
      node4 == ParseTreeNode[5, "DEFINE", 2]
  IN  AddNode(
              AddNode(
                      AddNode(
                              AddNode(Singleton(rootNode),
                                      rootNode, node1),
                              node1, node2),
                      rootNode, node3),
              node3, node4)

LOCAL analyze[T \in Tree(DOMAIN TreeSample),
              N \in DOMAIN TreeSample] ==
  CASE N.Type = "PROG" ->
             [info |-> [F1 |-> <<>>, F2 |-> <<>>, NA |-> <<>>], status |-> "Analyzing"]
    [] N.Type = "STMT" ->
             [info |-> [F1 |-> <<>>, F2 |-> <<>>, NA |-> <<>>], status |-> "Analyzing"]
    [] N.Type = "DEFINE" ->
             [info |-> [F1 |-> <<N.Value>>, F2 |-> <<>>, NA |-> <<>>],
              status |-> "Done"]

LOCAL INSTANCE Analyzer WITH
    NULL <- NULL,
    node_ids <- NodeIDS,
    node_types <- NodeTypes,
    node_values <- NodeValues,
    analyze <- analyze

Valid == PrintT(Analyze(TreeSample))
=============================
