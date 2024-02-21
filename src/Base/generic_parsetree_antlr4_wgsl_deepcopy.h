#ifndef GENERIC_PARSETREE_WGSL_DEEPCOPY_H_
#define GENERIC_PARSETREE_WGSL_DEEPCOPY_H_

#include "generic_parsetree_antlr4_wgsl.h"
#include "generic_parsetree_antlr4_deepcopy.h"
#include "parsers/wgsl/WGSLBaseListener.h"

namespace Chameleon::WGSL {

DEEPCOPY_IMPL(
  WGSLBaseListener,
  WGSL_CONTEXTS);

} // WGSL


#endif // GENERIC_PARSETREE_WGSL_DEEPCOPY_H_
