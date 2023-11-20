#ifndef CHAMELEONSPARSERMAIN_H
#define CHAMELEONSPARSERMAIN_H

#include <optional>

#include "Base/generic_parsetree.h"
#include "Analysis/analyzer.h"
#include "GenericTypes.h"

#include "TransEngine/Rewrite/Strategy-inl.h"

namespace TransEngine {
namespace Compiler {

// Program is consist of sequence of strategies.
class Program {
public:
  Program(Base::GptSupportLang lang,
          Rewrite::StrategySeqGeneric& stras):
    lang_{lang}, strategies_{std::move(stras)} {}

  std::optional<Base::GptGeneric>
  operator()(Base::GptGeneric& tree,
             Analyzer::AnalyzeDataGeneric& metaInfo);

  // program run in this case, without metainfo,
  // has no syntax and semantcis knowledge about
  // target parsetree.
  std::optional<Base::GptGeneric>
  operator()(Base::GptGeneric& tree);

private:
  Base::GptSupportLang lang_;

  Rewrite::StrategySeqGeneric strategies_;
};

// Compile rule configuration into
// program that do transformation onto
// ParseTree of target languages.
struct Compiler {

  std::shared_ptr<Program> compile(std::istream& input);

};

} // Compiler
} // TransEngine

#endif /* CHAMELEONSPARSERMAIN_H */
