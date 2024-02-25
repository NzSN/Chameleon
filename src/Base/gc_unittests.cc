#include <gtest/gtest.h>
#include <sstream>
#include "gc_defines.h"

#include "langs.h"
#include "Parser/Parser-inl.h"
#include "TransEngine/SigmaTerm.h"

#if ENABLE_GC

namespace Chameleon::Base::GC {

template<typename T>
struct NumSeq : public GCObject,
                public ContextInfo {
  NumSeq(T a): v{a}, ContextInfo(typeid(NumSeq<T>).name()) {}
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
  NumSeq<int>* nums() { return nums_; }
  void setNums(NumSeq<int>* nums) { nums_ = nums; }

  Storage* another() { return another_.get(); }
  void setAnother(std::unique_ptr<Storage>&& another) {
    another_ = std::move(another);
  }
private:
  NumSeq<int>* nums_;
  std::unique_ptr<Storage> another_;
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

    std::unique_ptr<Storage> storage_0 = std::make_unique<Storage>();
    storage_0->setAnother(std::make_unique<Storage>());
    storage_0->another()->setAnother(std::make_unique<Storage>());

    storage_0->another()->setNums(seq_1);
    storage_0->another()->another()->setNums(seq_2);

    seq_1->reach(seq_2);
    seq_1 = nullptr;
    seq_2 = nullptr;

    heap->ForceGarbageCollectionSlow("CppGC example", "Testing");
    seq_1 = storage_0->another()->nums();

    EXPECT_TRUE(*seq_1 == 3);
  }

  cppgc::ShutdownProcess();
}

// TEST(ParseTreeWithGC, Basic) {
//   auto cppgc_platform = std::make_shared<cppgc::DefaultPlatform>();
//   cppgc::InitializeProcess(cppgc_platform->GetPageAllocator());

//   {
//     std::unique_ptr<cppgc::Heap> heap = cppgc::Heap::Create(cppgc_platform);
//     Base::GC::Process::gc_heap = heap.get();

//     std::istringstream s{"a + b"};
//     auto t = Parser::ParserSelect<GET_LANG_TYPE(TESTLANG)>
//       ::parser
//       ::parse<Base::ParseTree<Base::Antlr4Node>>(&s);
//     auto t_copy = t.getMeta().clone();

//     heap->ForceGarbageCollectionSlow("ParseTreeWithGC.Basic", "Test");
//     t_copy->getText();
//   }
//}

// TEST(ParseTreeWithGC, Basic_1) {
//   auto cppgc_platform = std::make_shared<cppgc::DefaultPlatform>();
//   cppgc::InitializeProcess(cppgc_platform->GetPageAllocator());

//   {
//     std::unique_ptr<cppgc::Heap> heap = cppgc::Heap::Create(cppgc_platform);
//     Base::GC::Process::gc_heap = heap.get();

//     std::istringstream s{"a+b"};
//     auto env = Utility::Antlr4Parse<TestLangLexer, TestLangParser>(s);
//     auto tree = env->parser.prog();

//     Base::Antlr4Node nodes{Base::TESTLANG, tree};
//     std::unique_ptr<Base::Antlr4Node> copy = nodes.clone();

//     auto gcObj = dynamic_cast<Base::GC::GCObject*>(copy->tree());
//     EXPECT_TRUE(gcObj->objs().size() == 1);
//     gcObj = nullptr;

//     heap->ForceGarbageCollectionSlow("ParseTreeWithGC.Basic", "Test");
//     std::cout << copy->getText() << std::endl;
//   }
// }

//   cppgc::ShutdownProcess();
// }


} // Chameleon::Base::GC

#endif
