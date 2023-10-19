#include <gtest/gtest.h>
#include <optional>
#include <any>

#include "Refl.h"

namespace Refl = Utility::Refl;

struct ARefl {
  int value() { return 0; }
};

TEST(ReflTests, Basics) {
  bool success = Refl::DefaultRefl::addReflectType(
    Stringify(ARefl),
    [](std::optional<std::any> arg) -> std::any {
      return ARefl{};
    });
  ASSERT_TRUE(success);

  ARefl v = Utility::Refl::DefaultRefl::
    reflect<ARefl>("Arefl");

  ASSERT_EQ(v.value(), 0);
}
