---- MODULE TreeMain ----
EXTENDS TLC, Integers, FiniteSets, Sequences
CONSTANTS Nodes, NULL

INSTANCE Tree WITH NULL <- NULL


AllTrees == Tree(Nodes)

Valid ==
    LET t == Singleton("1")
    IN  /\ Assert(~OneParent(t), <<"CounterExample(1)", t>>)
        /\ Assert(~Ring(t), <<"CounterExample(2)", t>>)
        /\ Assert(~RingToRoot(t), <<"CounterExample(3)", t>>)
        /\ Assert(OneTree(t), <<"CounterExample(3)", t>>)
        /\ AddNode(t, "1", "2") \in Tree({"1", "2"})
        /\ DelNode(t, "1") \in Tree({"1"})

=========================
