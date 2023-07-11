#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <initializer_list>
#include <memory>

#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <concepts>
#include <utility>

#include "antlr4-runtime.h"
#include "code_str.h"
#include "generator.h"

using std::string;

namespace Rule {
namespace Interpreter {
namespace Language {


template<typename T>
concept Language = requires(T t, std::istream& is,
                            std::string str,
                            antlr4::tree::ParseTree* tree) {
  { t.parseTreeFromStream(is) } -> std::same_as<antlr4::tree::ParseTree*>;
  { t.parseTreeFromString(str) } -> std::same_as<antlr4::tree::ParseTree*>;
  { t.convertParseTreeToString(tree) } -> std::same_as<std::string>;
};

template<Language T>
struct MigrateInput {
  std::istream& is;
  T& language;
  antlr4::tree::ParseTree* tree_need_migrated;
};

///////////////////////////////////////////////////////////////////////////////
//                                MigrateRule                                //
///////////////////////////////////////////////////////////////////////////////
template<Language T>
class MigrateRule {
public:
  MigrateRule(std::string ident, OriginCode ocode, TargetCode tcode):
    identifier_(ident), origin_code_(ocode), target_code_(tcode) {

    target_generator_ = std::make_unique<Generator::Generator>(target_code_);
  }

  void operator()(MigrateInput<T> input, std::ostream& os) const;

private:
  const std::string identifier_;

  OriginCode origin_code_;
  OriginCode target_code_;

  // ParseTree used to matching the codes that you want to migrate
  std::unique_ptr<antlr4::tree::ParseTree> origin_tree_;
  std::unique_ptr<Generator::Generator> target_generator_;
};

template<Language T>
struct MigrateRules {
  std::vector<MigrateRule<T>> rules;
  MigrateRules(std::initializer_list<MigrateRule<T>> rule_list):
    rules{rule_list} {}

  typename std::vector<MigrateRule<T>>::const_iterator
  begin() const { return std::begin(rules); }

  typename std::vector<MigrateRule<T>>::const_iterator
  end() const { return std::end(rules); }

  void operator()(MigrateInput<T> input, std::ostream& os) const {
    for (auto& rule: rules) {
      rule(input, os);
    }
  }
};

///////////////////////////////////////////////////////////////////////////////
//                                  Migrate                                  //
///////////////////////////////////////////////////////////////////////////////
template<Language T>
struct Migrate {
  Migrate(std::initializer_list<MigrateRule<T>> rule_list):
    migrate_rules{rule_list} {}

  MigrateRules<T> migrate_rules;

  // Evaluation of a 'Migrate' Entity is to perform actions to
  // migrating codes from 'istream' to 'ostream' with Rules within
  // the 'Migrate' Entity.
  void operator()(MigrateInput<T> input, std::ostream& os) const {
    migrateRules(input, os);
  }
};

} // Rule
} // Interpreter
} // Language

#endif /* LANGUAGE_H */
