---- MODULE Rule ----
CONSTANTS NULL

LOCAL INSTANCE Naturals
LOCAL INSTANCE TLC
LOCAL INSTANCE TreeSamples WITH NULL <- NULL

Rules ==
    {[L |-> lt, R |-> rt]: lt \in TreeSamples, rt \in TreeSamples}

=====================
