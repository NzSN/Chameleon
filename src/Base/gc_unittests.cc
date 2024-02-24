#include <gtest/gtest.h>
#include "gc_defines.h"

#if ENABLE_GC

namespace Chameleon::Base::GC {

template<typename T>
struct NumSeq : public GCObject {
  NumSeq(T a): v{a} {}
  T v;

  operator T() const {
    T num = v;
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

struct Storage {
  std::vector<NumSeq<int>*> nums;
};

TEST(GCObject, Basic) {
  auto cppgc_platform = std::make_shared<cppgc::DefaultPlatform>();
  cppgc::InitializeProcess(cppgc_platform->GetPageAllocator());
  {
    std::unique_ptr<cppgc::Heap> heap = cppgc::Heap::Create(cppgc_platform);

    NumSeq<int>* seq_1 = cppgc::MakeGarbageCollected<NumSeq<int>>(
      heap->GetAllocationHandle(), 1);
    NumSeq<int>* seq_2 = cppgc::MakeGarbageCollected<NumSeq<int>>(
      heap->GetAllocationHandle(), 2);

    std::vector<Storage> storages{};
    storages.push_back(Storage{});

    storages.front().nums.push_back(seq_1);

    seq_1->reach(seq_2);
    seq_1 = nullptr;
    seq_2 = nullptr;

    heap->ForceGarbageCollectionSlow("CppGC example", "Testing");
    seq_1 = storages.front().nums.front();

    EXPECT_TRUE(seq_1 == 3);
  }
}


} // Chameleon::Base::GC

#endif
