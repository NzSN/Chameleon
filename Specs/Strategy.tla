--------- MODULE Strategy ---------
CONSTANTS ParseTree, Rule, Env

Strategy == [Rule \X ParseTree \X Env -> Rule \X ParseTree \X Env]

MatchStra[rule \in Rule,
          ast  \in ParseTree,
          env  \in Env] ==

WhereStra[rule \in Rule,
          ast  \in ParseTree,
          env  \in Env] ==

BuildStra[rule \in Rule,
          ast  \in ParseTree,
          env  \in Env] ==

====================================
