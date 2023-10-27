#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "Environment.h"
#include "Base/generic_parsetree.h"

namespace TransEngine {
namespace Rewrite {

struct BindingsTests: public ::testing::Test {
  void SetUp() override {}
};


TEST_F(BindingsTests, Basics) {
  Bindings<int> binds;

  // Add bindins
  auto t = Base::GenericParseTree<int>(1);
  Term<int> term{t};
  binds.bind("id1", term);

  RC_ASSERT(binds.isBinded("id1"));
  RC_ASSERT(term == binds["id1"]);

  binds.unbind("id1");
  RC_ASSERT_FALSE(binds.isBinded("id1"));
}

} // Rewrite
} // TransEngine
