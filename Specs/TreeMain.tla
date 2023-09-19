---- MODULE TreeMain ----
EXTENDS TLC, Integers, FiniteSets, Sequences
CONSTANTS Nodes, NULL

INSTANCE Tree WITH NULL <- NULL


AllTrees == Tree(Nodes)
Valid ==
    \A t \in AllTrees:
        /\ Assert(~OneParent(t), <<"CounterExample(1)", t>>)
        /\ Assert(~Ring(t), <<"CounterExample(2)", t>>)
        /\ Assert(~RingToRoot(t), <<"CounterExample(3)", t>>)
        /\ Assert(~OneTree(t), <<"CounterExample(3)", t>>)
=========================
