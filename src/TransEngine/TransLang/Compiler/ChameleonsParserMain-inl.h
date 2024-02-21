#include <plog/Log.h>
#include <stdexcept>
#include <optional>
#include <memory>
#include <algorithm>

#include "Base/langs.h"
#include "ChameleonsParserMain.h"
#include "../ChameleonsParser.h"
#include "../ChameleonsParserBaseListener.h"

#include "TransEngine/TransLang/Compiler/WhereClauseExprParsing-inl.h"

namespace Chameleon {
namespace TransEngine {
namespace Compiler {
/////////////////////////////////////////////////////////////////////////////
//                                 Compiler                                //
/////////////////////////////////////////////////////////////////////////////
std::optional<Base::GptSupportLang>
toLangID(std::string);

std::optional<std::unique_ptr<Program>>
programFromRules(ChameleonsParser::RewriteRulesContext *rCtx,
                 Base::GptSupportLang lang);

// Construct first rule a given Chameleon Script.
template<Base::isLangType L, Base::Layer T>
struct RuleConstructListener: public ChameleonsParserBaseListener {

  void enterRewriteRule(ChameleonsParser::RewriteRuleContext *ctx) {
    assertm(ctx->sourcePattern(), "No Source Pattern found in Rewrite Rule");
    assertm(ctx->targetPattern(), "No Target Pattern found in Rewrite Rule");

    std::string sourcePattern = ctx->sourcePattern()->getText();
    std::string targetPattern = ctx->targetPattern()->getText();

    Rewrite::Rule<T> rule = Rewrite::Rule<T>::template makeRule<L>(
      "", sourcePattern, targetPattern);

    if (ctx->whereExprs()) {
      std::vector<WhereClause::Expr_uptr> exprs =
        WhereClause::toExprs(*ctx->whereExprs());
      std::vector<Rewrite::CondExpr> condExprs(exprs.size());
      std::transform(exprs.begin(), exprs.end(), condExprs.begin(),
                     [](WhereClause::Expr_uptr& expr) {
                       return Rewrite::CondExpr(std::move(expr));
                     });
      rule.setConds(std::move(condExprs));
    }

    rules.push_back(rule);
  }

  std::vector<Rewrite::Rule<T>> rules;
};

struct CompileListener: public ChameleonsParserBaseListener {

  enum StrategeMode {
    // Without definition of Strategy. In this mode,
    // the generated program just aplly all strategy
    // to target parsetree in order.
    DEFAULT,
    // User defined strategy will cover the behaviror.
    USER_DEFINED
  };

  void enterProg(ChameleonsParser::ProgContext* ctx) {
    // Sections that required to form
    // a minimal Chameleons Program.
    //
    // Strategies section is optional so
    // no need to check.
    if (ctx->targetSection() == nullptr) {
      PLOG_DEBUG << "Target section is required";

      throw std::runtime_error(
        "TARGET Section is required\n");
    }
    if (ctx->ruleSection() == nullptr) {
      PLOG_DEBUG << "Rule section is required";

      throw std::runtime_error(
        "RULE Section is required\n");
    }

    mode = ctx->strategySection() == nullptr ?
      DEFAULT : USER_DEFINED;

    // Next to determine which target language
    // the program need to deal with.
    std::string langStr = ctx->targetSection()
                          ->IDENTIFIER()
                          ->getText();
    auto langMaybe = toLangID(langStr);
    if (langMaybe.has_value()) {
      targetLang = langMaybe.value();
      PLOG_DEBUG << "Target lang is " + langStr;
    } else {
      PLOG_DEBUG << "Lang " + langStr + " is not supported";
      throw std::runtime_error(
        "Unsupported language");
    }
  }

  void enterRewriteRules(ChameleonsParser::RewriteRulesContext* ctx) {

    if (mode == USER_DEFINED) {
      /* FIXME: Need to implement */
      PLOG_DEBUG << "Parsing RewriteRule in USER_DEFINED "
                    "Mode due to Strategies section is provide";
    }

    PLOG_DEBUG << "Parsing RewriteRule in DefaultMode";

    /* Default Mode
     *
     * Break down all rules into strategies and
     * instantiate a Program instance from these
     * strategies. */
    auto progMaybe = programFromRules(
      ctx, targetLang);
    if (!progMaybe.has_value()) {
      program = nullptr;
    } else {
      program = std::move(progMaybe.value());
    }
  }

  std::unique_ptr<Program> program;
  StrategeMode mode;
  Base::GptSupportLang targetLang;
};

template<Base::isLangType L>
std::vector<Rewrite::Rule<Adapter>>
Compiler::compileToRule(std::istream& input) {
  std::vector<Rewrite::Rule<Adapter>> rules;

  PLOG_DEBUG << "Compiling (compileToRule)...";

  auto env = Utility::Antlr4Parse<
  ChameleonsLexer, ChameleonsParser>(input);

  antlr4::tree::ParseTree *tree = env->parser.prog();
  if (!tree) {
    PLOG_DEBUG << "Failed to parse...";
    return rules;
  }

  RuleConstructListener<L, typename Base::LangArg<L>::Adapter>
    rulesCtor;

  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&rulesCtor, tree);
  assertm(!rulesCtor.rules.empty(),
          "Compiler::compileToRule: failed to parse rule from given script");
  rules = std::move(rulesCtor.rules);

  return rules;
}


} // Compiler
} // TransEngine
} // Chameleon
