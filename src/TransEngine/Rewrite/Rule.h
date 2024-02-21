#ifndef RULE_H
#define RULE_H

#include <memory>
#include <sstream>

#include "Base/langsInfo.h"

#include "Base/generic_parsetree.h"
#include "TransEngine/SigmaTerm.h"
#include "Parser/Parser-inl.h"
#include "CondExpr-inl.h"

namespace Chameleon {
namespace TransEngine {
namespace Rewrite {

template<Base::Layer T>
struct Rule {
  Rule():
    label{}, leftSide{nullptr},
    rightSide{nullptr}, lang{}  {}

  template<Base::isLangType L>
  inline static Rule makeRule(std::string labelArg,
                std::istringstream& l,
                std::istringstream& r) {

    std::unique_ptr<Pattern<T>> leftSide =
      Parser
      ::ParserSelect<L>
      ::parser
      ::template parse<Pattern<T>, Base::DYNAMIC>(&l);

    std::unique_ptr<Pattern<T>> rightSide =
      Parser
      ::ParserSelect<L>
      ::parser
      ::template parse<Pattern<T>, Base::DYNAMIC>(&r);

    Rule rule = Rule<T>(
      labelArg, std::move(leftSide), std::move(rightSide), Base::LangArg<L>::langEnum);
    return rule;
  }

  template<Base::isLangType L>
  inline static Rule makeRule(std::string labelArg,
                              std::string& l,
                              std::string& r) {
    std::istringstream ls{l};
    std::istringstream rs{r};
    return makeRule<L>(labelArg, ls, rs);
  }

  Rule(std::string labelArg,
       Pattern<T>& leftSideArg,
       Pattern<T>& rightSideArg,
       const int langArg):
    label(labelArg),
    leftSide(&leftSideArg),
    rightSide(&rightSideArg),
    lang(langArg) {}
  ~Rule() {}

  Rule(std::string labelArg,
       std::shared_ptr<Pattern<T>> leftSideArg,
       std::shared_ptr<Pattern<T>> rightSideArg,
       const int langArg):
    label{labelArg},
    leftSide_shared{leftSideArg},
    rightSide_shared{rightSideArg},
    lang{langArg} {

    leftSide = leftSide_shared.get();
    rightSide = rightSide_shared.get();
  }

  Rule(const Rule& other):
    label{other.label},

    leftSide_shared{other.leftSide_shared},
    rightSide_shared{other.rightSide_shared},

    leftSide{other.leftSide},
    rightSide{other.rightSide},

    lang{other.lang},

    cond{other.cond} {}

  Rule& operator=(const Rule& other) {
    label = other.label;
    leftSide_shared = other.leftSide_shared;
    rightSide_shared = other.rightSide_shared;

    leftSide = other.leftSide;
    rightSide = other.rightSide;

    lang = other.lang;
    cond = other.cond;

    return *this;
  }

  Rule& operator=(Rule&& other) {
    label = std::move(other.label);
    leftSide_shared = std::move(other.leftSide_shared);
    rightSide_shared = std::move(other.rightSide_shared);

    leftSide = other.leftSide;
    rightSide = other.rightSide;

    lang = other.lang;
    cond = std::move(other.cond);

    return *this;
  }

  void appendCond(CondExpr& cond_) {
    cond.push_back(cond_);
  }

  void setConds(std::vector<CondExpr>&& conds_) {
    cond = std::move(conds_);
  }

  bool operator==(const Rule& other) {
    assertm(leftSide, "No leftside pattern found");
    assertm(rightSide, "No rightside pattern found");
    assertm(other.leftSide, "No leftside pattern found in other");
    assertm(other.rightSide, "No rightside pattern found in other");

    return *leftSide == *other.leftSide &&
      *rightSide == *other.rightSide &&
      cond == other.cond;
  }

  std::string label;

  std::shared_ptr<Pattern<T>> leftSide_shared;
  std::shared_ptr<Pattern<T>> rightSide_shared;

  Pattern<T>* leftSide;
  Pattern<T>* rightSide;

  int lang;

  // Expressions within WhereClause.
  std::vector<CondExpr> cond;
};

} // Rewrite
} // TransEngine
} // Chameleon


#endif /* RULE_H */
