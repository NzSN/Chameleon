
#include "config.h"

#if ENABLE_GC
#include "gc_defines.h"
#endif

namespace Base {

template<typename T,
         Config::Configs gcState = Config::Configs::GC,
         typename ...ARGS>
requires Config::isGCEnable<gcState>
T* genericNew(ARGS ...args) {
  return cppgc::MakeGarbageCollected<T>(
    Base::GC::Process::gc_heap->GetAllocationHandle(),
    args...);
}

template<typename T,
         Config::Configs gcState = Config::Configs::GC,
         typename ...ARGS>
requires (!Config::isGCEnable<gcState>)
T* genericNew(ARGS ...args) {
  return new T(args...);
}


} // Base
