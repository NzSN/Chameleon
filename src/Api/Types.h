#ifndef CHAMELEON_TYPES_H
#define CHAMELEON_TYPES_H

#include "Base/generic_parsetree.h"
#include "Base/generic_parsetree_antlr4.h"

namespace Chameleon {
namespace api::Types {

using AntlrParseTree = Base::ParseTree<Base::Antlr4Node>;

} // Types
} // Chameleon


#endif /* CHAMELEON_TYPES_H */
