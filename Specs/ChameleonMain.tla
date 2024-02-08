------ MODULE ChameleonMain ------
CONSTANTS NULL, RuleConfig
VARIABLES parser, transformer, state

LOCAL INSTANCE Naturals
LOCAL INSTANCE Tree
LOCAL INSTANCE Rule

ParseTree == {Tree[0], Tree[1], Tree[2], Tree[3]}
RuleSamples == {
         \* Left side pattern is Tree[0]
         \* Right side pattern is Tree[1]
         RuleInst(Tree[0], Tree[1]),
         \* Rule define below is similar to
         \* thee first one.
         RuleInst(Tree[1], Tree[2]),
         RuleInst(Tree[2], Tree[3])}

Prog == INSTANCE Chameleon WITH
  NULL <- NULL,
  Rule <- RuleSamples,
  ParseTree <- ParseTree,
  RuleConfig <- RuleConfig,
  parser <- parser,
  transformer <- transformer,
  state <- state

Spec == Prog!Spec

=================================
