#include <sstream>
#include <gtest/gtest.h>
#include "ChameleonsLexer.h"
#include "ChameleonsParser.h"


struct ChameleonsTest: public ::testing::Test {
  std::string GetParseTree(std::string prog, bool pretty = false) {
    std::stringstream ss(prog);
    antlr4::ANTLRInputStream input(ss);
    ChameleonsLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ChameleonsParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.migrate();

    return tree->toStringTree(&parser, pretty);
  }

  bool ParseTreeMatching(std::string prog, std::string parseTree) {
    return GetParseTree(prog) == parseTree;
  }

};


TEST_F(ChameleonsTest, Basic) {
  EXPECT_TRUE(
    ParseTreeMatching(
      // Program
      "R: { Origin } => { Migrated }",
      // ParseTree
      "(migrate "
      "(migrateRules "
      "(migrateRule "
      "R : { (originCode  Origin ) } => { (targetCode  Migrated ) })))"
      ));
}

TEST_F(ChameleonsTest, WithSpaceCodes) {
  EXPECT_TRUE(
    ParseTreeMatching(
      // Program
      "R: {"

      "setTimeout(%A, %B);"
      "console.log(%A, %B); "

      " } => { "

      "SetTimeout_Coro(%A, %B)"

      " }",
      // Expected ParseTree
      "(migrate "
      "(migrateRules "
      "(migrateRule "
      "R : { (originCode setTimeout(%A, %B);console.log(%A, %B);  ) } "
      "=> { (targetCode  SetTimeout_Coro(%A, %B) ) })))"
      ));
}

TEST_F(ChameleonsTest, EscapedBrace) {
  EXPECT_TRUE(
    ParseTreeMatching(
      // Program
      "R: { \\{ SENTENCE \\} } => { \\{ Migrated SENTENCE \\} }",
      // Expected ParseTree
      "(migrate (migrateRules "
      "(migrateRule R : "
      "{ (originCode  \\{ SENTENCE \\} ) } => { "
      "(targetCode  \\{ Migrated SENTENCE \\} ) })))"
      ));
}
