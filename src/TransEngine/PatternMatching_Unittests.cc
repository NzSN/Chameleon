#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Algorithms {

struct PatternMatchingTests: public ::testing::Test {

};

RC_GTEST_FIXTURE_PROP(PatternMatchingTests, Basics, ()) {

}

} // Algorithms
