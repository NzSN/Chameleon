#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <memory>

#include "utility.h"
#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Parser {

struct ParserTests: ::testing::Test {
  using Entry = TestLangParser::ProgContext* (TestLangParser::*)();

  void SetUp() final {
    Entry entry;
    entry = &TestLangParser::prog;

    env = Utility::Antlr4_GenParseTree<
      TestLangLexer, TestLangParser>("1+1", entry);
  }

  std::unique_ptr<
    Utility::Antlr4ParseEnv<
      TestLangLexer, TestLangParser, Entry>> env;
};

RC_GTEST_FIXTURE_PROP(ParserTests, Basics, ()) {
  RC_ASSERT_FALSE(env->tree == nullptr);
}

} // Parser
