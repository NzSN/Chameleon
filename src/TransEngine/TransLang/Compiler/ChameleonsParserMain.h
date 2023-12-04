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
          Rewrite::StrategySeq<Adapter>& stras):
    lang_{lang}, strategies_{std::move(stras)} {}

  bool write(Rewrite::StrategyUnique<Adapter> stra) {
    strategies_.push_back(std::move(stra));
    return true;
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

} // Compiler
} // TransEngine

#endif /* CHAMELEONSPARSERMAIN_H */
