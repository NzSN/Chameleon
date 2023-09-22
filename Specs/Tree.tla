---- MODULE Tree ----
\* Tree define in this module is mainly to work as
\* an adaptor to wrap a concrete Tree to enable
\* Analyzer or Transformer to access it.
CONSTANTS NULL

LOCAL INSTANCE TLC
LOCAL INSTANCE Naturals
LOCAL INSTANCE Sequences
LOCAL INSTANCE FiniteSets

LOCAL CODOMAIN(f) ==
    {f[x]: x \in DOMAIN f}
LOCAL Root(Nodes) == Nodes[1]
LOCAL TreeRelations(Nodes) ==
    \* DOMAIN is the set of all nodes
    \* that is parent, NULL indicate
    \* nodes that been deleted.
    [Nodes -> Seq(Nodes) \union {NULL}]

LOCAL Descdent(Node, relation) ==
    LET D[N \in DOMAIN relation] ==
        IF relation[N] = <<>> \/ relation[N] = NULL
          THEN {} ELSE
          LET nodes == DOMAIN relation
              Childs == { c \in {relation[N][i]: i \in 1..Len(relation[N])}:
                          relation[c] /= NULL}
              InDirect == {D[c]: c \in Childs}
          IN (UNION InDirect) \union Childs
    IN D[Node]

\* 1. Every node can have infinite childs
\* 2. A child can have only one parent.
\* 3. Root has no parent.
\* 4. Every nodes except Root is descdent of Root
LOCAL IsTree(relation) ==
    LET nodes == DOMAIN relation
        all_seqs == [1..Cardinality(nodes) -> nodes]
    IN
        \* Assert that a node unable to be a Parent of itself.
        /\ \A x \in nodes:
             relation[x] /= NULL =>
                \A i \in 1..Len(relation[x]): relation[x][i] /= x
        \* Assert that only one path from parent to it's child.
        /\ \A x \in nodes:
             relation[x] /= NULL =>
                \A i \in 1..Len(relation[x]):
                \A j \in 1..Len(relation[x]) \ {i}:
                    relation[x][i] /= relation[x][j]
        \* Assert that every node has only one parent.
        /\ \A x \in nodes:
             relation[x] /= NULL =>
                \E y \in nodes \ {x}:
                    relation[y] /= NULL =>
                        \A i \in 1..Len(relation[x]):
                        \A j \in 1..Len(relation[y]):
                            /\ relation[x][i] /= relation[y][j]
        \* Assert that root has no parent,
        /\ \E ordering \in all_seqs:
           \A x \in nodes:
            relation[x] /= NULL =>
                \A i \in 1..Len(relation[x]):
                    Root(ordering) /= relation[x][i]
        \* Assert that every nodes except Root is descdent of Root
        \* which make sure a relation correspond to only one Tree.
        /\ \E ordering \in all_seqs:
           \A x \in nodes:
             relation[x] /= NULL =>
                \/ x = Root(ordering)
                \/ x \in Descdent(Root(ordering), relation)


Tree(Nodes) ==
    IF NULL \in Nodes
    THEN Assert(FALSE, "Root of tree cannot be NULL") \* Empty Tree
    ELSE LET Relations == TreeRelations(Nodes)
         IN  {tr \in Relations: TRUE}

(*Operations*)
Singleton(n) == (n :> <<>>)
IsExists(T, Node) ==
    \A r \in DOMAIN T: Node = r

AddNode(T, Node, New) ==
    LET TT == T @@ (New :> <<>>)
    IN  [TT EXCEPT ![Node] = Append(TT[Node], New)]

DelNode(T, Node) ==
    [T EXCEPT ![Node] = NULL]

GetChild(T, Node, N) ==
    IF IsExists(T, Node) /\ Len(T[Node]) > N
    THEN T[Node][N]
    ELSE NULL

NumOfChild(T, Node) ==
    IF IsExists(T, Node) /\ Len(T[Node]) > N
    THEN Len(T[Node])
    ELSE 0

GetRoot(T) ==
    LET nodes == DOMAIN T
        RootSet == {n \in nodes: \A y \in nodes \ {n}: y \in Descdent(n, T)}
    IN IF Cardinality(RootSet) = 1 \* There should only one root
       THEN CHOOSE n \in nodes: \A y \in nodes \ {n}: y \in Descdent(n, T)
       ELSE NULL

(*Tree Property Predicates*)
Ring(T) ==
    IF CODOMAIN(T) = {<<>>}
    THEN FALSE
    ELSE (DOMAIN T = CODOMAIN(T))

OneParent(T) ==
      LET nodes == DOMAIN T
      IN  \E x \in nodes:
          \E y \in nodes:
          \E i \in 1..Cardinality(nodes)-1:
          \E j \in 1..Cardinality(nodes)-1:
            /\ x /= y
            /\ T[x][i] /= T[y][j]
RingToRoot(T) ==
    LET nodes == DOMAIN T
        all_seqs == [1..Cardinality(nodes) -> nodes]
    IN  \A ordering \in all_seqs:
        \A x \in nodes:
          IF T[x] = <<>> THEN FALSE
          ELSE
            \A i \in 1..Cardinality(nodes)-1:
                /\ Root(ordering) = T[x][i]
OneTree(T) ==
    LET nodes == DOMAIN T
        all_seqs == [1..Cardinality(nodes) -> nodes]
    IN \E ordering \in all_seqs:
       \A x \in nodes:
         \/ x = Root(ordering)
         \/ x \in Descdent(Root(ordering), T)
=====================
