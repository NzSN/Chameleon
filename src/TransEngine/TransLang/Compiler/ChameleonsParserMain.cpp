#include <iostream>

#include <type_traits>
#include <optional>
#include <ranges>
#include <unordered_map>
#include <stdexcept>

#include "TransEngine/Rewrite/Environment.h"
#include "TransEngine/Rewrite/Rule.h"
#include "ChameleonsParserMain-inl.h"

#include "WhereClauseExprParsing-inl.h"

namespace TransEngine {
namespace Compiler {

std::optional<Base::GptGeneric>
Program::operator()(Base::GptGeneric& tree,
                    Analyzer::AnalyzeDataGeneric& metaInfo) {
  /* FIXME: Need to implement */
  return std::nullopt;
}

std::optional<Base::GenericParseTree<Adapter>>
EvalTestLang(Base::GenericParseTree<Adapter>& tree,
             Rewrite::StrategySeq<Adapter>& straSeq) {
  // Checking that all strategies are binded with
  // rules.
  for (auto& s: straSeq) {
    if (s->bindedRule.leftSide == nullptr ||
        s->bindedRule.rightSide == nullptr) {
      // Strategy must binded with a rule
      throw std::runtime_error(
        "Strategy to be evaluated must be binded with rule");
    }
  }

  // Setup environment
  Environment<Adapter> env{};
  env.setTargetTerm(&tree);

  // Evaluating all strategies with
  // target rules.
  for (auto& s: straSeq) {
    (*s)(s->bindedRule, env);
  }

  return tree;
}

std::optional<Base::GenericParseTree<Adapter>>
Program::operator()(Base::GenericParseTree<Adapter>& tree) {
  switch (lang_) {
  case Base::GptSupportLang::TESTLANG:
    return EvalTestLang(tree, strategies_);
  default:
    return std::nullopt;
  }
}


std::unordered_map<std::string, Base::GptSupportLang> langs = {
  {"TestLang", Base::GptSupportLang::TESTLANG}
};

std::optional<Base::GptSupportLang>
toLangID(std::string langID) {
  if (langs.contains(langID)) {
    return langs[langID];
  } else {
    return std::nullopt;
  }
}

// Transform CondExprContext to
template<Base::GPTMeta T>
bool createCondExpr(
  ChameleonsParser::CondExprContext* rCtx,
  Rewrite::Rule<T>& rule) {

  // Convert CondExprContext to Rewrite::CondExpr
  std::unique_ptr<Expression::Expr> expr =
    WhereClause::toExpr(rCtx);
  Rewrite::CondExpr<T> cond{std::move(expr)};

  // Append condition expression to Rule.
  rule.appendCond(cond);

  return true;
}

template<Base::GPTMeta T>
bool createCondExprs(
  ChameleonsParser::CondExprsContext* rCtx,
  Rewrite::Rule<T>& rule) {

  ChameleonsParser::CondExprsContext* current;
  while (current != nullptr) {
    bool success = createCondExpr(current->condExpr(), rule);
    if (!success) return success;
    current = current->condExprs();
  }

  return true;
}

// Traverse the tree of where expressions
// and spawn expressions.
template<Base::GPTMeta T>
bool createWhereExpressions(
  ChameleonsParser::WhereExprsContext* rCtx,
  Rewrite::Rule<T>& rule) {

  ChameleonsParser::WhereExprsContext* current = rCtx;
  while (current != nullptr) {
    /* Generate CondExprs into Rule */
    bool success = createCondExprs(
      current->condExprs(), rule);
    if (!success) return success;

    /* Next WhereExprs */
    current = current->whereExprs();
  }

  return true;
}

template<Base::GPTMeta T, int lang>
std::optional<Rewrite::Rule<T>>
strategyFromRule(ChameleonsParser::RewriteRuleContext* rCtx) {
  // Generate left side pattern and right side pattern
  std::istringstream ls{rCtx->sourcePattern()->getText()};
  std::unique_ptr<Pattern<T>> leftSide =
    Parser
    ::ParserSelect<lang>
    ::parser
    ::template parse<Pattern<T>, Utility::DYNAMIC>(&ls);

  std::istringstream rs{rCtx->targetPattern()->getText()};
  std::unique_ptr<Pattern<T>> rightSide =
     Parser
    ::ParserSelect<lang>
    ::parser
    ::template parse<Pattern<T>, Utility::DYNAMIC>(&rs);

  Rewrite::Rule<T> rule{
    rCtx->IDENTIFIER()->getText(),
    std::move(leftSide),
    std::move(rightSide),
    lang};

  // Spawning expression to handle where clause.
  // This part is optional, deal with if where expression
  // is present.
  if (rCtx->whereExprs() != nullptr) {
    bool success = createWhereExpressions(
      rCtx->whereExprs(),
      rule);
    if (!success) {
      // Program that where clause is in ill-formed
      // is unusable.
      throw std::runtime_error(
        "Failed to parse where clause.");
    }
  }

  return rule;
}

template<Base::GPTMeta T, int lang>
std::optional<Rewrite::StrategySeq<T>>
strategiesFromRules(ChameleonsParser::RewriteRulesContext* rCtx) {

  if (rCtx == nullptr) {
    return std::nullopt;
  }

  // Generate Rule from RewriteRuleContext
  std::optional<Rewrite::Rule<T>> ruleMaybe =
    strategyFromRule<T, lang>(rCtx->rewriteRule());
  if (!ruleMaybe.has_value()) {
    return std::nullopt;
  }

  // Then break the rule down into strategies
  Rewrite::StrategySeq<T> straSeq {
    Rewrite::ruleBreakDown(ruleMaybe.value())
  };

  std::optional<Rewrite::StrategySeq<T>>
    remain = strategiesFromRules<T, lang>(rCtx->rewriteRules());
  if (!remain.has_value()) {
    return straSeq;
  } else {
    // Concate two strategies sequences.
    straSeq.insert(
      straSeq.end(),
      std::make_move_iterator(remain.value().begin()),
      std::make_move_iterator(remain.value().end()));

    return straSeq;
  }
}

std::optional<std::unique_ptr<Program>>
programFromRules(ChameleonsParser::RewriteRulesContext* rCtx,
                 Base::GptSupportLang lang) {

  // Convergence condition
  if (rCtx == nullptr) {
    return std::nullopt;
  }

  switch (lang) {
  case Base::GptSupportLang::TESTLANG: {
    std::optional<Rewrite::StrategySeq<Adapter>>
      straMaybe = strategiesFromRules<Adapter,
                                      Base::GptSupportLang::TESTLANG>(rCtx);
    if (straMaybe.has_value()) {
      Rewrite::StrategySeq<Adapter> stras {std::move(straMaybe.value())};
      return std::make_unique<Program>(lang, stras);
    } else {
      return std::nullopt;
    }
    break;
  }
  default:
    return std::nullopt;
  }
}

std::unique_ptr<Program> Compiler::compile(std::istream& stream) {
  antlr4::ANTLRInputStream input(stream);
  ChameleonsLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  ChameleonsParser parser(&tokens);

  antlr4::tree::ParseTree *tree = parser.prog();

  // Use listener or visitor to traverse Chameleons
  // ParseTree then translate into Program.

  CompileListener listener;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  return std::move(listener.program);
}

} // Compiler
} // TransEngine
