#ifndef API_RULE_H
#define API_RULE_H

#include <string>
#include <memory>

#include "Base/langs.h"
#include "Base/langsInfo.h"
#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

#include "TransEngine/Rewrite/Strategy.h"

#include "Base/generic_parsetree_antlr4.h"
#include "src/TransEngine/Rewrite/Rule.h"

#include "TransEngine/TransLang/Compiler/ChameleonsParserMain-inl.h"

namespace Chameleon::api {

using LeftPattern = std::string;
using RightPattern = LeftPattern;
using WhereClause = LeftPattern;

namespace RewriteSys = TransEngine::Rewrite;

/* Internal Definitions */
template<Base::isLangType lang_>
struct LayerInfo;

template<>
struct LayerInfo<GET_LANG_TYPE(TESTLANG)> {
  using LowerLayer = Base::Antlr4Node;
};

template<>
struct LayerInfo<GET_LANG_TYPE(WGSL)> {
  using LowerLayer = Base::Antlr4Node;
};


template<Base::isLangType lang>
struct Rule {
private:
  using LowerLayer = typename LayerInfo<lang>::LowerLayer;

public:
  Rule(LeftPattern& lp, RightPattern& rp): rule_{} {
    namespace R = TransEngine::Rewrite;

    rule_ = R::Rule<Base::Antlr4Node>::makeRule<lang>("", lp, rp);
  }

  Rule(LeftPattern& lp, WhereClause& where, RightPattern& rp):
    Rule(lp, rp) {

    std::string virtualRule = TransEngine::Compiler::SingleRuleTemplate(
      Base::LangArg<lang>::name, lp, where, rp);

    TransEngine::Compiler::Compiler compiler;
    std::istringstream s{virtualRule};
    std::vector<RewriteRule> rules = compiler.compileToRule<lang>(s);

    assertm(rules.size() == 1, "Only one rule can be generated");

    rule_ = rules[0];
  }

  Rule(LeftPattern&& lp, RightPattern&& rp):
    Rule(lp, rp) {}

  Rule(LeftPattern&& lp, WhereClause&& where, RightPattern&& rp):
    Rule(lp, where, rp) {}

  RewriteSys::StrategySeq<LowerLayer>
  toStrategy() const {
    return RewriteSys::ruleBreakDown(const_cast<RewriteRule&>(rule_));
  }

  bool operator==(const Rule& other) const {
    return rule_ == const_cast<Rule&>(other).rule_;
  }

private:
  using RewriteRule = TransEngine::Rewrite::Rule<typename LayerInfo<lang>::LowerLayer>;
  RewriteRule rule_;
};


} // Chameleon::api

#endif /* API_RULE_H */
