#ifndef CLASS_PROP_H
#define CLASS_PROP_H

#include <type_traits>
#include <concepts>

namespace Chameleon::CLASSPROP {

// For expresive purposes only

// Prevent object instantiae from this class.
#define UNINSTANTIALIZABLE(IDENT) IDENT() = delete

#define DISALLOW_HEAP_OBJECT_DIRECTLY \
  void* operator new(std::size_t) = delete; \
  void* operator new[](std::size_t) = delete;

} // CLSPROP


#endif /* CLASS_PROP_H */
