#ifndef GENERIC_PARSETREE_ANTLR4_GC_H_
#define GENERIC_PARSETREE_ANTLR4_GC_H_

#include "utility.h"
#include "gc_defines.h"

#include "antlr4-runtime.h"

#if ENABLE_GC

namespace Chameleon::Base::GC {

struct ContextInfo {
  ContextInfo(std::string typeName_): typeName{typeName_} {}
  std::string typeName;
};

} // Chameleon::Base::GC

#define DECLARE_AS_GC_OBJECT(LANG, PARSER, ENTRY, NODE)                                       \
  class NODE##Context final:  public GCObject,                                                \
                              public ContextInfo,                                             \
                              public PARSER::NODE##Context                                    \
  {                                                                                           \
public:                                                                                       \
    NODE##Context(antlr4::ParserRuleContext* ctx, int state):                                   \
      PARSER::NODE##Context(ctx, state), ContextInfo(typeid(PARSER::NODE##Context).name()) {} \
  };

#define MAPPING_CONTEXT_TO_GC_REALM(LANG, PARSER, ENTRY, NODE)  \
  template<>                                                    \
  struct TypeMapping <PARSER::NODE##Context> {                   \
    using type = Base::GC::Antlr::LANG::NODE##Context;                \
  };


namespace Chameleon::Base::GC::Antlr {

class TerminalNodeImpl final: public GCObject,                         \
                              public antlr4::tree::TerminalNodeImpl  \
{
  public:

  explicit TerminalNodeImpl(antlr4::Token* symbol):
    antlr4::tree::TerminalNodeImpl(symbol) {}

};

} // Base::GC::Antlr

namespace Chameleon::Utility {

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

namespace Chameleon::Base::GC::Antlr::TestLang {

TEST_LANG_CONTEXTS(DECLARE_AS_GC_OBJECT);

} // Base::GC::Antlr::TestLang

namespace Chameleon::Utility {

TEST_LANG_CONTEXTS(MAPPING_CONTEXT_TO_GC_REALM);

} // Utility

/////////////////////////////////////////////////////////////////////////////
//                               GC For WGSL                               //
/////////////////////////////////////////////////////////////////////////////
#include "parsers/wgsl/WGSLParser.h"
#include "generic_parsetree_antlr4_wgsl.h"

namespace Chameleon::Base::GC::Antlr::WGSL {

WGSL_CONTEXTS(DECLARE_AS_GC_OBJECT);

} // Base::GC:Antlr::WGSL

namespace Chameleon::Utility {

WGSL_CONTEXTS(MAPPING_CONTEXT_TO_GC_REALM)

} // Utility

#endif

#endif // GENERIC_PARSETREE_ANTLR4_GC_H_
