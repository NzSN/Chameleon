#include "language.h"
#include "generator.h"
#include <optional>
#include <plog/Log.h>

namespace Rules {
namespace Interpreter {
namespace Language {

using std::string;
template<GPTMeta T>
using ParseTree = GenericParseTree<T>;
using Generator = Generator::Generator;

namespace {

template<GPTMeta T>
bool applyRule(ParseTree<T>* mtree, /* Migrate Tree */
               ParseTree<T>* scheme, /* Origin scheme */
               Generator& gen) {
  // Scheme maching


  // Failed to migrate
  return false;
}

}

template<GPTMeta M, Language<M> T>
Generator RewriteRule<M, T>::operator()(
  MigrateInput<M, T> input) const {

  Generator gen{target_code_};

  // Build ParseTree for origin pattern
  origin_tree_ = std::make_unique<GenericParseTree<M>>(
    input.language.parseTreeFromString(origin_code_.codebytes()));

  // Iterate over the parse tree from input to find pattern
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
