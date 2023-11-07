#ifndef CHAMELEONSPARSERMAIN_H
#define CHAMELEONSPARSERMAIN_H

#include "Base/generic_parsetree.h"
#include "Analysis/analyzer.h"
#include "GenericTypes.h"

#include "TransEngine/Rewrite/Strategy-inl.h"

namespace TransEngine {
namespace Compiler {

// Program is consist of sequence of strategies.
class Program {
public:
  Base::GptGeneric
  operator()(Base::GptGeneric& tree,
             Analyzer::AnalyzeDataGeneric& metaInfo);

  // program run in this case, without metainfo,
  // has no syntax and semantcis knowledge about
  // target parsetree.
  Base::GptGeneric operator()(Base::GptGeneric& tree);

private:
  std::string targetLang;
  Rewrite::StrategySeqGeneric strategies_;
};

// Compile rule configuration into
// program that do transformation onto
// ParseTree of target languages.
struct Compiler {

  Program compile(std::istream& input);

};

} // Compiler
} // TransEngine

#endif /* CHAMELEONSPARSERMAIN_H */
