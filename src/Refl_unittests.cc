#include <gtest/gtest.h>

#include "Refl.h"

using Refl = Utility::Refl::Refl;

struct ARefl {
  int value() { return 0; }
};

TEST(ReflTests, Basics) {
  ARefl s = Refl::reflect<ARefl>("ARefl");
  ASSERT_EQ(0, s.value());
}
