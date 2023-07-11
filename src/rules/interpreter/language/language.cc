
#include "language.h"
#include <optional>
#include <plog/Log.h>

namespace Rule {
namespace Interpreter {
namespace Language {

using std::optional, std::string;
using ParseTree = antlr4::tree::ParseTree;
using Generator = Generator::Generator;

namespace {

struct MigratedInfo {
  optional<string> code;
  int source_offset;
  int source_span;
};

optional<string> iterateAndMigrate(ParseTree* tree, ParseTree* tree_to_match,
                           Generator gen) {
  return std::nullopt;
}

}


template<Language T>
void MigrateRule<T>::operator()(MigrateInput<T> input, std::ostream& os) const {
  // Build ParseTree for origin codes
  origin_tree_ = std::make_unique<antlr4::tree::ParseTree>(
    input.language.parseTreeFromString(origin_code_.codebytes()));

  // Iterate over the parse tree from input to find scheme
  // need to migrated.
  MigratedInfo info = iterateAndMigrate(
    input.tree_need_migrated, origin_tree_, target_generator_);
  if (!info.code.has_value()) {
    PLOG_FATAL << "There are some errors occurs during migrating codes."

               << "Code ParseTree:\n"
               << input.language.convertParseTreeToString(
                 input.tree_need_migrated) << "\n"

               <<  "Match Tree:\n"
               << input.language.convertParseTreeToString(
                 origin_tree_) << "\n";
  }

  // Make sure that parts of original codes that before the current match
  // code are all been processed. If not processed then move these codes
  // directly from origin stream to output stream.


  // Push migrated rule to output stream
  os << info.code.value();
}

} // Language
} // Interpreter
} // Rule
