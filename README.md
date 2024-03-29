Chameleons
==========
Chameleons is a system that use rewrite rules to build a [Rewrite System](https://en.wikipedia.org/wiki/Abstract_rewriting_system).


```
TARGET: TESTLANG
RULES:

IdnentityMulti:
    {| a * 1 |} => {| a |}
IdentityPlus:
    {| a + 0 |} => {| a |}

```

TODO
====
* Generic way to define Term functions (which can be called in where expression).
* Implement STRATEGIES section in rule_examples.txt
