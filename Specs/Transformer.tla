---- MODULE Transformer ----
CONSTANT RuleConfig, Rule, NULL, ParseTree
VARIABLES transformer

ParsingRuleConfig[config \in RuleConfig] ==
  CHOOSE r \in Rule: TRUE

Transform[ast \in ParseTree,
          rule \in Rule] ==
  CHOOSE t \in ParseTree: TRUE

TypeInvariant ==
  transformer = [out |-> NULL]

Init ==
  /\ TypeInvariant

Transforming(ast, rule) ==
  /\ ast \in ParseTree
  /\ transformer' = [transformer EXCEPT
                     !.out = Transform[ast,rule]]

TransDone ==
  /\ transformer.out # NULL
  /\ UNCHANGED transformer

Next == \/ \E t \in ParseTree:
           \E r \in RuleConfig: Transforming(t,r)
        \/ TransDone

Spec == Init /\ [][Next]_transformer
============================
