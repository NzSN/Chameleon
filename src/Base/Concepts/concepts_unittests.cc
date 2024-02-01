#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "n_ary_tree.h"
#include <vector>
#include <tuple>
#include <optional>


namespace Concepts {
namespace NAryTree {

struct NAryTreeTests: public ::testing::Test {
  struct TreeNary_T1 {
    int n;
    std::vector<TreeNary_T1>& getChildren() {
      return c;
    }
    std::vector<TreeNary_T1> c;
  };
  struct TreeNary_T2 {
    int n;
    std::vector<TreeNary_T2> children;
  };
  struct UpperLayerOfT1 {
    UpperLayerOfT1(const TreeNary_T1& t) {
      MAP_TO_TREE(t);
    }

    DEFINE_AS_LAYER_OF_NARY_TREE(UpperLayerOfT1, TreeNary_T1, public);
  };

  TreeNary_T1* l;
  TreeNary_T2* r;

  std::optional<const std::tuple<
    std::unique_ptr<TreeNary_T1>,
    std::unique_ptr<TreeNary_T2>>>
  genTwinsNAry(const unsigned int n_nodes) {
    std::unique_ptr<TreeNary_T1> l = std::make_unique<TreeNary_T1>();
    std::unique_ptr<TreeNary_T2> r = std::make_unique<TreeNary_T2>();

    std::function<void(TreeNary_T1*,TreeNary_T2*,int)>
      genSubTreeWithN = [&](TreeNary_T1* l, TreeNary_T2* r, int nsubs) {
        while (nsubs > 0) {
          // Create directly child
          l->getChildren().emplace_back();
          TreeNary_T1& child_l = l->getChildren().back();
          r->children.emplace_back();
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

    genSubTreeWithN(l.get(), r.get(), n_nodes - 1);

    return std::make_tuple(std::move(l), std::move(r));
  }
};

RC_GTEST_FIXTURE_PROP(NAryTreeTests, Equal, ()) {
  int n = *rc::gen::inRange(1, 100);
  const auto& trees = genTwinsNAry(n);

  RC_ASSERT(trees.has_value());
  const auto& [l, r] = trees.value();

  bool isEqual = equal<TreeNary_T1, TreeNary_T2>
    (*l, *r, [](const TreeNary_T1& l,
              const TreeNary_T2& r) -> bool {
      return l.n == r.n;
    });
  RC_ASSERT(isEqual);
}

RC_GTEST_FIXTURE_PROP(NAryTreeTests, Isomorphic, ()) {
  int n = *rc::gen::inRange(1, 100);
  const auto& trees = genTwinsNAry(n);

  RC_ASSERT(trees.has_value());
  const auto& [l, r] = trees.value();

  UpperLayerOfT1 ut1{*l};
  RC_ASSERT((isIsomorphic<TreeNary_T1, UpperLayerOfT1>(ut1, *l)));
}


} // NAryTree
} // Concepts
