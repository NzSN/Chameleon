---- MODULE TreeSamples ----
CONSTANTS NULL

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE Sequences
LOCAL INSTANCE FiniteSets

LOCAL INSTANCE Tree WITH NULL <- NULL


LOCAL CODOMAIN(f) == {f[x]: x \in DOMAIN f}

ParseTreeNodeStatus == {"Unanalyzed", "Analyzing", "Done"}

IsUnanalyzed[s \in ParseTreeNodeStatus] ==
  s = "Unanalyzed"

IsAnalyzing[s \in ParseTreeNodeStatus] ==
  s = "Analyzing"

IsAnalyzeFinished[s \in ParseTreeNodeStatus] ==
  s = "Done"

NodeValue == {"a", "b", "c", "d", "e"}

ParseTreeNode[ident \in Nat, type \in {"S", "C"}, value \in NodeValue] ==
    [ID |-> ident, Type |-> type, Status |-> "Unanalyzed", Value |-> value]
SkipNode[ident \in Nat, value \in NodeValue] ==
    [ID |-> ident, Type |-> "S", Status |-> "Unanalyzed", Value |-> value]
ContinueNode[ident \in Nat, value \in NodeValue] ==
    [ID |-> ident, Type |-> "C", Status |-> "Unanalyzed", Value |-> value]


MAXIMUM_NUM_OF_NODES == 4

RECURSIVE TreeSample(_,_)
TreeSample(N, Root) ==
  LET NodeType == CHOOSE n \in {0,1}: TRUE
      Value == CHOOSE v \in NodeValue: TRUE
      Node == IF NodeType = 0 \* Skip
              THEN SkipNode[N, Value]
              ELSE ContinueNode[N, Value]
      AppendNode == CHOOSE n \in (DOMAIN Root): n.Type # "S"
  IN IF N > 0
     THEN TreeSample(N-1, AddNode(Root, AppendNode, Node))
     ELSE Root
TreeSamples ==
  LET Value == CHOOSE v \in NodeValue: TRUE
  IN {TreeSample(n, Singleton(ParseTreeNode[n+1, "C", Value])): n \in 1..MAXIMUM_NUM_OF_NODES}

TreeSampleNodes ==
       {[ID |-> ident, Type |-> type, Status |-> "Unanalyzed", Value |-> value]:
        ident \in 1..MAXIMUM_NUM_OF_NODES+1, type \in {"C", "S"}, value \in NodeValue}
analyze[T \in TreeSamples,
        N \in TreeSampleNodes] ==
  CASE N.Type = "C" ->
             [info |-> [F1 |-> <<>>, F2 |-> <<>>, NA |-> <<>>], status |-> "Analyzing"]
    [] N.Type = "S" ->
             [info |-> [F1 |-> <<1>>, F2 |-> <<>>, NA |-> <<>>],
              status |-> "Done"]


ParsedData ==
  [{"F1", "F2", "NA"} -> Seq(Nat)]
MergeDatas[D1 \in ParsedData,
           D2 \in ParsedData] ==
  LET conflict_fields ==
    {f: f \in (DOMAIN D1 \intersect DOMAIN D2)}
  IN  IF conflict_fields /= {}
      THEN [x \in (DOMAIN D1) \union (DOMAIN D2) |->
            IF x \in conflict_fields
            THEN D1[x] \o D2[x]
            ELSE IF x \in DOMAIN D1 THEN D1[x] ELSE D2[x]]
      ELSE D1 @@ D2

================================
