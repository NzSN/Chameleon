#include <gtest/gtest.h>
#include <optional>
#include <tuple>
#include "utility.h"

namespace Rules::Interpreter::Utility {
TEST(UtilityTest, zip) {
  std::vector<int> l  {1, 3, 5, 7, 9};
  std::vector<int> r  {2, 4, 6, 8, 10};

  auto zipped = zip_vec(l, r);
  EXPECT_TRUE(zipped != std::nullopt);
  std::vector<std::tuple<int, int>> m = {
    {1,2}, {3,4}, {5,6}, {7,8}, {9,10}
  };
  EXPECT_EQ(m, zipped.value());
}

} // Rules::Interpreter::Utility
