---- MODULE AnalyzerMain ----
EXTENDS Sequences, Naturals
CONSTANT NULL

LOCAL INSTANCE FiniteSets
LOCAL INSTANCE TLC

NodeIDS == 1..5
NodeTypes == {"T1", "T2", "T3"}
NodeValues == 1..2 \union {NULL}

LOCAL INSTANCE AnalyzerDefines WITH
    node_ids <- NodeIDS,
    node_types <- NodeTypes,
    node_values <- NodeValues
LOCAL INSTANCE Tree WITH NULL <- NULL
LOCAL analyze[T \in Tree(ParseTreeNodes),
        N \in ParseTreeNodes] ==
    [tree |-> Singleton(ParseTreeNode[1, "T1", 1]),
     info |-> [F1 |-> <<1>>],
     status |-> "Unanalyzed"]

LOCAL INSTANCE Analyzer WITH
    NULL <- NULL,
    node_ids <- NodeIDS,
    node_types <- NodeTypes,
    node_values <- NodeValues,
    analyze <- analyze

LOCAL CODOMAIN(f) ==
    {f[x]: x \in DOMAIN f}

ParseTreeNodeRestrict ==
    {[ID |-> ident,
      Type |-> type,
      Value |-> value,
      Status |-> {"Unanalyzed"}]:
        ident \in NodeIDS,
        type  \in NodeTypes,
        value \in NodeValues}

ParseTreeSamples ==
    {s \in [1..4 -> ParseTreeNodeRestrict]:
     \A x \in CODOMAIN(s):
     \A y \in CODOMAIN(s): x.ID /= y.ID}

Valid == \A x \in ParseTreeSamples:
    /\ PrintT(x)

=============================
