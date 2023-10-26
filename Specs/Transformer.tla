---- MODULE Transformer ----
CONSTANT TrRules
VARIABLES transformer


TypeInvariant ==
  transformer =
    [rdy |-> 1, info |-> NULL, ast |-> NULL, rules |-> TrRules, out |-> NULL]

Init ==
  /\ TypeInvariant

Transforming(info, ast) ==
  /\ info \in ParsedData
  /\ ast \in TreeSamples
  /\ transformer' = [transformer EXCEPT
                     !.rdy = 0,
                     !.info = info,
                     !.ast = ast,
                     !.out = transform(info,ast,@.rules)]

TransedDone ==
  /\ transformer.rdy = 0
  /\ transformer.info # NULL
  /\ transformer.ast # NULL
  /\ transformer.out # NULL

Next == Transforming \/ TransedDone

Spec == Init /\ [][Next]_transformer

============================
