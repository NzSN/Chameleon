#ifndef GENERIC_PARSETREE_ANTLR4_GC_H_
#define GENERIC_PARSETREE_ANTLR4_GC_H_

#include "utility.h"
#include "gc_defines.h"

#include "antlr4-runtime.h"

#if ENABLE_GC

#define DECLARE_AS_GC_OBJECT(LANG, PARSER, ENTRY, NODE) \
  class NODE##Context final: public PARSER::NODE##Context, \
                             public GCObject \
  {                                          \
    public:                                                             \
    NODE##Context(antlr4::ParserRuleContext* ctx, int state):           \
      PARSER::NODE##Context(ctx, state) {}                              \
  };

#define MAPPING_CONTEXT_TO_GC_REALM(LANG, PARSER, ENTRY, NODE)  \
  template<>                                                    \
  struct TypeMapping <PARSER::NODE##Context> {                   \
    using type = Base::GC::Antlr::LANG::NODE##Context;                \
  };


namespace Base::GC::Antlr {

class TerminalNodeImpl final: public antlr4::tree::TerminalNodeImpl,
                              public GCObject
{
  public:

  explicit TerminalNodeImpl(antlr4::Token* symbol):
    antlr4::tree::TerminalNodeImpl(symbol) {}

};

} // Base::GC::Antlr

namespace Utility {

template<>
struct TypeMapping<antlr4::tree::TerminalNodeImpl> {
  using type = Base::GC::Antlr::TerminalNodeImpl;
};

} // Utility


/////////////////////////////////////////////////////////////////////////////
//                             GC For Testlang                             //
/////////////////////////////////////////////////////////////////////////////
#include "src/Misc/testLanguage/TestLangParser.h"
#include "generic_parsetree_antlr4_testlang.h"

namespace Base::GC::Antlr::TestLang {

TEST_LANG_CONTEXTS(DECLARE_AS_GC_OBJECT);

} // Base::GC::Antlr::TestLang

namespace Utility {

TEST_LANG_CONTEXTS(MAPPING_CONTEXT_TO_GC_REALM);

} // Utility

/////////////////////////////////////////////////////////////////////////////
//                               GC For WGSL                               //
/////////////////////////////////////////////////////////////////////////////
#include "parsers/wgsl/WGSLParser.h"
#include "generic_parsetree_antlr4_wgsl.h"

namespace Base::GC::Antlr::WGSL {

WGSL_CONTEXTS(DECLARE_AS_GC_OBJECT);

} // Base::GC:Antlr::WGSL

namespace Utility {

WGSL_CONTEXTS(MAPPING_CONTEXT_TO_GC_REALM)

} // Utility

#endif

#endif // GENERIC_PARSETREE_ANTLR4_GC_H_
