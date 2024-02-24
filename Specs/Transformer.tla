---- MODULE Transformer ----
CONSTANT Rule, RuleConfig, NULL, ParseTree
VARIABLES transformer

LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals
LOCAL INSTANCE Strategy
LOCAL INSTANCE Rule
LOCAL INSTANCE Tree
LOCAL INSTANCE TLC

\* RuleConfig -> Seq(Rule)
ParseConfig[config \in RuleConfig] ==
  <<RuleInst(Tree[0], Tree[1]),
    RuleInst(Tree[0], Tree[1])>>

IsAlreadyTransformed[t \in Trees,
                     config \in RuleConfig] ==
  LET rules == ParseConfig[config]
      isRightPatterns[t_ \in Trees, rs \in Seq(Rule)] ==
        IF rs = <<>>
        THEN FALSE
        ELSE
          LET r == Head(rs)
          IN  RightPattern(r) = t_ \/
              isRightPatterns[t_, Tail(rs)]
  IN isRightPatterns[t, rules]

IsAnyRuleMatch[t \in Trees, config \in RuleConfig] ==
  LET rules == ParseConfig[config]
      isLeftPatterns[t_ \in Trees, rs \in Seq(Rule)] ==
        IF rs = <<>>
        THEN FALSE
        ELSE
          LET r == Head(rs)
          IN  LeftPattern(r) = t_ \/
              isLeftPatterns[t_, Tail(rs)]
  IN isLeftPatterns[t, rules]


RECURSIVE TransRules(_,_)
TransRules(ast,rules) ==
  IF rules = <<>>
  THEN ast
  ELSE
    LET currentRule == Head(rules)
        R1   == MatchStrategy(currentRule,ast,<<>>)
        ast_ == BuildStrategy(R1[1], R1[2], R1[3])[2]
    IN TransRules(ast_, Tail(rules))

TypeInvariant ==
  transformer = [out |-> NULL, config |-> NULL]

Init ==
  /\ TypeInvariant

Transforming(ast, config) ==
  /\ ast \in ParseTree
  /\ transformer' = [transformer EXCEPT
                     !.out = TransRules(ast,ParseConfig[config]),
                     !.config = config]

TransDone(transed_ast, config) ==
  /\ transformer.out # NULL
  \* Assert that the AST has already
  \* been transformed into right side
  \* pattern of rule otherwise no rule to
  \* match the given AST.
  /\ IsAlreadyTransformed[transed_ast, config] \/
     (~IsAlreadyTransformed[transed_ast, config] /\
      ~IsAnyRuleMatch[transed_ast, config])
  /\ UNCHANGED transformer

Next == \/ \E t \in ParseTree:
           \E r \in Rule: Transforming(t,r)
        \/ \E t \in ParseTree:
           \E r \in Rule: TransDone(t, r)

Spec == Init /\ [][Next]_{transformer}
============================
