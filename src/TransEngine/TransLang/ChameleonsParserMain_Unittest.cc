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
  Compiler compiler;

  std::istringstream target_codes{"1 + 2 + 3"};
  GPTAntlr4 t =
    Parser
    ::ParserSelect<GPTAntlr4::TESTLANG>
    ::parser
    ::parse<GPTAntlr4>(&target_codes);

  std::istringstream rule_config{
    "TARGET: TestLang \n"
    "RULES:\n"
    "Commutative: {| a+b+c |} => {| c+b+a |}"
  };

  // What we expect is program consist of
  // strategies.
  std::shared_ptr<Program> program =
    compiler.compile(rule_config);

  // Suppose there exists a parse tree t
  // and analyze data i.
  //
  // The calling of operator() of program will
  // do transformation for t.
  Base::GptGeneric tt = t;
  std::optional<Base::GptGeneric> u = (*program)(tt);

  EXPECT_TRUE(!u.has_value());
  //EXPECT_TRUE(std::get<GPTAntlr4>(u).getText() == "3 + 2 + 1");
}

} // Compiler
} // TransEngine
