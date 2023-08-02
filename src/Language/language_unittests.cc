#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include "utility.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Language {

struct LangTests: public ::testing::Test {
  using Entry = TestLangParser::ProgContext* (TestLangParser::*)();

  void SetUp() final {

  }
};

} // Language
