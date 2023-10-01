------- MODULE Analyzer ------------
CONSTANT NULL, node_ids, node_types, node_values, analyze

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE Tree WITH NULL <- NULL
LOCAL INSTANCE AnalyzerDefines WITH
  node_ids <- node_ids,
  node_types <- node_types,
  node_values <- node_values

\* AnalyzeImpls ==
\*   [Tree(ParseTreeNodes) \X ParseTreeNodes ->
\*    {[info |-> i, status |-> s]:
\*     i \in ParsedData,
\*     s \in ParseTreeNodeStatus} \union {NULL}]

\*ASSUME analyze \in AnalyzeImpls

LOCAL DoAnalyze(T) ==
  LET rootNode == GetRoot(T)
      Analyzing[tree \in Tree(DOMAIN T),
                node_ \in DOMAIN T] ==
        LET result == analyze[T, node_]

            AnalyzingChildren[tree_ \in Tree(DOMAIN T),
                              node__ \in DOMAIN T,
                              idx \in Nat] ==
              IF idx <= NumOfChild(tree_, node__)
              THEN LET current_result == Analyzing[tree_, GetChild(tree_, node__, idx)]
                       remains == AnalyzingChildren[tree_, node__, idx+1]
                   IN  IF current_result /= NULL /\ remains /= NULL
                       THEN MergeDatas[current_result, remains]
                       ELSE
                         IF current_result /= NULL
                         THEN current_result
                         ELSE
                           IF remains /= NULL
                           THEN remains
                           ELSE NULL

              ELSE NULL

        IN  IF IsAnalyzing[result.status]
            \* Some of children still unanalyzed.
            THEN
              IF NumOfChild(tree, node_) > 0
              THEN LET result_children == AnalyzingChildren[tree, node_, 1]
                   IN  IF result_children /= NULL
                       THEN MergeDatas[result.info, result_children]
                       ELSE Assert(FALSE, "Failed to parse children")
              ELSE Assert(FALSE, "Failed to analyze node: No child node to parse")
            ELSE
              IF IsAnalyzeFinished[result.status]
              THEN result.info
              ELSE Assert(FALSE, "Failed to analyze node")
  IN Analyzing[T, rootNode]

\* Analyze the tree which root
\* node as parameter.
Analyze(T) == DoAnalyze(T)



===========================================
