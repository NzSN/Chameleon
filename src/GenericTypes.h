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

using StrategyAntlr4 =
  std::variant<
  MatchStra<Base::Antlr4Node>,
  BuildStra<Base::Antlr4Node>
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

/////////////////////////////////////////////////////////////////////////////
//                                   Rule                                  //
/////////////////////////////////////////////////////////////////////////////
#include "TransEngine/Rewrite/Rule.h"

namespace TransEngine {
namespace Rewrite {

using RuleGeneric =
  std::variant<
  Rule<Base::Antlr4Node>
  >;

} // Rewrite
} // TransEngine



#endif /* GENERICTYPES_H */
