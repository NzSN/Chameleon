---- MODULE AnalyzerMain ----
EXTENDS Sequences
CONSTANT NULL

NodeIDS == 1..5
NodeTypes == {"PROG", "STMT", "DEFINE"}
NodeValues == 1..2 \union {NULL}

LOCAL INSTANCE Analyzer WITH
    NULL <- NULL,
    node_ids <- NodeIDS,
    node_types <- NodeTypes,
    node_values <- NodeValues
LOCAL INSTANCE Tree WITH NULL <- NULL
LOCAL INSTANCE AnalyzerDefines WITH
    nodes_ids <- NodeIDS,
    node_types <- NodeTypes,
    node_values <- NodeValues

ParseTreeNodeRestrict ==
    [ID -> NodeIDS,
     Type -> NodeTypes,
     Value -> NodeValues,
     Status -> {"Unanalyzed"}]

ParseTreeSamples ==
    LET RootNode == [ID |-> 1, Type |-> "PROG", Value |-> NULL,
                     Status |-> "Unanalyzed"]
        NA == [ID |-> 2, Type |-> "STMT", Value |-> NULL,
               Status |-> "Unanalyzed"]
        NB == [ID |-> 3, Type |-> "DEFINE", Value |-> 1,
               Status |-> "Unanalyzed"]
        NC == [ID |-> 4, Type |-> "STMT", Value |-> NULL,
               Status |-> "Unanalyzed"]
        ND == [ID |-> 5, Type |-> "DEFINE", Value |-> 1,
               Status |-> "Unanalyzed"]
    IN <<
        [RootNode |-> <<NA,NB>>,
         NA |-> <<NB>>,
         NB |-> <<>>,
         NC |-> <<ND>>,
         ND |-> <<>>]
       >>

=============================
