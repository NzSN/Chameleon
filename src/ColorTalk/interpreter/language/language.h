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

namespace Rules::Interpreter::Language {

template<typename L, typename M>
concept Language = requires(L t, std::istream& is,
                            std::string str,
                            GenericParseTree<M>* tree) {
  { t.parseTreeFromStream(is) } -> std::same_as<GenericParseTree<M>*>;
  { t.parseTreeFromString(str) } -> std::same_as<GenericParseTree<M>*>;
  { t.convertParseTreeToStr(tree) } -> std::same_as<std::string>;
};

template<GPTMeta M, Language<M> L>
struct MigrateInput {
  const std::istream& is;
  const L& language;
  GenericParseTree<M>* tree_need_migrated;
};

///////////////////////////////////////////////////////////////////////////////
//                                MigrateRule                                //
///////////////////////////////////////////////////////////////////////////////
template<GPTMeta M, Language<M> L>
class RewriteRule {
public:

  enum ERROR_CODE {
    OK,
    ERROR
  };

  RewriteRule(std::string ident, OriginCode ocode, TargetCode tcode):
    identifier_(ident), origin_code_(ocode), target_code_(tcode) {}

  Generator::Generator operator()(MigrateInput<M, L> input) const;

private:
  const std::string identifier_;

  OriginCode origin_code_;
  OriginCode target_code_;

  // ParseTree used to matching the codes that you want to migrate
  std::unique_ptr<GenericParseTree<M>> origin_tree_;
};

template<GPTMeta M, Language<M> T>
struct RewriteRules {
  std::vector<RewriteRule<M, T>> rules;
  RewriteRules(std::initializer_list<RewriteRule<M, T>> rule_list):
    rules{rule_list} {}

  typename std::vector<RewriteRule<M, T>>::const_iterator
  begin() const { return std::begin(rules); }

  typename std::vector<RewriteRule<M, T>>::const_iterator
  end() const { return std::end(rules); }

  std::list<Generator::Generator> operator()(MigrateInput<M, T> input) const {
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
template<GPTMeta M, Language<M> L>
struct Prog {
  Prog(std::initializer_list<RewriteRule<M, L>> rule_list):
    rewrite_rules{rule_list} {}

  RewriteRules<M, L> rewrite_rules;

  // Evaluation of a 'Migrate' Entity is to perform actions to
  // migrating codes from 'istream' to 'ostream' with Rules within
  // the 'Migrate' Entity.
  void operator()(MigrateInput<M, L> input, std::ostream& os) const {
    std::list<Generator::Generator> gens = rewrite_rules(input);

    // Do migrating
  }
};

} // Rules::Interpreter::Language

#endif /* LANGUAGE_H */
