---- MODULE Transformer ----
CONSTANT RuleConfig, Rule, NULL
VARIABLES transformer

LOCAL INSTANCE TreeSamples WITH NULL <- NULL

ParsingRuleConfig[config \in RuleConfig] ==
  CHOOSE r \in Rule: TRUE

Transform[info \in ParsedData,
          ast \in TreeSamples,
          rule \in Rule] ==
  CHOOSE t \in TreeSamples: TRUE

TypeInvariant ==
  transformer = [rdy |-> 1, rule |-> NULL, out |-> NULL]

Init ==
  /\ TypeInvariant

ParseRuleConfig(config) ==
  /\ transformer.rule = NULL
  /\ transformer.rdy = 1
  /\ transformer' = [transformer EXCEPT !.rule = ParsingRuleConfig[config]]


Transforming(info, ast) ==
  /\ transformer.rdy = 1
  /\ transformer.rule # NULL
  /\ info \in ParsedData
  /\ ast \in TreeSamples
  /\ transformer' = [transformer EXCEPT
                     !.rdy = 0,
                     !.out = Transform[info,ast,transformer.rule]]

TransDone ==
  /\ transformer.rdy = 0
  /\ transformer.out # NULL
  /\ UNCHANGED transformer

Next == \/ \E c \in RuleConfig: ParseRuleConfig(c)
        \/ \E info \in ParsedData:
            \E t \in TreeSamples: Transforming(info, t)
        \/ TransDone

Spec == Init /\ [][Next]_transformer
============================
