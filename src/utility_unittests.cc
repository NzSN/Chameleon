#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <tuple>
#include "utility.h"

namespace Utility {

struct ZipTest: public ::testing::Test {
  std::vector<int> rdValVector(int size) {
    std::vector<int> v;

    for (int i = 0; i < size; ++i) {
      v.push_back(*rc::gen::inRange(0, 100));
    }

    return v;
  }

  std::vector<int> l{}, r{};
};

// Zipping testing
RC_GTEST_FIXTURE_PROP(ZipTest, EqualSize, ()) {
  const int size = *rc::gen::inRange(0, 10);

  // Create Vectors
  l = rdValVector(size);
  r = rdValVector(size);

  auto zipped = zip_vector<int>(l, r);

  // Check Property:
  // size(l) == size(r) == size(zipped)
  // l[n] * r[n] == fst(zipped[n]) * snd(zipped[n])
  RC_ASSERT(l.size() == r.size() && r.size() == zipped.size());
  for (int index = 0; index < size; ++index) {
    RC_ASSERT(l[index] * r[index] ==
              std::get<0>(zipped[index]) * std::get<1>(zipped[index]));
  }
}

RC_GTEST_FIXTURE_PROP(ZipTest, ArbitarySize, ()) {
  const int size_l = *rc::gen::inRange(0, 100);
  const int size_r = *rc::gen::inRange(0, 100);

  l = rdValVector(size_l);
  r = rdValVector(size_r);

  auto zipped = zip_vector<int>(l, r);

  if (size_l == size_r) {
    RC_ASSERT(zipped.size() == size_l);
  } else {
    RC_ASSERT(zipped.size() == 0);
  }
}

} // Utility
