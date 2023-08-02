#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <plog/Log.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/TxtFormatter.h>

#include <algorithm>

#include "utility.h"
#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"
#include "language_inl.h"
#include "antlr4-runtime.h"

namespace Language {

struct TestWithTestLang: public ::testing::Test {
  using Entry = TestLangParser::ProgContext* (TestLangParser::*)();
  using APT = antlr4::tree::ParseTree;
  using ANTLREnv = Utility::Antlr4ParseEnv<TestLangLexer, TestLangParser, Entry>;

  struct TestLangWrapper {
    TestLangWrapper(std::string sentences) {
      Entry entry = &TestLangParser::prog;
      env = std::make_unique<ANTLREnv>(sentences, entry);
    }

    APT* parse(std::string sentences) {
      return env->tree;
    }

    std::unique_ptr<ANTLREnv> env;
  };

  void SetUp() final {
    plog::init<plog::TxtFormatterUtcTime>
      (plog::debug, plog::streamStdOut);
  }

  using ANTLRLang = Language<APT, TestLangWrapper>;
  ANTLRLang getLang(std::string sentences) {
    return ANTLRLang(sentences);
  }
};

RC_GTEST_FIXTURE_PROP(TestWithTestLang, Basics, ()) {
  ANTLRLang lang = getLang("1+1\n");
  RC_ASSERT(lang.tree() != nullptr);
}

} // Language
