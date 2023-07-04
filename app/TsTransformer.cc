#include <iostream>
#include <fstream>
#include "parsers/ts/TypeScriptLexer.h"
#include "parsers/ts/TypeScriptParser.h"
#include "parsers/ts/TypeScriptParserListener.h"


int main(int argc, char *argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);

    antlr4::ANTLRInputStream input(stream);
    TypeScriptLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    TypeScriptParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.program();

    std::cout << tree->toStringTree(&parser) << std::endl;

    return 0;
}
