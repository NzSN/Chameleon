---- MODULE Strategy ----
CONSTANTS NULL

LOCAL INSTANCE TLC
LOCAL INSTANCE Naturals
LOCAL INSTANCE Environment WITH NULL <- NULL
LOCAL INSTANCE Rule WITH NULL <- NULL

Strategies ==
    [Rules \X Environments -> {NULL}]

=========================
