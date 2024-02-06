--------- MODULE Strategy ---------
CONSTANTS ParseTree, Rule

LOCAL INSTANCE Naturals
LOCAL INSTANCE Sequences
LOCAL INSTANCE Rule
LOCAL INSTANCE Tree

StraEnv == UNION {[1..n -> ParseTree]: n \in 0..MAXIMUM_INDEX}

MatchStrategy[r \in Rule, t \in ParseTree, e \in StraEnv] ==
    LET Match == LeftPattern
    <<r, t, e>>
BuildStrategy[r \in Rule, t \in ParseTree, e \in StraEnv] ==
    <<r, t, e>>

Strategies == {MatchStrategy, BuildStrategy}
BasicStrategies == <<MatchStrategy, BuildStrategy>>



====================================
