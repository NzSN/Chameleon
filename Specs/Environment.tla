---- MODULE Environment ----
\* Environment is a set of Variables with binding
\* Informations. Those information show what terms
\* a variable is binded to.

CONSTANTS NULL

LOCAL INSTANCE TreeSamples WITH NULL <- NULL
LOCAL INSTANCE TLC
LOCAL INSTANCE Variables

\* From another aspect, Environment can be treated
\* as a function that map variable to term (tree).
Environments == [Variables -> TreeSamples]

CreateEnv(V, T) == V :> T
Bind(Env, V, T) ==
    IF V \in DOMAIN Env
    THEN NULL
    ELSE Env @@ (V :> T)
============================
