---- MODULE Rule ----
CONSTANTS NULL, RID

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

RIDConst == 1..3

Rules ==
    {[ID |-> id, L |-> lt, R |-> rt,
      \* Transform Rule may define without
      \* condition parts.
      S |-> s]:
     id \in RID, lt \in TreeSamples, rt \in TreeSamples,
     s \in ExprTree \union {NULL}}

EVAL == \A t \in Rules: PrintT(t)
=====================
