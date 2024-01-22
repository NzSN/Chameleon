#ifndef CHAMELEONSPARSERMAIN_H
#define CHAMELEONSPARSERMAIN_H

#include <optional>

#include "Base/generic_parsetree_antlr4.h"
#include "Analysis/analyzer.h"
#include "GenericTypes.h"

#include "TransEngine/Rewrite/Strategy-inl.h"

namespace TransEngine {
namespace Compiler {

using Adapter = Base::Antlr4Node;

// Program is consist of sequence of strategies.
class Program {
public:
  Program(Base::GptSupportLang lang):
    lang_{lang}, strategies_{} {}

  Program(Base::GptSupportLang lang,
          Rewrite::StrategySeq<Adapter>&& stras):
    lang_{lang}, strategies_{std::move(stras)} {}

  bool write(Rewrite::StrategyUnique<Adapter> stra) {
    strategies_.push_back(std::move(stra));
    return true;
  }

  Base::SUPPORTED_LANGUAGE lang() const {
    return lang_;
  }

  std::optional<Base::GptGeneric>
  operator()(Base::GptGeneric& tree,
             Analyzer::AnalyzeDataGeneric& metaInfo);

  // program run in this case, without metainfo,
  // has no syntax and semantcis knowledge about
  // target parsetree.
  std::optional<Base::GenericParseTree<Adapter>>
  operator()(Base::GenericParseTree<Adapter>& tree);

private:
  Base::GptSupportLang lang_;

  Rewrite::StrategySeq<Adapter> strategies_;
};

// Compile rule configuration into
// program that do transformation onto
// ParseTree of target languages.
struct Compiler {

  std::unique_ptr<Program> compile(std::istream& input);

};

class ChameleonsMain {
public:
  using SUPPORTED_LANG = Base::SUPPORTED_LANGUAGE;

  ChameleonsMain(std::istream* ruleConfig, std::istream* targetCodes):
    ruleConfig_(ruleConfig), targetCodes_(targetCodes) {}

  std::optional<std::string>
  operator()() {
    // Spawn Rule Compiler
    Compiler compiler;

    // Initialize GC
    Utility::ScopeGC gc{};

    // Compiling Rule into program
    std::unique_ptr<Program> program =
      compiler.compile(*ruleConfig_);
    Base::SUPPORTED_LANGUAGE lang = program->lang();

    // Transforming
    std::optional<std::string> transedProg = ([&] {
      switch (lang) {
      case SUPPORTED_LANG::TESTLANG:
        return transform<SUPPORTED_LANG::TESTLANG>(program.get());
      case SUPPORTED_LANG::WGSL:
        return transform<SUPPORTED_LANG::WGSL>(program.get());
      default:
        std::unreachable();
      }
    })();

    return transedProg;
  }

private:
  template<SUPPORTED_LANG lang = SUPPORTED_LANG::TESTLANG>
  requires Base::isTestLang<lang>
  Base::GptGeneric parse(std::istream* s) {
    return
      Parser
      ::ParserSelect<Base::SUPPORTED_LANGUAGE::TESTLANG>
      ::parser
      ::parse<Base::GenericParseTree<Base::Antlr4Node>>(s);
  }

  template<SUPPORTED_LANG lang = SUPPORTED_LANG::TESTLANG>
  requires Base::isWGSL<lang>
  Base::GptGeneric parse(std::istream* s) {
    return
      Parser
      ::ParserSelect<Base::SUPPORTED_LANGUAGE::WGSL>
      ::parser
      ::parse<Base::GenericParseTree<Base::Antlr4Node>>(s);
  }

  template<SUPPORTED_LANG lang = SUPPORTED_LANG::TESTLANG>
  requires Base::isTestLang<lang> ||
           Base::isWGSL<lang>
  std::optional<std::string> transform(Program* program) {
    using Tree = Base::GenericParseTree<Base::Antlr4Node>;
    Base::GptGeneric tree = parse<lang>(targetCodes_);

    Tree t = std::get<Tree>(tree);

    return (*program)(t).transform(
      [](auto&& tree) {
        return tree.getText();
      });
  }

  std::istream* ruleConfig_;
  std::istream* targetCodes_;
};


} // Compiler
} // TransEngine

#endif /* CHAMELEONSPARSERMAIN_H */
