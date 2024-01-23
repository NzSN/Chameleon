#ifndef GC_DEFINES_H
#define GC_DEFINES_H

#include <list>

#include "cppgc/allocation.h"
#include "cppgc/default-platform.h"
#include "cppgc/garbage-collected.h"
#include "cppgc/heap.h"
#include "cppgc/member.h"
#include "cppgc/visitor.h"

namespace Base::GC {

namespace Process {
inline cppgc::Heap* gc_heap = nullptr;
}


struct GC {
  GC(): platform_{std::make_shared<cppgc::DefaultPlatform>()} {
    cppgc::InitializeProcess(platform_->GetPageAllocator());
    heap_ = cppgc::Heap::Create(platform_);

    Process::gc_heap = heap_.get();
  }

  cppgc::Heap* heap() {
    return heap_.get();
  }

  ~GC() {
    cppgc::ShutdownProcess();
    Process::gc_heap = nullptr;
  }

private:
  std::shared_ptr<cppgc::DefaultPlatform> platform_;
  std::unique_ptr<cppgc::Heap> heap_;
};

class GCObject: public cppgc::GarbageCollected<GCObject> {
public:
  void Trace(cppgc::Visitor* visitor) const {
    for (auto& o: objs_) {
      visitor->Trace(o);
    }
  }
  void reach(GCObject *obj) {
    objs_.push_back(obj);
  }
private:
  std::list<cppgc::Member<GCObject>> objs_;
};

}


#endif /* GC_DEFINES_H */
