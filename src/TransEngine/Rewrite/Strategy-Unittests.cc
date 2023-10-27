#include <gtest/gtest.h>
#include "Strategy.h"

namespace TransEngine {
namespace Rewrite {

/* A strategy binding an empty tree into
 * environment only. */
template<Base::GPTMeta T>
struct EmptyStrat: public Strategy<T> {
  UNUSED_V operator()(Rule<T>& rule, Environment<T>& env) {

  }
};

TEST(StrategiesTests, Basic) {

}

} // Rewrite
} // TransEngine
