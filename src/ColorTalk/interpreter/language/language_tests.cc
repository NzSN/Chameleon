#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <typeinfo>
#include <utility>

#include "language.h"
#include "testLanguage/TestLangLexer.h"
#include "testLanguage/TestLangParser.h"


using std::string;
using std::stringstream;

namespace Rules {
namespace Interpreter {
namespace Language {

class CodeStrImpl: public CodeStr {
public:
    string toStr() const final {
        return "";
    }

    string withoutEscape() const final {
        return "";
    }
};

struct LanguageForTesting {
  LanguageForTesting() {}

  antlr4::tree::ParseTree* GetParseTree(std::istream& is, bool pretty = false) {
    antlr4::ANTLRInputStream input(is);
    TestLangLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    TestLangParser parser(&tokens);

    // Convert antlr4::tree::ParseTree
    // to GenericParseTree.
    return parser.prog();
  }

  GenericParseTree<std::type_info>* parseTreeFromStream(std::istream& is) {
    return GetParseTree(is);
  }
  GenericParseTree<std::type_info>* parseTreeFromString(std::string codestr) {
    std::stringstream ss {codestr};
    return GetParseTree(ss);
  }
  std::string convertParseTreeToStr(GenericParseTree<std::type_info>* tree) {
    return "";
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

TEST_F(LanguageTest, ReplacePlusByMulti_OneRule) {
    Trans<int, LanguageForTesting> migrate {
        // Rule to replace all '1+1' to '1*1'
        { "Plus2Multi",
          OriginCode {
              { "1 + 1" }
          },
          TargetCode {
              { "1 * 1" }
          }
        }
    };

    stringstream s;
    migrate(input, s);

    std::cout << s.str() << std::endl;
}

TEST_F(LanguageTest, WithCommand) {
    Migrate<LanguageForTesting> migrate {
        { "Plus2Multi",
          OriginCode {
              { "1 + 1" }
          },
          TargetCode {
              {
                "1 * 1\n"
                // @random_number is a command which is executing during
                // migrating
                "1 + @random_number\n"
              }
          }
        }
    };

    stringstream s;
    migrate(input, s);

    std::cout << s.str() << std::endl;

}


} // Rule
} // Interpreter
} // Language
