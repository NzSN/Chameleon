--------- MODULE Strategy ---------
CONSTANTS ParseTree, Rule

LOCAL INSTANCE TLC
LOCAL INSTANCE Naturals
LOCAL INSTANCE Sequences
LOCAL INSTANCE Rule
LOCAL INSTANCE Tree

\* Algorithm to do PatternMatching is not specified.
MatchStrategy(r,t,e) ==
    IF LeftPattern(r) = t
    THEN <<r, t, Append(e, t)>>
    ELSE <<r, t, e>>

\* Build Strategy is resiponsible to build up an instance
\* tree from right side pattern of Rule.
\* Only thing that specify here is the fact that Build
\* Strategy do transforming Target Tree into a tree that
\* match right side pattern.
BuildStrategy(r,t,e) ==
    IF /\ e /= <<>>
       /\ \exists i \in 1..Len(e): e[i] = t
    THEN <<r, RightPattern(r), e>>
    ELSE <<r, t, e>>

====================================
