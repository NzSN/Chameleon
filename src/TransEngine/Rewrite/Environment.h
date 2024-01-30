#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <optional>

#include "Concepts/concepts.h"

#include "Term.h"
#include "Base/generic_parsetree_inl.h"
#include "utility.h"
#include "Analysis/analyzer.h"

namespace TransEngine {
namespace Rewrite {

// INVARIANT:
//  1.For all a,b in TermIdent, if both a and b are binded
//    then a != b. (TermIdent Uniqueness)
template<Base::GPTMeta T>
class Bindings {
public:

  Bindings() = default;

  Bindings(Bindings&& other) {
    bindings_ = std::move(other.bindings_);
  }

  // Identifier of a term in bindings is determined
  // by Transform Rules. For example, there is a rule:
  // {| a + 1 |} => {| a * 1 |}
  //
  // This rule binds terms that match with left side
  // pattern to identifier "a".
  using TermIdent = std::string;

  void bind(const TermIdent& ident, Term<T> term) {
    bindings_.insert_or_assign(ident, term);
  }

  Term<T>& operator[](const TermIdent& ident) {
    if (bindings_.contains(ident)) {
      return std::get<1>(*bindings_.find(ident));
    } else {
      throw std::overflow_error(
        "No term is binding to " + ident + ".");
    }
  }

  bool isBinded(const TermIdent& ident) const {
    return bindings_.contains(ident);
  }

  bool unbind(const TermIdent& ident) {
    if (bindings_.contains(ident)) {
      bindings_.erase(ident);
      return true;
    } else {
      return false;
    }
  }

  size_t size() const {
    return bindings_.size();
  }

  void clear() {
    bindings_.clear();
  }

private:
  std::unordered_map<TermIdent, Term<T>> bindings_;
};

/* Environment is a collection of Variable bindings. */
template<Base::GPTMeta T>
class Environment {
public:
  /* Alias types for Match and its basis */
  using MatchTerm = std::tuple<Base::GenericParseTree<T>*, Bindings<T>>;
  using MatchTerms = std::list<MatchTerm>;

  const Base::GenericParseTree<T>* getTree(const MatchTerm& term) {
    return std::get<0>(term);
  }

  Bindings<T>& getBindings(MatchTerm& term) {
    return std::get<1>(term);
  }
  /* End of MatchTerm(s) definitnion */


  using AnalysisData =
    Analyzer::AnalyzeData<Base::GenericParseTree<T>>;

  Environment():
    targetTerm_{nullptr}, matchTerm_{nullptr},
    analysisData_{nullptr} {

    bindings_ = &bindingsDefault;
  }

  Base::GenericParseTree<T>* targetTerm() {
    return targetTerm_;
  }

  void setTargetTerm(Base::GenericParseTree<T>* t) {
    targetTerm_ = t;
  }

  Base::GenericParseTree<T>* matchTerm() {
    return matchTerm_;
  }

  MatchTerms& matchTerms() {
    return matchTerms_;
  }

  void setMatchTerm(Base::GenericParseTree<T>* t) {
    matchTerm_ = t;
  }

  void addMatchTerms(MatchTerm&& t) {
    matchTerms_.push_back(std::move(t));
  }

  void setMatchTerms(MatchTerms&& t) {
    matchTerms_ = std::move(t);
  }

  void setCurrentTerm(MatchTerm& t) {
    currentTerm_ = &t;
    matchTerm_ = std::get<0>(*currentTerm_);
    bindings_ = &std::get<1>(*currentTerm_);
  }

  using MatchTermCompare =
    std::function<bool(const MatchTerm&, const MatchTerm&)>;

template<bool isAscending = true>
  requires Concepts::isAscending<isAscending>
  void sortMatchTerms(MatchTermCompare compare) {
    matchTerms().sort(compare);
  }

  template<bool isAscending = true>
  requires (!Concepts::isAscending<isAscending>)
  void sortMatchTerms(MatchTermCompare compare) {
    sortMatchTerms<true>([&](const MatchTerm& lhs, const MatchTerm& rhs) -> bool {
      return !compare(lhs, rhs);
    });
  }

  Bindings<T>& bindings() {
    return *bindings_;
  }

  void setAnalysisData(AnalysisData* data) {
    analysisData_ = data;
  }

  const AnalysisData* getAnalysisData() const {
    return analysisData_;
  }

  void holdResource(Utility::HeapResourceHolder& resource) {
    resources_.push_back(resource);
  }

  void holdResource(Utility::HeapResourceHolder&& resource) {
    resources_.push_back(std::move(resource));
  }

  void clearResource() {
    resources_.clear();
  }

private:
  // Target Term is the Term to be transformed.
  Base::GenericParseTree<T>* targetTerm_;

  // The part that match by left side patterns.
  Base::GenericParseTree<T>* matchTerm_;
  Bindings<T>* bindings_;
  // For compatibility, a default bindings is requried
  // to make bindings_ point to valid area of memory.
  Bindings<T>  bindingsDefault;

  MatchTerms matchTerms_;

  MatchTerm* currentTerm_;

  std::vector<Utility::HeapResourceHolder> resources_;
  const AnalysisData* analysisData_;
};


} // Rewrite
} // TransEngine

#endif /* ENVIRONMENT_H */
