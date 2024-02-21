#include <gtest/gtest.h>
#include "gc_defines.h"

namespace Chameleon::Base::GC {

struct NumSeq : public GCObject {
  NumSeq(int a): v{a} {}
  int v;

  operator int() const {
    int num = v;
    for (auto& s: const_cast<NumSeq*>(this)->GCObject::objs()) {
      num += dynamic_cast<NumSeq*>(s.Get())->v;
    }
    return num;
  }

  friend std::ostream& operator<<(std::ostream& os, NumSeq& seq) {
    os << seq.v;
    for (auto& s: seq.objs()) {
      os << dynamic_cast<NumSeq*>(s.Get())->v << std::endl;
    }

    return os;
  }
};

TEST(GCObject, Basic) {
  auto cppgc_platform = std::make_shared<cppgc::DefaultPlatform>();
  cppgc::InitializeProcess(cppgc_platform->GetPageAllocator());
  {
    std::unique_ptr<cppgc::Heap> heap = cppgc::Heap::Create(cppgc_platform);

    NumSeq* seq_1 = cppgc::MakeGarbageCollected<NumSeq>(
      heap->GetAllocationHandle(), 1);
    NumSeq* seq_2 = cppgc::MakeGarbageCollected<NumSeq>(
      heap->GetAllocationHandle(), 2);

    seq_1->reach(seq_2);

    heap->ForceGarbageCollectionSlow("CppGC example", "Testing");

    EXPECT_TRUE(*seq_1 == 3);
  }
}


} // Chameleon::Base::GC
