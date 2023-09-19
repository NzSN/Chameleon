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
LOCAL TreeRelations(Nodes, N) ==
    \* DOMAIN is the set of all nodes
    \* that is parent
    [Nodes -> [N -> Nodes \union {NULL}]]

LOCAL Descdent(Node, relation) ==
    LET D[N \in DOMAIN relation] ==
        IF N = NULL THEN {} ELSE
          LET nodes == DOMAIN relation
              Childs == {relation[N][i]: i \in 1..Cardinality(nodes)-1}
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
           \A i \in 1..Cardinality(nodes)-1:
             relation[x][i] /= x
        \* Assert that only one path from parent to it's child.
        /\ \A x \in nodes:
           \A i \in 1..Cardinality(nodes)-1:
           \A j \in 1..Cardinality(nodes)-1 \ {i}:
             relation[x][i] /= relation[x][j]
        \* Assert that every node has only one parent.
        /\ \A x \in nodes:
           \E y \in nodes \ {x}:
           \A i \in 1..Cardinality(nodes)-1:
           \A j \in 1..Cardinality(nodes)-1:
             /\ relation[x][i] /= NULL
             /\ relation[y][j] /= NULL
             /\ relation[x][i] /= relation[y][j]
        \* Assert that root has no parent,
        \* /\ \E ordering \in all_seqs:
        \*    \A x \in nodes:
        \*    \A i \in 1..Cardinality(nodes)-1:
        \*      Root(ordering) /= relation[x][i]
        \* Assert that every nodes except Root is descdent of Root
        \* which make sure a relation correspond to only one Tree.
        /\ \A x \in nodes:
           \E i \in 1..Cardinality(nodes)-1:
            \/ x = relation[Root(nodes), i]
            \/ x \in Descdent(Root(nodes), relation)



Tree(Nodes) ==
    IF NULL \in Nodes
    THEN Assert(FALSE, "Root of tree cannot be NULL") \* Empty Tree
    ELSE TreeRelations(Nodes, 1..Cardinality(Nodes))

Ring(T) == (DOMAIN T = CODOMAIN(T))
OneParent(T) ==
      LET nodes == DOMAIN T
      IN  \E x \in nodes:
          \E y \in nodes:
          \E i \in 1..Cardinality(nodes)-1:
          \E j \in 1..Cardinality(nodes)-1:
            /\ x /= y
            /\ T[x][i] /= NULL
            /\ T[y][j] /= NULL
            /\ T[x][i] /= T[y][j]
RingToRoot(T) ==
    LET nodes == DOMAIN T
        all_seqs == [1..Cardinality(nodes) -> nodes]
    IN  \A ordering \in all_seqs:
        \A x \in nodes:
        \A i \in 1..Cardinality(nodes)-1:
          Root(ordering) = T[x][i]
OneTree(T) ==
    LET nodes == DOMAIN T
        all_seqs == [1..Cardinality(nodes) -> nodes]
    IN \E ordering \in all_seqs:
       \A x \in nodes:
         \/ x = Root(ordering)
         \/ x \in Descdent(Root(ordering), T)
=====================
