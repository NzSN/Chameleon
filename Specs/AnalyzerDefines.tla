---- MODULE AnalyzerDefines ----
CONSTANTS node_ids, node_types, node_values

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE Sequences


ParseTreeNodeStatus == {"Unanalyzed", "Analyzing", "Done"}

IsUnanalyzed[s \in ParseTreeNodeStatus] ==
  s = "Unanalyzed"

IsAnalyzing[s \in ParseTreeNodeStatus] ==
  s = "Analyzing"

IsAnalyzeFinished[s \in ParseTreeNodeStatus] ==
  s = "Done"

ParseTreeNodes == {[ID |-> ident,
                    Type |-> type,
                    Value |-> value,
                    Status |-> ParseTreeNodeStatus]:
                    ident \in node_ids, type \in node_types, value \in node_values}

ParseTreeNode[ident  \in node_ids,
              type   \in node_types,
              value  \in node_values] ==
    [ID |-> ident, Type |-> type, Value |-> value,
     Status |-> "Unanalyzed"]

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
