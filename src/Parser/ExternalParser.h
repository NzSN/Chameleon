#include <string>
#include <memory>
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

    std::string expression;
    *s >> expression;

    static std::unique_ptr<
      Utility::Antlr4ParseEnv<
        TestLangLexer, TestLangParser, Entry>> env;

    if (env.get() != nullptr) {
      env.release();
    }

    env = Utility::Antlr4_GenParseTree<
      TestLangLexer, TestLangParser>(
        expression, entry);

    tree = env->tree;

    return env->tree;
  }

  static antlr4::tree::ParseTree* tree;
};

} // Parser
