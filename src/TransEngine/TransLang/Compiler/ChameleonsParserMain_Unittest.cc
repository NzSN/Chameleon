#include <gtest/gtest.h>
#include <sstream>
#include <utility>

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

  std::istringstream target_codes{"1+2+3"};
  Base::GptGeneric t =
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
  std::optional<Base::GptGeneric> u = (*program)(t);

  EXPECT_TRUE(u.has_value());
  EXPECT_TRUE(std::get<GPTAntlr4>(u.value()).getText() == "3+2+1");
}

// A Chameleon Function, plus a number by 1
namespace TransExpr = TransEngine::Expression;
struct Plus: public TransExpr::Function {
  std::unique_ptr<TransExpr::Value> operator()(
    TransExpr::Arguments* args) {

    if (args->args.size() != 1) {
      return nullptr;
    }

    // Try to convert the text presentation to integer,
    // no effects if failed to convert.
    if (!TransExpr::Value::isTerm(*args->args[0])) {
      return nullptr;
    }

    TransExpr::Term* term = dynamic_cast<TransExpr::Term*>(
      args->args[0].get());

    std::string numberMaybe = term->term->tree.get().getText();

    int number{};

    try {
      number = std::stoi(numberMaybe);
    } catch (const std::invalid_argument& e) {
      return nullptr;
    } catch (const std::out_of_range& e) {
      return nullptr;
    }
  }
};

TEST(ChameleonsParserMainTest, WhereClause_Condition) {
  Compiler compiler;

  std::istringstream target_codes{"1+2+3"};
  Base::GptGeneric t =
    Parser
    ::ParserSelect<GPTAntlr4::TESTLANG>
    ::parser
    ::parse<GPTAntlr4>(&target_codes);

  std::istringstream rule_config{
    "TARGET: TestLang \n"
    "RULES: \n"
    "Commutative: {| a+b+c |} => {| c+b+a |} "
    " where a := Plus(a);"
  };

  std::shared_ptr<Program> program =
    compiler.compile(rule_config);
  std::optional<Base::GptGeneric> u = (*program)(t);

  EXPECT_TRUE(u.has_value());
  EXPECT_TRUE(std::get<GPTAntlr4>(u.value()).getText()
              == "3+2+2");
}


} // Compiler
} // TransEngine
