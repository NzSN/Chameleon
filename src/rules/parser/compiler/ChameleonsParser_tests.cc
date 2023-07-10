#include <sstream>
#include <gtest/gtest.h>
#include "ChameleonsLexer.h"
#include "ChameleonsParser.h"

std::string GetParseTree(std::string prog, bool pretty = false) {
    std::stringstream ss(prog);
    antlr4::ANTLRInputStream input(ss);
    ChameleonsLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ChameleonsParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.migrate();
    return tree->toStringTree(&parser, pretty);
}


TEST(ChameleonsTest, Basic) {
    std::string treeStr = GetParseTree("R: { Origin } => { Migrated }");
    std::string expected =
        "(migrate "
        "(migrateRules "
        "(migrateRule "
        "R : { (originCode  Origin ) } => { (targetCode  Migrated ) })))";
    EXPECT_EQ(treeStr, expected);
}

TEST(ChameleonsTest, WithSpaceCodes) {
    std::string treeStr = GetParseTree(
        "R: {"

        "setTimeout(%A, %B);"
        "console.log(%A, %B); "

        " } => { "

        "SetTimeout_Coro(%A, %B)"

        " }");
    std::string expected =
        "(migrate "
        "(migrateRules "
        "(migrateRule "
        "R : { (originCode setTimeout(%A, %B);console.log(%A, %B);  ) } "
        "=> { (targetCode  SetTimeout_Coro(%A, %B) ) })))";

    EXPECT_EQ(treeStr, expected);
}
