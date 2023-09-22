---- MODULE TreeMain ----
EXTENDS TLC, Integers, FiniteSets, Sequences
CONSTANTS Nodes, NULL

INSTANCE Tree WITH NULL <- NULL


AllTrees == Tree(Nodes)

e1 == [name |-> "A", Value |-> "V"]
e2 == [name |-> "AA", Value |-> "VV"]

Valid ==
    LET t == Singleton(e1)
    IN  /\ Assert(~OneParent(t), <<"CounterExample(1)", t>>)
        /\ Assert(~Ring(t), <<"CounterExample(2)", t>>)
        /\ Assert(~RingToRoot(t), <<"CounterExample(3)", t>>)
        /\ Assert(OneTree(t), <<"CounterExample(3)", t>>)
        /\ AddNode(t, e1, e2) \in Tree({e1, e2})
        /\ t \in Tree({e1})
        /\ GetRoot(t) = e1

=========================
