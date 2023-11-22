#include <iostream>

#include <type_traits>
#include <optional>
#include <ranges>
#include <unordered_map>
#include <stdexcept>

#include "TransEngine/Rewrite/Environment.h"
#include "TransEngine/Rewrite/Rule.h"
#include "ChameleonsParserMain-inl.h"

namespace TransEngine {
namespace Compiler {

std::optional<Base::GptGeneric>
Program::operator()(Base::GptGeneric& tree,
                    Analyzer::AnalyzeDataGeneric& metaInfo) {
  /* FIXME: Need to implement */
  return std::nullopt;
}

std::optional<Base::GptGeneric>
EvalTestLang(Base::GptGeneric& tree,
             Rewrite::StrategySeqGeneric& straSeq) {
  using StraSeqAntlr4 = Rewrite::StrategySeq<Base::Antlr4Node>;

  // Convert to concrete type, TestLang
  // use Antlr4 ParseTree to represent
  // it's grammar structure.
  Base::Antlr4GPT treeAntlr4 =
    std::get<Base::Antlr4GPT>(tree);

  // Apply same process to strategies
  Rewrite::StrategySeq<Base::Antlr4Node>
    seq = std::move(std::get<StraSeqAntlr4>(straSeq));

  // Checking that all strategies are binded with
  // rules.
  for (auto& s: seq) {
    if (s->bindedRule.leftSide == nullptr ||
        s->bindedRule.rightSide == nullptr) {
      // Strategy must binded with a rule
      throw std::runtime_error(
        "Strategy to be evaluated must be binded with rule");
    }
  }

  // Setup environment
  Environment<Base::Antlr4Node> env{};
  env.setTargetTerm(&treeAntlr4);

  // Evaluating all strategies with
  // target rules.
  for (auto& s: seq) {
    (*s)(s->bindedRule, env);
  }

  return treeAntlr4;
}

std::optional<Base::GptGeneric>
Program::operator()(Base::GptGeneric& tree) {
  switch (lang_) {
  case Base::GptSupportLang::TESTLANG:
    return EvalTestLang(tree, strategies_);
    break;
  }

  return std::nullopt;
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

namespace {

template<Base::GPTMeta T>
bool createCondExpr(
  ChameleonsParser::CondExprContext* rCtx,
  Rewrite::Rule<T>& rule) {

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

}

std::optional<std::shared_ptr<Program>>
programFromRules(ChameleonsParser::RewriteRulesContext* rCtx,
                 Base::GptSupportLang lang) {

  // Convergence condition
  if (rCtx == nullptr) {
    return std::nullopt;
  }

  switch (lang) {
  case Base::GptSupportLang::TESTLANG: {
    std::optional<Rewrite::StrategySeq<Base::Antlr4Node>>
      straMaybe = strategiesFromRules<Base::Antlr4Node,
                                      Base::GptSupportLang::TESTLANG>(rCtx);
    if (straMaybe.has_value()) {
      Rewrite::StrategySeqGeneric stras {std::move(straMaybe.value())};
      return std::make_shared<Program>(lang, stras);
    } else {
      return std::nullopt;
    }
    break;
  }
  default:
    return std::nullopt;
  }
}

std::shared_ptr<Program> Compiler::compile(std::istream& stream) {
  antlr4::ANTLRInputStream input(stream);
  ChameleonsLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  ChameleonsParser parser(&tokens);

  antlr4::tree::ParseTree *tree = parser.prog();

  // Use listener or visitor to traverse Chameleons
  // ParseTree then translate into Program.

  CompileListener listener;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  return listener.program;
}

} // Compiler
} // TransEngine
