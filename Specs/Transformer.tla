---- MODULE Transformer ----
VARIABLES transformer


TypeInvariant ==
  transformer == [rdy |-> 1, infor |-> NULL, ast |-> NULL]
============================
