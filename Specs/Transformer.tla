---- MODULE Transformer ----
CONSTANT Rule, RuleConfig, NULL, ParseTree
VARIABLES transformer

ParseConfig[config \in RuleConfig] ==
  CHOOSE r \in Rule: TRUE

\* ParseTree -> ParseTree
Transform[ast \in ParseTree,
          rule \in Rule] ==
  \* TODO: Specify how transformation done
  CHOOSE t \in ParseTree: TRUE

TypeInvariant ==
  transformer = [out |-> NULL]

Init ==
  /\ TypeInvariant

Transforming(ast, config) ==
  /\ ast \in ParseTree
  /\ transformer' = [transformer EXCEPT
                     !.out = Transform[ast,ParseConfig[config]]]

TransDone ==
  /\ transformer.out # NULL
  /\ UNCHANGED transformer

Next == \/ \E t \in ParseTree:
           \E r \in Rule: Transforming(t,r)
        \/ TransDone

Spec == Init /\ [][Next]_transformer
============================
