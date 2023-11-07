#include <variant>

#ifndef GENERICTYPES_H
#define GENERICTYPES_H


/////////////////////////////////////////////////////////////////////////////
//                        GenericParseTree Generics                        //
/////////////////////////////////////////////////////////////////////////////
#include "Base/generic_parsetree_types.h"

/////////////////////////////////////////////////////////////////////////////
//                            Analyzer Generics                            //
/////////////////////////////////////////////////////////////////////////////
#include "Analysis/analyzer.h"
namespace Analyzer {

using AnalyzeDataGeneric =
  std::variant<
  AnalyzeData<Base::Antlr4Node>
  >;

} // Analyzer

/////////////////////////////////////////////////////////////////////////////
//                            Strategy Generics                            //
/////////////////////////////////////////////////////////////////////////////
#include "TransEngine/Rewrite/Strategy-inl.h"

namespace TransEngine {
namespace Rewrite {

using StrategyGeneric =
  std::variant<
  Strategy<Base::Antlr4Node>
  >;
using StrategySeqGeneric =
  std::variant<
  StrategySeq<Base::Antlr4Node>
  >;
using StrategySetGeneric =
  std::variant<
  StrategySet<Base::Antlr4Node>
  >;

} // Rewrite
} // TransEngine


#endif /* GENERICTYPES_H */
