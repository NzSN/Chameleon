#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "Rule.h"
#include "Program.h"

#include <optional>

namespace Chameleon::api {

// TODO: Enable ability to define Chameleon Function
//       in transformer so Call Expression can work.
template<Base::isLangType lang>
class Transformer {
public:
  Transformer(std::initializer_list<Rule<lang>> rules):
    prog{rules} {

    rules_.insert(rules_.end(), rules.begin(), rules.end());
  }

  Transformer(const Transformer& seq) {
    rules_ = seq.rules_;
  }

  Transformer operator+(const Transformer& other) {
    Transformer ret;

    for (auto seq: {this, &const_cast<Transformer&>(other)}) {
      ret.rules_.insert(ret.rules_.end(),
                        seq->rules_.begin(),
                        seq->rules_.end());
    }

    return ret;
  }

  Transformer& operator=(const Transformer& other) {
    rules_ = other.rules_;
  }

  Transformer& operator=(Transformer&& other) noexcept {
    rules_ = std::move(other.rules_);
  }

  bool operator==(const Transformer& other) const {
    return rules_ == other.rules_;
  }

  size_t ruleSize() const {
    return rules_.size();
  }

  std::optional<std::string> operator()(std::string input) {
    std::istringstream s{input};

    using TargetTree = Base::ParseTree<
      typename Base::LangArg<lang>::Adapter>;

    auto tree = Parser
      ::ParserSelect<lang>
      ::parser
      ::template parse<TargetTree>(&s);

    #if ENABLE_GC
    Base::GC::GC gc{};
    #endif

    auto transedTree = prog(tree);
    return transedTree->getText();
  }

private:
  Transformer() {}

  std::vector<Rule<lang>> rules_;
  Program<lang> prog;
};


} // Chameleon::api

#endif /* TRANSFORMER_H */
