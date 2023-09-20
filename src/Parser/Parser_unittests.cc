#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <memory>
#include <string>
#include <istream>
#include <sstream>

#include "Parser.h"
#include "Base/generic_parsetree_antlr4.h"
#include "utility.h"
#include "Misc/testLanguage/TestLangLexer.h"
#include "Misc/testLanguage/TestLangParser.h"

namespace Parser {

struct TestLangExt {
  using Entry =
    TestLangParser::ProgContext* (TestLangParser::*)();

  static antlr4::tree::ParseTree*
  parse(std::istream *s) {
    Entry entry = &TestLangParser::prog;

    static std::unique_ptr<
      Utility::Antlr4ParseEnv<
        TestLangLexer, TestLangParser, Entry>> env;

    if (env.get() != nullptr) {
      env.release();
    }

    env = Utility::Antlr4_GenParseTree<
      TestLangLexer, TestLangParser>(
        "1+1", entry);

    return env->tree;
  }
};

RC_GTEST_PROP(ParserTests, Basics, ()) {

  std::istringstream codes{"1+1"};

  auto t = Parser<
    antlr4::tree::ParseTree*,
    TestLangExt,
    Base::Antlr4Node,
    Base::GenericParseTree<Base::Antlr4Node>::TESTLANG>
    ::parse(&codes);
}

} // Parser
