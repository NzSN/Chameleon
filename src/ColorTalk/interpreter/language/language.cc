#include "language.h"
#include "generator.h"
#include <optional>
#include <plog/Log.h>

namespace Rules {
namespace Interpreter {
namespace Language {

using std::string;
using Generator = Generator::Generator;

namespace {

template<GPTMeta T>
bool doRewrite(std::unique_ptr<GenericParseTree<T>>& mtree, /* Migrate Tree */
               std::unique_ptr<GenericParseTree<T>>& scheme, /* Origin scheme */
               Generator& gen) {
  // Scheme matching

  // Failed to migrate
  return false;
}

}

template<GPTMeta M, Language<M> T>
Generator RewriteRule<M, T>::operator()(
  MigrateInput<M, T> input) const {

  Generator gen{target_code_};

  // Build GenericParseTree for origin pattern
  source_tree_ = std::make_unique<GenericParseTree<M>>(
    input.language.parseTreeFromString(source_code_.codebytes()));

  // Iterate over the parse tree from input to find pattern
  // need to migrated.
  bool success = doRewrite(
    input.tree_need_migrated, source_tree_, gen);
  if (!success) {
    PLOG_FATAL << "There are some errors occurs during migrating source codes.\n"
               << "Code GenericParseTree:\n"
               << input.language.convertGenericParseTreeToStr(
                 input.tree_need_migrated) << "\n"
               <<  "Match Tree:\n"
               << input.language.convertGenericParseTreeToStr(
                 source_tree_) << "\n";
    return ERROR;
  }

  return gen;
}

} // Language
} // Interpreter
} // Rules
