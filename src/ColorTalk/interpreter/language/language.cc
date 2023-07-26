#include "language.h"
#include "generator.h"
#include <optional>
#include <plog/Log.h>

namespace Rules {
namespace Interpreter {
namespace Language {

using std::string;
template<typename Backend>
using ParseTree = GenericParseTree<Backend>;
using Generator = Generator::Generator;

namespace {

template<typename Backend>
bool applyRule(ParseTree<Backend>* mtree, /* Migrate Tree */
               ParseTree<Backend>* scheme, /* Origin scheme */
               Generator& gen) {
  // Scheme maching

  // Failed to migrate
  return false;
}

}

template<typename Backend, Language<Backend> T>
Generator RewriteRule<Backend, T>::operator()(
  MigrateInput<Backend, T> input) const {

  Generator gen{target_code_};

  // Build ParseTree for origin codes
  origin_tree_ = std::make_unique<GenericParseTree<Backend>>(
    input.language.parseTreeFromString(origin_code_.codebytes()));

  // Iterate over the parse tree from input to find scheme
  // need to migrated.
  bool success = applyRule(
    input.tree_need_migrated, origin_tree_, gen);
  if (!success) {
    PLOG_FATAL << "There are some errors occurs during migrating source codes.\n"
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
} // Rules
