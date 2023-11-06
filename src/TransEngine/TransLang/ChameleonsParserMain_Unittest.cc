#include <gtest/gtest.h>
#include <sstream>

#include "ChameleonsParserMain-inl.h"
#include "Base/generic_parsetree_antlr4.h"

#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

namespace TransEngine {
namespace Compiler {

using Meta = Base::Antlr4Node;
using GPTAntlr4 = Base::GenericParseTree<Meta>;

TEST(ChameleonsParserMainTest, Spec) {
  Compiler<Meta> compiler;

  std::istringstream target_codes{"1 + 2 + 3"};
  GPTAntlr4 t =
    Parser
    ::ParserSelect<GPTAntlr4::TESTLANG>
    ::parser
    ::parse<GPTAntlr4>(&target_codes);

  std::istringstream rule_config{
    "TARGET: TestLang\n"
    "RULES:\n"
    "Commutative: {| a + b + c |} => {| c + b + a |}"
  };

  // What we expect is program consist of
  // strategies.
  Program<Base::Antlr4Node> program =
    compiler.compile(rule_config);

  // Suppose there exists a parse tree t
  // and analyze data i.
  //
  // The calling of operator() of program will
  // do transformation for t.
  GPTAntlr4 u = program(t);

  EXPECT_TRUE(u.getText() == "3 + 2 + 1");
}

} // Compiler
} // TransEngine
