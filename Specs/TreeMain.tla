---- MODULE TreeMain ----
EXTENDS TLC, Integers, FiniteSets, Sequences
CONSTANTS Nodes, NULL

INSTANCE Tree WITH NULL <- NULL

e1 == [name |-> "A", Value |-> "V"]
e2 == [name |-> "AA", Value |-> "VV"]
e3 == [name |-> "AAA", Value |-> "VVV"]
e4 == [name |-> "AAAA", Value |-> "VVVV"]
e5 == [name |-> "AAAAA", Value |-> "VVVVV"]
e6 == [name |-> "AAAAAA", Value |-> "VVVVVV"]
e7 == [name |-> "AAAAAAA", Value |-> "VVVVVVV"]

Valid ==
    LET N == Tree({e1,e2,e3,e4})
        t == Singleton(e1)
    IN  /\ Assert(~OneParent(t), <<"CounterExample(1)", t>>)
        /\ Assert(~Ring(t), <<"CounterExample(2)", t>>)
        /\ Assert(~RingToRoot(t), <<"CounterExample(3)", t>>)
        /\ Assert(OneTree(t), <<"CounterExample(3)", t>>)
        /\ AddNode(t, e1, e2) \in N
        /\ t \in N
        /\ GetRoot(t) = e1

=========================
