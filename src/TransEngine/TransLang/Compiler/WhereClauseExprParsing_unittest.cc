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
      "R: {| a+0 |} => {| a |}"
      "where a = 0;",
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
        std::cout << typeid(t).name() << std::endl;
        if (typeid(t) ==
            typeid(ChameleonsParser::CondExprContext)) {
          return true;
        } else {
          return false;
        }
    });

  EXPECT_TRUE(result.size() == 3);

  std::unique_ptr<Expression::Expr<Base::Antlr4Node>> expr =
    WhereClause::toExpr<Base::Antlr4Node>(
      dynamic_cast<ChameleonsParser::CondExprContext*>(result[0]));

  (*expr)(nullptr);
}


} // TransEngine::Compiler::WhereClause
