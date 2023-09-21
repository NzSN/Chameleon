---- MODULE Parser ----
CONSTANT
    Source,
    Nodes,

    \* Tree's CONSTANTS
    NULL,

LOCAL INSTANCE Tree WITH NULL <- NULL,

\* I don't specify how Parser works only
\* due this part of works will bridged to
\* another Parser exists.
\*
\* I define Parser in Chamelone simplly is
\* a function that do transformation between
\* Source and ParseTree.
Parser == [Source -> Tree(Nodes)]
=======================
