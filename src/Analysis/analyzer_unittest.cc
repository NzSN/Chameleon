#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

struct AnalyzerTests: public ::testing::Test {
  void SetUp() final {

  }
};

RC_GTEST_FIXTURE_PROP(AnalyzerTests, Basics, ()) {

}
