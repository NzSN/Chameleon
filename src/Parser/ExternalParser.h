#ifndef EXTERNALPARSER_H
#define EXTERNALPARSER_H

#include <string>
#include <vector>
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

    std::unique_ptr<
      Utility::Antlr4ParseEnv<
        TestLangLexer, TestLangParser, Entry>> env;

    env = Utility::Antlr4_GenParseTree<
      TestLangLexer, TestLangParser>(
        expression, entry);

    tree = env->tree;
    envs.push_back(std::move(env));

    return tree;
  }

  static antlr4::tree::ParseTree* tree;

  using EnvPtr = std::unique_ptr<
    Utility::Antlr4ParseEnv<TestLangLexer, TestLangParser, Entry>>;
  static std::vector<EnvPtr> envs;
};

struct WGSLLangExt {
};

} // Parser

#endif /* EXTERNALPARSER_H */
