#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "n_ary_tree.h"
#include <vector>
#include <tuple>
#include <optional>


namespace Concepts {

struct NAryTreeTests: public ::testing::Test {
  struct TreeNary_T1 {
    int n;
    std::vector<TreeNary_T1> children;
  };
  struct TreeNary_T2 {
    int n;
    std::vector<TreeNary_T2> children;
  };

  TreeNary_T1* l;
  TreeNary_T2* r;

  std::optional<std::tuple<
    const TreeNary_T1&,
    const TreeNary_T2&>>
  genTwinsNAry(const unsigned int n_nodes) {
    if (n_nodes == 0) return std::nullopt;

    TreeNary_T1 l;
    TreeNary_T2 r;

    std::function<void(TreeNary_T1*,TreeNary_T2*,int)>
      genSubTreeWithN = [&](TreeNary_T1* l, TreeNary_T2* r, int nsubs) {
        while (nsubs > 0) {
          // Create directly child
          l->children.push_back({});
          TreeNary_T1& child_l = l->children.back();
          r->children.push_back({});
          TreeNary_T2& child_r = r->children.back();

          int value = *rc::gen::inRange(0, nsubs);
          child_l.n = child_r.n = value;


          nsubs -= 1;
          if (nsubs == 0) { return; }

          // Create a subtree with M nodes,
          // M is in range [0, remain]
          int m = *rc::gen::inRange(0, nsubs);
          genSubTreeWithN(&child_l, &child_r, m);
          nsubs -= m;
        }
    };

    genSubTreeWithN(&l, &r, n_nodes - 1);

    return std::make_tuple(l, r);
  }
};

RC_GTEST_FIXTURE_PROP(NAryTreeTests, Equal, ()) {
  int n = *rc::gen::inRange(1, 100);
  auto trees = genTwinsNAry(n);

  RC_ASSERT(trees.has_value());
  const auto [l, r] = trees.value();

  equal<TreeNary_T1, TreeNary_T2>
    (l, r, [](const TreeNary_T1& l,
              const TreeNary_T2& r) -> bool {
      return l.n == r.n;
  });
}


} // Concepts
