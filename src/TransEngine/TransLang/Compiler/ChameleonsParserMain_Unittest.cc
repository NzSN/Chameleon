#include <plog/Log.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/TxtFormatter.h>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "ChameleonsParserMain-inl.h"
#include "Base/generic_parsetree_antlr4.h"

#include "Parser/Parser-inl.h"
#include "Parser/ExternalParser.h"

#include "Registered-Functions.h"

namespace TransEngine {
namespace Compiler {

using Meta = Base::Antlr4Node;
using GPTAntlr4 = Base::GenericParseTree<Meta>;

TEST(ChameleonsParserMainTest, Spec) {
  Compiler compiler;

  std::istringstream target_codes{"1 + 2 + 3"};
  Base::GenericParseTree<Adapter> t =
    Parser
    ::ParserSelect<GPTAntlr4::TESTLANG>
    ::parser
    ::parse<GPTAntlr4>(&target_codes);

  std::istringstream rule_config{
    "TARGET: TestLang \n"
    "RULES:\n"
    "Commutative: {| a + b + c |} => {| c + b + a |}"
  };

  // What we expect is program consist of
  // strategies.
  std::unique_ptr<Program> program =
    compiler.compile(rule_config);


  // Suppose there exists a parse tree t
  // and analyze data i.
  //
  // The calling of operator() of program will
  // do transformation for t.
  std::optional<Base::GptGeneric> u = (*program)(t);

  EXPECT_TRUE(u.has_value());
  EXPECT_TRUE(std::get<GPTAntlr4>(u.value()).getText() == "3+2+1");
}

TEST(ChameleonsParserMainTest, WhereClause_Condition) {
  Compiler compiler;

  std::istringstream target_codes{"1 + 2 + 3"};
  Base::GenericParseTree<Adapter> t =
    Parser
    ::ParserSelect<GPTAntlr4::TESTLANG>
    ::parser
    ::parse<GPTAntlr4>(&target_codes);

  std::istringstream rule_config{
    "TARGET: TestLang \n"
    "RULES: \n"
    "Commutative: {| a + b + c |} => {| c + b + a |} "
    " where a := Plus(a);"
  };

  // Initialize infrastructures that
  // compiler is depends.

  // plog
  plog::init<plog::TxtFormatterUtcTime>(
    plog::debug, plog::streamStdOut);

  // Reflections
  registerFunctions(Base::GptSupportLang::TESTLANG);

  // Compiling
  std::unique_ptr<Program> program =
    compiler.compile(rule_config);
  std::optional<Base::GptGeneric> u = (*program)(t);

  // Assert
  EXPECT_TRUE(u.has_value());
  EXPECT_TRUE(std::get<GPTAntlr4>(u.value()).getText()
              == "3+2+2");
}

TEST(ChameleonsParserMainTest, WGSL) {
  Compiler compiler;

  std::istringstream target_codes{
    "fn main() { a = b + c; }" };
  Base::GenericParseTree<Adapter> t =
    Parser
    ::ParserSelect<Base::SUPPORTED_LANGUAGE::WGSL>
    ::parser
    ::parse<GPTAntlr4>(&target_codes);

  std::istringstream rule_config{
    "TARGET: WGSL \n"
    "RULES: \n"
    "Commutative: {| a = __b + __c; |} => {| a = __c + __b; |}"
  };

  // plog
  plog::init<plog::TxtFormatterUtcTime>(
    plog::debug, plog::streamStdOut);

  // Compiling
  std::unique_ptr<Program> program =
    compiler.compile(rule_config);
  std::optional<Base::GptGeneric> u = (*program)(t);

  EXPECT_TRUE(u.has_value());
  EXPECT_TRUE(std::get<GPTAntlr4>(u.value()).getText()
              == "fnmain(){a=c+b;}");
}

TEST(ChameleonsParserMainTest, Main) {
 std::istringstream target_codes{
    "fn main() { a = b + c; }" };

  std::istringstream rule_config{
    "TARGET: WGSL \n"
    "RULES: \n"
    "Commutative: {| a = __b + __c; |} => {| a = __c + __b; |}"
  };

  ChameleonsMain main(&rule_config, &target_codes);

  std::optional<std::string> codes = main();

  EXPECT_TRUE(codes.has_value());
  EXPECT_TRUE(codes.value() == "fnmain(){a=c+b;}");

}

} // Compiler
} // TransEngine
