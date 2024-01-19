---- MODULE Transformer ----
CONSTANT Rule, RuleConfig, NULL, ParseTree
VARIABLES transformer

LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals
LOCAL INSTANCE Strategy

Strategy == [Rule \X ParseTree -> Rule \X ParseTree]
ToStrategies[rule \in Rule] ==
  LET toStrategies_[n \in Nat] ==
        IF n = 0
        THEN <<>>
        ELSE <<CHOOSE s \in Strategy: TRUE>> \o toStrategies_[n-1]
      N == CHOOSE N \in 1..100: TRUE
  IN toStrategies_[N]

ParseConfig[config \in RuleConfig] ==
  CHOOSE r \in Rule: TRUE

\* ParseTree -> ParseTree
Transform[ast \in ParseTree,
          rule \in Rule] ==
  LET S == ToStrategies[rule] \* Break the Rule into Strategies
      ApplyStrategies[ss \in Seq(Strategy),
                      rule_ \in Rule,
                      ast_ \in ParseTree] ==
        IF ss = <<>>
        THEN <<rule_, ast_>>
        ELSE
          LET s == Head(ss)
              r == s[<<rule_,ast_>>]
          IN  ApplyStrategies[Tail(ss), r[1], r[2]]
  \* Do transformation by apply each of strategies
  \* to rule.
  IN ApplyStrategies[S, rule, ast][2]

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
