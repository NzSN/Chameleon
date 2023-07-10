#include <sstream>
#include <gtest/gtest.h>
#include "ChameleonsLexer.h"
#include "ChameleonsParser.h"

std::string GetParseTree(std::string prog) {
    std::stringstream ss("R:{ Origin }=>{ Migrated }");
    antlr4::ANTLRInputStream input(ss);
    ChameleonsLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ChameleonsParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.migrate();
    return tree->toStringTree(&parser);
}

struct ChameleonsTest: public ::testing::Test {
    void SetUp() override {}

    void TearDown() override {}
};


TEST_F(ChameleonsTest, Basic) {
    std::string treeStr = GetParseTree("R: { Origin } => { Target }");
    std::string expected =
        "(migrate "
        "(migrateRules "
        "(migrateRule "
        "R : { (originCode  Origin ) } => { (targetCode  Migrated ) })))";
    EXPECT_TRUE(treeStr == expected);
}
