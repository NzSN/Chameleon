#ifndef GENERIC_PARSETREE_ANTLR4_GC_H_
#define GENERIC_PARSETREE_ANTLR4_GC_H_

#include "gc_defines.h"

#define DECLARE_AS_GC_OBJECT(PARSER, ENTRY, NODE) \
  class NODE##Context final: public PARSER::NODE##Context, \
                             public GCObject \
  {};


/////////////////////////////////////////////////////////////////////////////
//                             GC For Testlang                             //
/////////////////////////////////////////////////////////////////////////////
#include "src/Misc/testLanguage/TestLangParser.h"
#include "generic_parsetree_antlr4_testlang.h"

namespace Base::GC::Antlr::TestLang {

TEST_LANG_CONTEXTS(DECLARE_AS_GC_OBJECT);

} // Base::GC::Antlr::TestLang


/////////////////////////////////////////////////////////////////////////////
//                               GC For WGSL                               //
/////////////////////////////////////////////////////////////////////////////
#include "parsers/wgsl/WGSLParser.h"
#include "generic_parsetree_antlr4_wgsl.h"

namespace Base::GC::Antlr::WGSL {

WGSL_CONTEXTS(DECLARE_AS_GC_OBJECT);

} // Base::GC:Antlr::WGSL

#endif // GENERIC_PARSETREE_ANTLR4_GC_H_
