---- MODULE Rule ----
CONSTANTS NULL, RID

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

RIDConst == 1..3

Rules ==
    {[ID |-> id, L |-> lt, R |-> rt]:
     id \in RID, lt \in TreeSamples, rt \in TreeSamples}

EVAL == \A t \in Rules: PrintT(t)
=====================
