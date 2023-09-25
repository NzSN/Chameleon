------- MODULE Analyzer ------------
CONSTANT NULL, node_ids, node_types, node_values, analyze

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE Tree WITH NULL <- NULL
LOCAL INSTANCE AnalyzerDefines WITH
  node_ids <- node_ids,
  node_types <- node_types,
  node_values <- node_values

AnalyzeImpls ==
  [Tree(ParseTreeNodes) \X ParseTreeNodes ->
   {[tree |-> t, info |-> i, status |-> s]:
    t \in Tree(ParseTreeNodes),
    i \in ParsedData,
    s \in ParseTreeNodeStatus} \union {NULL}]

ASSUME analyze \in AnalyzeImpls

LOCAL DoAnalyze(T) ==
  LET rootNode == GetRoot(T)
      Analyzing[tree \in Tree(ParseTreeNodes),
                node_ \in ParseTreeNodes] ==
        LET result == analyze[T, node_]

            AnalyzingChildren[tree_ \in Tree(ParseTreeNodes),
                              node__ \in ParseTreeNodes,
                              idx \in Nat] ==
              IF idx < NumOfChild(tree_, node__)
              THEN LET current_result == Analyzing[tree_, GetChild(tree_, node__, idx)]
                       remains == AnalyzingChildren[tree_, node__, idx+1]
                   IN  IF remains /= NULL
                       THEN MergeDatas[current_result, remains]
                       ELSE NULL
              ELSE NULL

        IN  IF IsAnalyzing[result.status]
            \* Some of children still unanalyzed.
            THEN
              IF NumOfChild(tree, node_) > 0
              THEN LET result_children == AnalyzingChildren[tree, node_, 1]
                   IN  IF result_children /= NULL
                       THEN MergeDatas[result, result_children]
                       ELSE Assert(FALSE, "Failed to parse children")
              ELSE Assert(FALSE, "Failed to analyze node")
            ELSE
              IF IsAnalyzeFinished[result.status]
              THEN result.info
              ELSE Assert(FALSE, "Failed to analyze node")
  IN Analyzing[T, rootNode]

\* Analyze the tree which root
\* node as parameter.
Analyze(T) == DoAnalyze(T)

===========================================
