#include "language.h"
#include "generator.h"
#include <optional>
#include <plog/Log.h>

namespace Rule {
namespace Interpreter {
namespace Language {

using std::string;
using ParseTree = antlr4::tree::ParseTree;
using Generator = Generator::Generator;

namespace {

bool applyRule(ParseTree* mtree, /* Migrate Tree */
               ParseTree* scheme, /* Origin scheme */
               Generator& gen) {
  // Scheme maching

  // Failed to migrate
  return false;
}

}

template<Language T>
Generator MigrateRule<T>::operator()(
  MigrateInput<T> input) const {

  Generator gen{target_code_};

  // Build ParseTree for origin codes
  origin_tree_ = std::make_unique<antlr4::tree::ParseTree>(
    input.language.parseTreeFromString(origin_code_.codebytes()));

  // Iterate over the parse tree from input to find scheme
  // need to migrated.
  bool success = applyRule(
    input.tree_need_migrated, origin_tree_, gen);
  if (!success) {
    PLOG_FATAL << "There are some errors occurs during migrating codes.\n"

               << "Code ParseTree:\n"
               << input.language.convertParseTreeToStr(
                 input.tree_need_migrated) << "\n"

               <<  "Match Tree:\n"
               << input.language.convertParseTreeToStr(
                 origin_tree_) << "\n";
    return ERROR;
  }

  return gen;
}

} // Language
} // Interpreter
} // Rule
