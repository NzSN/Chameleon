#include <gtest/gtest.h>

#include <sstream>
#include "ExternalParser.h"

namespace Chameleon::Parser {

TEST(ExternalParserUnittests, Basic) {
  ExternalParser<GET_LANG_TYPE(TESTLANG)> extParser;

  extParser.releaseAll();

  std::istringstream s {"1+2+3"};
  auto* tree = extParser.parse(&s);

  EXPECT_TRUE(tree != nullptr);
  EXPECT_TRUE(extParser.numOfResInTracked() == 1);

  extParser.release(reinterpret_cast<uintptr_t>(tree));
  EXPECT_TRUE(extParser.numOfResInTracked() == 0);
}

TEST(ExternalParserUnittests, Empty) {
  ExternalParser<GET_LANG_TYPE(TESTLANG)> extParser;
  extParser.releaseAll();

  extParser.release(0);
  EXPECT_TRUE(extParser.numOfResInTracked() == 0);

  // After that ExternalParser should still works
  std::istringstream s {"1+2+3"};
  auto* tree = extParser.parse(&s);

  EXPECT_TRUE(tree != nullptr);
  EXPECT_TRUE(extParser.numOfResInTracked() == 1);

  extParser.release(reinterpret_cast<uintptr_t>(tree));
  EXPECT_TRUE(extParser.numOfResInTracked() == 0);
}

} // Parser
