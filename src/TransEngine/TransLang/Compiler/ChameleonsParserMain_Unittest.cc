#include <plog/Log.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/TxtFormatter.h>
#include <gtest/gtest.h>
#include <sstream>

#include "Base/gc_defines.h"

#include "ChameleonsParserMain-inl.h"
#include "Base/generic_parsetree_antlr4.h"

#include "Parser/Parser-inl.h"

#include "Registered-Functions.h"

namespace Chameleon {
namespace TransEngine {
namespace Compiler {

using Meta = Base::Antlr4Node;
using GPTAntlr4 = Base::ParseTree<Meta>;

TEST(ChameleonsParserMainTest, Spec) {
  Compiler compiler;

  #if ENABLE_GC
  Base::GC::GC gc{};
  #endif

  std::istringstream target_codes{"1 + 2 + 3"};
  Base::ParseTree<Adapter> t =
    Parser
    ::ParserSelect<GET_LANG_TYPE(TESTLANG)>
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

  #if ENABLE_GC
  Base::GC::GC gc{};
  #endif

  std::istringstream target_codes{"1 + 2 + 3"};
  Base::ParseTree<Adapter> t =
    Parser
    ::ParserSelect<GET_LANG_TYPE(TESTLANG)>
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

  #if ENABLE_GC
  Base::GC::GC gc{};
  #endif

  std::istringstream target_codes{
    "fn main() { a = b + c; }" };
  Base::ParseTree<Adapter> t =
    Parser
    ::ParserSelect<GET_LANG_TYPE(WGSL)>
    ::parser
    ::parse<GPTAntlr4>(&target_codes);

  std::istringstream rule_config{
    "TARGET: WGSL \n"
    "RULES: \n"
    "Commutative: {| a = b + c; |} => {| a = c + b; |}"
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
    "Commutative: {| a = b + c; |} => {| a = c + b; |}"
  };

  ChameleonsMain main(&rule_config, &target_codes);

  std::optional<std::string> codes = main();

  EXPECT_TRUE(codes.has_value());
  EXPECT_TRUE(codes.value() == "fnmain(){a=c+b;}");
}

TEST(ChameleonsParserMainTest, MainWithWhere) {
 std::istringstream target_codes{
    "fn main() { ident = b + c; }" };

  std::istringstream rule_config{
    "TARGET: WGSL \n"
    "RULES: \n"
    "Commutative: {| a = b + c; |} => {| a = c + b; |}"
    " where b := RandomIdent(b);"
  };

  registerFunctions(Base::GptSupportLang::WGSL);

  ChameleonsMain main(&rule_config, &target_codes);

  std::optional<std::string> codes = main();

  EXPECT_TRUE(codes.has_value());

  EXPECT_TRUE(codes.value() != "fnmain(){ident=c+b;}");
}

TEST(ChameleonsParserMainTest, MainMultiMatch) {
 std::istringstream target_codes{
    "fn main() { a = b + c; c = d + e; }" };

  std::istringstream rule_config{
    "TARGET: WGSL \n"
    "RULES: \n"
    "Commutative: {| a = b + c; |} => {| a = c + b; |}"
    " where b := RandomIdent(b); c := RandomIdent(c);"
  };

  registerFunctions(Base::GptSupportLang::WGSL);

  ChameleonsMain main(&rule_config, &target_codes);

  std::optional<std::string> codes = main();

  EXPECT_TRUE(codes.has_value());
  // Don't know how to assert those random result.
}



} // Compiler
} // TransEngine
} // Chameleon
