---- MODULE Transformer ----
CONSTANT Rule, RuleConfig, NULL, ParseTree
VARIABLES transformer

LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals
LOCAL INSTANCE Strategy
LOCAL INSTANCE Rule
LOCAL INSTANCE Tree

\* RuleConfig -> Seq(Rule)
ParseConfig[config \in RuleConfig] ==
  <<RuleInst(Tree[0], Tree[1])>>

\* ParseTree -> ParseTree
Transform[ast \in ParseTree,
          rule \in Rule] ==
  LET S == BasicStrategies \* Break the Rule into Strategies
      ApplyStrategies[ss \in Seq(Strategies),
                      rule_ \in Rule,
                      ast_ \in ParseTree,
                      env_ \in Seq(ParseTree)] ==
        IF ss = <<>>
        THEN <<rule_, ast_>>
        ELSE
          LET s == Head(ss)
              r == s[<<rule_,ast_, env_>>]
          IN  ApplyStrategies[Tail(ss), r[1], r[2], env_]
  \* Do transformation by apply each of strategies
  \* to rule.
  IN ApplyStrategies[S, rule, ast, <<>>][2]

TransRules[ast \in ParseTree, rules \in Seq(Rule)] ==
  IF rules = <<>>
  THEN ast
  ELSE
    LET currentRule == Head(rules)
        ast_    == Transform[ast, currentRule]
    IN TransRules[ast_, Tail(rules)]

TypeInvariant ==
  transformer = [out |-> NULL]

Init ==
  /\ TypeInvariant

Transforming(ast, config) ==
  /\ ast \in ParseTree
  /\ transformer' = [transformer EXCEPT
                     !.out = TransRules[ast,ParseConfig[config]]]

TransDone ==
  /\ transformer.out # NULL
  /\ UNCHANGED transformer

Next == \/ \E t \in ParseTree:
           \E r \in Rule: Transforming(t,r)
        \/ TransDone

Spec == Init /\ [][Next]_transformer
============================
