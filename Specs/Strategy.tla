--------- MODULE Strategy ---------
CONSTANTS ParseTree, Rule

Strategies == [Rule \X ParseTree -> Rule \X ParseTree]

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
