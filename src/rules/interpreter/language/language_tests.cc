#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <utility>

#include "language.hh"
#include "testLanguage/TestLangLexer.h"
#include "testLanguage/TestLangParser.h"


using std::string;
using std::stringstream;

namespace Rule {
namespace Interpreter {
namespace Language {

struct LanguageForTesting {
    LanguageForTesting() {}

    antlr4::tree::ParseTree* GetParseTree(std::istream& is, bool pretty = false) {
        antlr4::ANTLRInputStream input(is);
        TestLangLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        TestLangParser parser(&tokens);

        return parser.prog();
    }

    antlr4::tree::ParseTree* parseTreeFromStream(std::istream& is) {
        return GetParseTree(is);
    }
    antlr4::tree::ParseTree* parseTreeFromString(std::string codestr) {
        std::stringstream ss {codestr};
        return GetParseTree(ss);
    }
};

struct LanguageTest: public ::testing::Test {

    std::string inputProgram {
        "1 + 1 * 30\n"
        "1 + 3\n"
        "2 * 3 + 2\n"
    };

    MigrateInput<LanguageForTesting> input = {
        stringstream{inputProgram}, LanguageForTesting{}};
};

TEST_F(LanguageTest, ReplacePlusByMulti) {

}


} // Rule
} // Interpreter
} // Language
