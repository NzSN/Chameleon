------ MODULE Rule ------
LOCAL INSTANCE Naturals
LOCAL INSTANCE Tree

Rules == {<<l, r>>: l \in Trees, r \in Trees}
RuleInst(l,r) == <<l,r>>
LeftPattern(t) == t[1]
RightPattern(t) == t[2]

===========================
