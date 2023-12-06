#include <gtest/gtest.h>
#include <optional>
#include <any>
#include <string.h>

#include "Refl.h"

struct Base {
  virtual int value() const { return 0; }
};

struct Derived: public Base {
  int value() const override { return 1; }
};

constexpr Base ctor() {
  return Base{};
}

constexpr Derived ctor_D() {
  return Derived{};
}

TEST(ReflTests, Basics_new) {
  Utility::Reflection::registering(
    Stringify(Derived),
    []() -> Utility::Var {
      return Utility::Var{new Derived()};
    });

  std::optional<Utility::Var> vMaybe =
    Utility::Reflection::construct("Derived");

  Base* b = vMaybe.value().convert<Base>();
  EXPECT_TRUE(b->value() == 1);
}
