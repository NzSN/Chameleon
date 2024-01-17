---- MODULE TreeMain ----
EXTENDS TLC, Integers, FiniteSets, Sequences
CONSTANTS Nodes, NULL

INSTANCE Tree WITH NULL <- NULL

Valid ==
    \A t \in Tree({"A","B", "C"}):
        /\ Assert(~Ring(t), <<"CounterExample(Ring)", t>>)
        /\ Assert(UniqueParent(t), <<"CounterExample(UniqueParent)", t>>)
        /\ Assert(OneTree(t), <<"CounterExample(OneTree)",t>>)
=========================
