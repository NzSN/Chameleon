#include <gtest/gtest.h>

#include <typeinfo>

#include "utility.h"
#include "WhereClauseExprParsing-inl.h"

#include "Base/generic_parsetree_antlr4.h"

#include "../ChameleonsLexer.h"
#include "../ChameleonsParser.h"

namespace TransEngine::Compiler::WhereClause {

struct WhereClauseTest: public ::testing::Test {
  using Entry =
    ChameleonsParser::ProgContext* (ChameleonsParser::*)();

  void SetUp() override {
    Entry entry = &ChameleonsParser::prog;

    env = Utility::Antlr4_GenParseTree<ChameleonsLexer, ChameleonsParser>(
      "TARGET: TestLang \n"
      "RULES: \n"
      "R: {| a + 0 |} => {| a |}"
      " where a := a;",
      entry);
  }

  std::unique_ptr<
    Utility::Antlr4ParseEnv<
      ChameleonsLexer,
      ChameleonsParser,
      ChameleonsParser::ProgContext* (ChameleonsParser::*)()>> env;
};

TEST_F(WhereClauseTest, introduce) {
  antlr4::tree::ParseTree* tree = env->tree;

  std::vector<antlr4::tree::ParseTree*> result =
    Concepts::NAryTree::search<antlr4::tree::ParseTree>(
      *tree,
      [](antlr4::tree::ParseTree& t) -> bool {
        return typeid(t) ==
          typeid(ChameleonsParser::CondExprContext);
      });

  EXPECT_TRUE(result.size() == 2);

  std::unique_ptr<Expression::Expr> expr =
    WhereClause::toExpr(
      dynamic_cast<ChameleonsParser::CondExprContext*>(result[0]));
  EXPECT_TRUE(expr != nullptr);
}


} // TransEngine::Compiler::WhereClause
