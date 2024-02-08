#include <gtest/gtest.h>
#include "Transformer.h"

namespace Chameleon::api {

TEST(ApiUnittests, RuleIntroduce) {
  Transformer<GET_LANG_TYPE(TESTLANG)> t{
    // { LeftSide Pattern, Where Clause (Optional), RightSide Pattern }
    {"a + a", "a := a;","2 * a"},
    {"a + a", "a := a;","2 * a"},
    {"a + a", "2 * a"},
  };

  Transformer<GET_LANG_TYPE(TESTLANG)> t1{
    {"a + a", "a := a;","2 * a"},
  };
  Transformer<GET_LANG_TYPE(TESTLANG)> t2{
    {"a + a", "a := a;","2 * a"},
  };
  Transformer<GET_LANG_TYPE(TESTLANG)> t3{
    {"a + a", "2 * a"},
  };

  Transformer<GET_LANG_TYPE(TESTLANG)> t4 = t1 + t2 + t3;

  EXPECT_TRUE(t.ruleSize() == t4.ruleSize());
  EXPECT_TRUE(t == t4);
  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 == t3);
  EXPECT_FALSE(t == t1);
  EXPECT_FALSE(t == t2);
  EXPECT_FALSE(t == t3);
}

TEST(ApiUnittests, Transform) {
  Transformer<GET_LANG_TYPE(TESTLANG)> t{
    // { LeftSide Pattern, Where Clause (Optional), RightSide Pattern }
    {"a + 2", "2 * a"},
    {"2 * a", "a + a"},
    {"a + b", "b + 3"}
  };

  EXPECT_TRUE(t("1 + 2").value() == "1+3");
}

} // Chameleon::api
