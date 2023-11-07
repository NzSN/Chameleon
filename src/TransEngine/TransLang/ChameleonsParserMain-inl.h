#include <stdexcept>
#include <optional>

#include "ChameleonsParserMain.h"
#include "ChameleonsLexer.h"
#include "ChameleonsParser.h"
#include "ChameleonsParserBaseListener.h"

#include "TransEngine/Rewrite/Environment.h"

namespace TransEngine {
namespace Compiler {

Base::GptGeneric
Program::operator()(Base::GptGeneric& tree,
                       Analyzer::AnalyzeDataGeneric& metaInfo) {

}

Base::GptGeneric
Program::operator()(Base::GptGeneric& tree) {

}

/////////////////////////////////////////////////////////////////////////////
//                                 Compiler                                //
/////////////////////////////////////////////////////////////////////////////
std::optional<Base::GptSupportLang>
toLangID(std::string);

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
      throw std::runtime_error(
        "TARGET Section is required\n");
    }
    if (ctx->ruleSection() == nullptr) {
      throw std::runtime_error(
        "RULE Section is required\n");
    }

    mode = ctx->strategySection() == nullptr ?
      DEFAULT : USER_DEFINED;

    // Next to determine which target language
    // the program need to deal with.
    auto langMaybe = toLangID(ctx->targetSection()
                          ->IDENTIFIER()
                          ->getText());
    if (langMaybe.has_value()) {
      targetLang = langMaybe.value();
    } else {
      throw std::runtime_error(
        "Unsupported language");
    }
  }

  void enterRewriteRules(ChameleonsParser::RewriteRulesContext* ctx) {
    if (mode == USER_DEFINED) {}

    /* Default Mode
     *
     * Break down all rules into strategies and
     * instantiate a Program instance from these
     * strategies. */

  }

  StrategeMode mode;
  Base::GptSupportLang targetLang;
};

Program Compiler::compile(std::istream& stream) {
  antlr4::ANTLRInputStream input(stream);
  ChameleonsLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  ChameleonsParser parser(&tokens);

  antlr4::tree::ParseTree *tree = parser.prog();

  // Use listener or visitor to traverse Chameleons
  // ParseTree then translate into Program.

  CompileListener listener;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
}


} // Compiler
} // TransEngine
