#ifndef CHAMELEONSPARSERMAIN_H
#define CHAMELEONSPARSERMAIN_H

#include "Base/generic_parsetree.h"
#include "Analysis/analyzer.h"
#include "TransEngine/Rewrite/Strategy-inl.h"

namespace TransEngine {
namespace Compiler {

// Program is consist of sequence of strategies.
template<typename T>
struct Program {
  Rewrite::StrategySeq<T> strategies;

  Base::GenericParseTree<T>
  operator()(Base::GenericParseTree<T>& tree,
             Analyzer::AnalyzeData<T>& metaInfo);

  // program run in this case, without metainfo,
  // has no syntax and semantcis knowledge about
  // target parsetree.
  Base::GenericParseTree<T>
  operator()(Base::GenericParseTree<T>& tree);
};

// Compile rule configuration into
// program that do transformation onto
// ParseTree of target languages.
template<typename T>
struct Compiler {

  Program<T> compile(std::istream& input);

};

} // Compiler
} // TransEngine

#endif /* CHAMELEONSPARSERMAIN_H */
