#include <sstream>
#include <gtest/gtest.h>
#include "ColorTalk/interpreter/utility.h"
#include "ChameleonsLexer.h"
#include "ChameleonsParser.h"

namespace Utility = Rules::Interpreter::Utility;

struct ChameleonsTest: public ::testing::Test {
  typedef ChameleonsParser::ProgContext* (ChameleonsParser::*Entry)();
  std::string GetParseTree(std::string prog, bool pretty = false) {
    Entry entry;
    entry = &ChameleonsParser::prog;

    env = Utility::Antlr4_GenParseTree<
      ChameleonsLexer, ChameleonsParser>(prog, entry);

    return env->tree->toStringTree(&env->parser, pretty);
  }

  bool ParseTreeMatching(std::string prog, std::string parseTree) {
    return GetParseTree(prog) == parseTree;
  }

  Utility::Antlr4ParseEnvUniquePtr<
    ChameleonsLexer, ChameleonsParser, Entry> env;

};


TEST_F(ChameleonsTest, Basic) {
  EXPECT_TRUE(ParseTreeMatching(
                // Program
                "R: { Origin } => { Progd }",
                // ParseTree
                "(prog "
                "(rewriteRules "
                "(rewriteRule "
                "R : { (sourcePattern  Origin ) } => { (targetPattern  Progd ) })))"
                ));
}

TEST_F(ChameleonsTest, WithSpaceCodes) {
  EXPECT_TRUE(ParseTreeMatching(
                // Program
                "R: {"

                "setTimeout(%A, %B);"
                "console.log(%A, %B); "

                " } => { "

                "SetTimeout_Coro(%A, %B)"

                " }",
                // Expected ParseTree
                "(prog "
                "(rewriteRules "
                "(rewriteRule "
                "R : { (sourcePattern setTimeout(%A, %B);console.log(%A, %B);  ) } "
                "=> { (targetPattern  SetTimeout_Coro(%A, %B) ) })))"
                ));
}

TEST_F(ChameleonsTest, EscapedBrace) {
  EXPECT_TRUE(
    ParseTreeMatching(
      // Program
      "R: { \\{ SENTENCE \\} } => { \\{ Progd SENTENCE \\} }",
      // Expected ParseTree
      "(prog (rewriteRules "
      "(rewriteRule R : "
      "{ (sourcePattern  \\{ SENTENCE \\} ) } => { "
      "(targetPattern  \\{ Progd SENTENCE \\} ) })))"
      ));
}
