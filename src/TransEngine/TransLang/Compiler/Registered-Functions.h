#ifndef REGISTERED_FUNCTIONS_H
#define REGISTERED_FUNCTIONS_H

#include "Refl.h"
#include "Functions.h"
#include "GenericTypes.h"


// Register functions of correspond lang to reflect system.
inline void registerFunctions(Base::GptSupportLang lang) {

#define REGISTER_FUNCTIONS(F)                       \
  Utility::Refl::DefaultRefl::addReflectType(       \
    Stringify(F),                                   \
    [](std::optional<std::any> arg) -> std::any {   \
      return new F();                               \
    })

  switch (lang) {
  case Base::GptSupportLang::TESTLANG:
    // Register all TestLang Functions
    TESTLANG_FUNCTIONS(REGISTER_FUNCTIONS);
    break;
  default:
    return;
  }

#undef REGISTER_FUNCTIONS
}

#endif /* REGISTERED_FUNCTIONS_H */
