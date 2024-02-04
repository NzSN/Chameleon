------ MODULE ChameleonMain ------
CONSTANTS NULL, RuleConfig
VARIABLES parser, transformer, state

LOCAL INSTANCE Naturals

\* CONSTANTS that we want to specify for
\* Module Chameleon.
Tree[n \in Nat] == {{n}}

ParseTree == {Tree[0], Tree[1]}
Rule == {
         \* Left side pattern is Tree[0]
         \* Right side pattern is Tree[1]
         <<Tree[0], Tree[1]>>,
         \* Rule define below is similar to
         \* thee first one.
         <<Tree[1], Tree[2]>>,
         <<Tree[2], Tree[3]>>}


Prog == INSTANCE Chameleon WITH
  NULL <- NULL,
  Rule <- Rule,
  ParseTree <- ParseTree,
  RuleConfig <- RuleConfig,
  parser <- parser,
  transformer <- transformer,
  state <- state

Spec == Prog!Spec

=================================
