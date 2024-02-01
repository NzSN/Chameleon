#include <plog/Log.h>
#include <stdexcept>
#include <optional>
#include <memory>

#include "ChameleonsParserMain.h"
#include "../ChameleonsParser.h"
#include "../ChameleonsParserBaseListener.h"


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

} // Compiler
} // TransEngine
