#include <gtest/gtest.h>
#include <optional>
#include <any>
#include <string.h>

#include "Refl.h"

struct Base {
  virtual int value() const { return 0; }
  virtual ~Base() {}
};

struct Derived: public Base {
  ~Derived() {}
  int value() const override { return 1; }
};

Base ctor() {
  return Base{};
}

Derived ctor_D() {
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
  Utility::VarScopeGuard<Derived> guard{vMaybe};

  Base* b = vMaybe.value().convert<Base>();
  EXPECT_TRUE(b->value() == 1);
}
