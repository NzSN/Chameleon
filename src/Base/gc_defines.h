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

struct GC {
  GC(): platform_{std::make_shared<cppgc::DefaultPlatform>()} {
    cppgc::InitializeProcess(platform_->GetPageAllocator());
  }

  ~GC() {
    cppgc::ShutdownProcess();
  }

private:
 std::shared_ptr<cppgc::DefaultPlatform> platform_;
};


class GCObject: public cppgc::GarbageCollected<GCObject> {
public:
  void Trace(cppgc::Visitor* visitor) const {
    for (auto& o: objs_) {
      visitor->Trace(o);
    }
  }
  void newReach(GCObject *obj) {
    objs_.push_back(obj);
  }
private:
  std::list<cppgc::Member<GCObject>> objs_;
};


}


#endif /* GC_DEFINES_H */
