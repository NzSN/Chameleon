
#ifndef ANALYZER_H
#define ANALYZER_H

#include <utility>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "plog/Log.h"
#include "Concepts/n_ary_tree.h"

namespace Analyzer {

using Concepts::NAryTree::NAryTree;

namespace {

struct AnalyzeState {
  enum Status {
    // None of nodes are analyzed.
    Unanalyzed = 0,
    // Root node of the subtree is analyzed but
    // none of descdent nodes are analyzed.
    Analyzing = 1,
    // All nodes of the tree
    // is analyzed.
    Finished = 2
  };

  bool IsUnanalyzed() const {
    return state == Unanalyzed;
  }

  bool IsAnalyzing() const {
    return state == Analyzing;
  }

  bool IsFinished() const {
    return state == Finished;
  }

  Status state;
};

}

template<NAryTree T>
struct AnalyzeData {
  std::vector<T> defines;
  std::vector<T> merge(AnalyzeData d1, AnalyzeData d2) {

  }
};

template<typename F, typename T>
concept ParseTreeAnalyze =
  NAryTree<T> &&
  requires(F f, T t) {
    { f(t) } -> std::same_as<std::tuple<AnalyzeState, AnalyzeData<T>>>;
  };

template<NAryTree T,
         ParseTreeAnalyze<T> A>
class Analyzer {
public:
  static AnalyzeData<T> Analyze(T& tree, A nodeAnalyzer) {
    // Analyzing started from Root.
    DoAnalyze(tree, tree, nodeAnalyzer);
  }
private:
  static AnalyzeData<T> DoAnalyze(T& tree, T& node, A nodeAnalyzer) {
    // Analyzeing node
    std::tuple<AnalyzeState, AnalyzeData<T>>
      analyzedInfo = nodeAnalyzer(node);

    AnalyzeState state = std::get<0>(analyzedInfo);
    if (state.IsAnalyzing()) {
      // Descdent nodes of subtree still unanalyzed
      // need to parsed them recursively.
      std::vector<T> children = node.getChildren();

      std::transform_reduce(, children.cbegin(), children.cend(), );

    } else if (state.IsFinished()) {
      return std::get<1>(analyzedInfo);
    } else {
      PLOG_FATAL << "Failed to analyze: node still in "
                 << "Unanalyzed state after analyze.";
      std::abort();
    }
  }
};

} // Analyzer


#endif /* ANALYZER_H */
