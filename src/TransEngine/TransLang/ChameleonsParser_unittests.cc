#include <sstream>
#include <gtest/gtest.h>
#include "utility.h"
#include "ChameleonsLexer.h"
#include "ChameleonsParser.h"

struct ChameleonsTest: public ::testing::Test {
  using Entry = ChameleonsParser::ProgContext* (ChameleonsParser::*)();
  std::string GetParseTree(std::string prog, bool pretty = false) {
    Entry entry;
    entry = &ChameleonsParser::prog;

    env = Utility::Antlr4_GenParseTree<
      ChameleonsLexer, ChameleonsParser>(prog, entry);

    return env->tree->toStringTree(&env->parser, pretty);
  }

  bool ParseTreeMatching(std::string prog, std::string parseTree) {
    std::cout << GetParseTree(prog);
    return GetParseTree(prog) == parseTree;
  }

  Utility::Antlr4ParseEnvUniquePtr<
    ChameleonsLexer, ChameleonsParser, Entry> env;

};


TEST_F(ChameleonsTest, Basic) {
  EXPECT_TRUE(ParseTreeMatching(
                // Program
                "TARGET: Cpp\n"
                "RULES:\n"
                "R: {| Origin |} => {| Progd |}",
                // ParseTree
                "(prog "
                "(targetSection TARGET: Cpp) "
                "(ruleSection RULES: "
                "(rewriteRules "
                "(rewriteRule R : {| (sourcePattern  Origin ) |} => {| (targetPattern  Progd ) |}))))"
                ));

  EXPECT_TRUE(ParseTreeMatching(
                // Program
                "TARGET: Cpp\n"
                "RULES:\n"
                "R: {| Origin\\| |} => {| Progd\\| |}",
                // ParseTree
                "(prog "
                "(targetSection TARGET: Cpp) "
                "(ruleSection RULES: "
                "(rewriteRules "
                "(rewriteRule "
                "R : {| (sourcePattern  Origin\\| ) |} => {| (targetPattern  Progd\\| ) |}))))"
                ));

}

TEST_F(ChameleonsTest, WithSpaceCodes) {
  EXPECT_TRUE(ParseTreeMatching(
                // Program
                "TARGET: Cpp\n"
                "RULES:\n"
                "R: {|"

                "F();"
                "setTimeout(A, B);"
                "console.log(A, B); "

                " |} => {| "

                "SetTimeout_Coro(A, B)"

                " |}",
                // Expected ParseTree
                "(prog "
                "(targetSection TARGET: Cpp) "
                "(ruleSection RULES: "
                "(rewriteRules "
                "(rewriteRule "
                "R : {| (sourcePattern F();setTimeout(A, B);console.log(A, B);  ) |} "
                "=> {| (targetPattern  SetTimeout_Coro(A, B) ) |}))))"
                ));
}

TEST_F(ChameleonsTest, EscapedBrace) {
  EXPECT_TRUE(
    ParseTreeMatching(
      // Program
      "TARGET: Cpp\n"
      "RULES:\n"
      "R: {| \\{ SENTENCE \\} |} => {| \\{ Progd SENTENCE \\} |}",
      // Expected ParseTree
      "(prog "
      "(targetSection TARGET: Cpp) "
      "(ruleSection RULES: "
      "(rewriteRules "
      "(rewriteRule R : "
      "{| (sourcePattern  \\{ SENTENCE \\} ) |} => {| "
      "(targetPattern  \\{ Progd SENTENCE \\} ) |}))))"
      ));
}

TEST_F(ChameleonsTest, WhereCondition) {
  // Single condition expression
  EXPECT_TRUE(
    ParseTreeMatching(
      "TARGET: Cpp\n"
      "RULES:\n"
      "R: {| T = 0 |} => {| T = 1 |} where T = T;",
      // Expected
      "(prog "
      "(targetSection TARGET: Cpp) "
      "(ruleSection RULES: "
      "(rewriteRules "
      "(rewriteRule "
      "R : {| (sourcePattern  T = 0 ) |} => {| (targetPattern  T = 1 ) |} "
      "where (whereExprs (condExprs (condExpr (condExpr (term T)) = (condExpr (term T))) ;))))))"
      ));
  EXPECT_TRUE(
    ParseTreeMatching(
      "TARGET: Cpp\n"
      "RULES:\n"
      "R: {| T = 0 |} => {| T = 1 |} "
      " where T = \"ABC\" AND T = \"CAB\" OR T = \"AAA\";",
      // Expected
      "(prog (targetSection TARGET: Cpp) "
      "(ruleSection RULES: "
      "(rewriteRules "
      "(rewriteRule R : {| (sourcePattern  T = 0 ) |} => {| (targetPattern  T = 1 ) |} "
      "where "
      "(whereExprs (condExprs "
      "(condExpr (condExpr (condExpr (condExpr (term T)) = (condExpr \"ABC\")) AND "
      "(condExpr (condExpr (term T)) = (condExpr \"CAB\"))) OR "
      "(condExpr (condExpr (term T)) = (condExpr \"AAA\"))) ;))))))"
      ));

  //Multiple condition expression
  EXPECT_TRUE(
    ParseTreeMatching(
      "TARGET: Cpp\n"
      "RULES:\n"
      "R: {| T = 0 |} => {| T = 1 |} "
      " where T = \"A\" AND T = \"B\" OR T = \"C\";"
      "       T = \"D\";",
      // Expected
      "(prog (targetSection TARGET: Cpp) "
      "(ruleSection RULES: "
      "(rewriteRules (rewriteRule R : {| (sourcePattern  T = 0 ) |} => {| (targetPattern  T = 1 ) |} "
      "where "
      "(whereExprs "
      "(condExprs "
      "(condExpr (condExpr (condExpr (condExpr (term T)) = (condExpr \"A\")) AND (condExpr (condExpr (term T)) = (condExpr \"B\"))) OR (condExpr (condExpr (term T)) = (condExpr \"C\"))) ;) "
      "(whereExprs "
      "(condExprs "
      "(condExpr (condExpr (term T)) = (condExpr \"D\")) ;)))))))"
      ));
}


TEST_F(ChameleonsTest, WhereCondition_CallExpr) {
  EXPECT_TRUE(
    ParseTreeMatching(
      "TARGET: LANG \n"
      "RULES: \n"
      "R: {| T + 0 |} => {| T |}"
      // Notes the side effects apply to T by operator
      // := only appear after build strategy is applied.
      " where T := RD(T);",

      "(prog "
      "(targetSection TARGET: LANG) "
      "(ruleSection RULES: "
      "(rewriteRules "
      "(rewriteRule R : {| (sourcePattern  T + 0 ) |} => {| (targetPattern  T ) |} "
      "where (whereExprs (condExprs "
      "(condExpr (assignExpr T := "
      "(condExpr (callExpr RD ( (arguments T) ))))) ;))))))"
      ));
}
