#ifndef REGISTERED_FUNCTIONS_H
#define REGISTERED_FUNCTIONS_H

#include "Refl.h"
#include "Functions.h"
#include "GenericTypes.h"

namespace TransEngine {
namespace Compiler {

// Register functions of correspond lang to reflect system.
inline void registerFunctions(Base::GptSupportLang lang) {

#define REGISTER_FUNCTIONS(F)                       \
  Utility::Reflection::registering(                 \
    Stringify(F),                                   \
    []() -> Utility::Var {                          \
      return Utility::Var{new F()};                 \
    })

  switch (lang) {
  case Base::GptSupportLang::TESTLANG:
    // Register all TestLang Functions
    TESTLANG_FUNCTIONS(REGISTER_FUNCTIONS);
    break;
  case Base::GptSupportLang::WGSL:
    WGSL_FUNCTIONS(REGISTER_FUNCTIONS);
  default:
    return;
  }

#undef REGISTER_FUNCTIONS
}

} // Compiler
} // TransEngine

#endif /* REGISTERED_FUNCTIONS_H */
