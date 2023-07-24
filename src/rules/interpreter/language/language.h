#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <initializer_list>
#include <memory>

#include <string>
#include <vector>
#include <list>
#include <istream>
#include <ostream>
#include <concepts>
#include <utility>

#include "generic_parsetree.h"
#include "code_str.h"
#include "generator.h"

namespace Rule{
namespace Interpreter {
namespace Language {

template<typename T>
concept Language = requires(T t, std::istream& is,
                            std::string str,
                            GenericParseTree* tree) {
  { t.parseTreeFromStream(is) } -> std::same_as<GenericParseTree*>;
  { t.parseTreeFromString(str) } -> std::same_as<GenericParseTree*>;
  { t.convertParseTreeToStr(tree) } -> std::same_as<std::string>;
};

template<Language T>
struct MigrateInput {
  const std::istream& is;
  const T& language;
  GenericParseTree* tree_need_migrated;
};

///////////////////////////////////////////////////////////////////////////////
//                                MigrateRule                                //
///////////////////////////////////////////////////////////////////////////////
template<Language T>
class MigrateRule {
public:

  enum ERROR_CODE {
    OK,
    ERROR
  };

  MigrateRule(std::string ident, OriginCode ocode, TargetCode tcode):
    identifier_(ident), origin_code_(ocode), target_code_(tcode) {}

  std::unique_ptr<Generator::Generator> operator()(MigrateInput<T> input) const;

private:
  const std::string identifier_;

  OriginCode origin_code_;
  OriginCode target_code_;

  // ParseTree used to matching the codes that you want to migrate
  std::unique_ptr<GenericParseTree> origin_tree_;
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

  std::list<Generator::Generator> operator()(MigrateInput<T> input) const {
    std::list<Generator::Generator> gens;

    for (auto& rule: rules) {
      gens.push_back(std::move(rule(input)));
    }

    return gens;
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
    std::list<Generator::Generator> gens = migrateRules(input);

    // Do migrating
  }
};

} // Rule
} // Interpreter
} // Language

#endif /* LANGUAGE_H */
