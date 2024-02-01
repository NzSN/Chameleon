#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <utility>
#include "utility.h"
#include "Environment.h"
#include "Base/generic_parsetree.h"

namespace TransEngine {
namespace Rewrite {

struct BindingsTests: public ::testing::Test {
  void SetUp() override {}
};


void f(int a ) { std:: cout << a << std::endl; }

TEST_F(BindingsTests, Basics) {
  Bindings<int> binds;

  // Add bindins
  auto t = Base::ParseTree<int>(1);
  Term<int> term{t};
  binds.bind("id1", term);

  RC_ASSERT(binds.isBinded("id1"));
  RC_ASSERT(term == binds["id1"]);

  binds.unbind("id1");
  RC_ASSERT_FALSE(binds.isBinded("id1"));
}

TEST(EnvironmentTests, MatchTermsSorted) {
  Environment<int> env;

  int a = 1, b = 2, c = 3;
  Base::ParseTree<int> one{a};
  Base::ParseTree<int> two{b};
  Base::ParseTree<int> three{c};
  env.addMatchTerms(Environment<int>::MatchTerm{
      &three, Bindings<int>()});
  env.addMatchTerms(Environment<int>::MatchTerm{
      &two, Bindings<int>()});
  env.addMatchTerms(Environment<int>::MatchTerm{
      &one, Bindings<int>()});

  // Ascending order
  {
    env.sortMatchTerms<true>([&](const Environment<int>::MatchTerm& lhs,
                              const Environment<int>::MatchTerm& rhs) -> bool{
      auto lTree = env.getTree(lhs);
      auto rTree = env.getTree(rhs);

      return lTree->getMeta() < rTree->getMeta();
    });

    auto* currentTerm = &env.matchTerms().front();
    for (auto& term: env.matchTerms()) {
      ASSERT_TRUE(env.getTree(*currentTerm)->getMeta() <=
                  env.getTree(term)->getMeta());
      currentTerm = &term;
    }
  }

  // Dscending order
  {
    env.sortMatchTerms<false>([&](const Environment<int>::MatchTerm& lhs,
                              const Environment<int>::MatchTerm& rhs) -> bool{
      auto lTree = env.getTree(lhs);
      auto rTree = env.getTree(rhs);

      return lTree->getMeta() < rTree->getMeta();
    });

    auto* currentTerm = &env.matchTerms().front();
    for (auto& term: env.matchTerms()) {
      ASSERT_TRUE(env.getTree(*currentTerm)->getMeta() >=
                  env.getTree(term)->getMeta());
      currentTerm = &term;
    }
  }

}

} // Rewrite
} // TransEngine
