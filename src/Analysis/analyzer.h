#ifndef ANALYZER_H
#define ANALYZER_H

#include <utility>
#include <unordered_set>
#include <functional>
#include <vector>
#include <map>
#include <numeric>
#include <cstdlib>
#include <functional>
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

  struct DataHash {
    size_t operator()(const std::reference_wrapper<T> item) const {
      return reinterpret_cast<std::uintptr_t>(&item.get());
    }
  };

  struct DataEqual {
    constexpr bool operator()(const std::reference_wrapper<T> l,
                              const std::reference_wrapper<T> r) const {
      return l.get() == r.get();
    }
  };

  using DataSet = std::unordered_set<std::reference_wrapper<T>,
                                     DataHash, DataEqual>;
  using Data = std::map<std::string, DataSet>;

  AnalyzeData() : data{} {}
  AnalyzeData(AnalyzeData& ad) : data{ad.data} {}
  AnalyzeData& operator=(AnalyzeData& ad) {
    return AnalyzeData{ad};
  }
  AnalyzeData(AnalyzeData&& ad) : data{std::move(ad.data)} {}
  AnalyzeData& operator=(AnalyzeData&& ad) {
    return AnalyzeData{std::move(ad)};
  }

  // Generate new data, d3, by merge d1 and d2,
  // INVARIANT:
  // 1.\A x \in d1,\A y \in d2:
  //     (x \in d3) /\ (y \in d3)
  // 2.\exists x \in d1:
  //     (x \in d2) => (x \in d3 /\ (\A y \in d3\{x}: x /= y))
  static AnalyzeData merge(AnalyzeData& d1, AnalyzeData& d2) {
    AnalyzeData merged{d1};

    for (auto& [key, lineOfData]: d2.data) {
      if (merged.data.contains(key)) {
        std::unordered_set<std::reference_wrapper<T>>& dataValue = merged.data;

        std::for_each(lineOfData.cbegin(), lineOfData.cend(),
                      [&](std::reference_wrapper<T> d) {
                        dataValue.insert(d);
                      });
      } else {
        merged.data.insert(std::make_tuple(key, lineOfData));
      }
    }

    return merged;
  }

  Data data;
};

template<typename F, typename T>
concept NodeAnalyzer =
  NAryTree<T> &&
  requires(F f, T t) {
    { f(t) } -> std::same_as<std::tuple<AnalyzeState, AnalyzeData<T>>>;
  };

template<NAryTree T,
         NodeAnalyzer<T> A>
class Analyzer {
public:
  static AnalyzeData<T> Analyze(T& tree, A nodeAnalyzer) {
    // Analyzing started from Root.
    DoAnalyze(tree, nodeAnalyzer);
  }
private:
  static AnalyzeData<T> DoAnalyze(T& node, A nodeAnalyzer) {
    // Analyzeing node
    std::tuple<AnalyzeState, AnalyzeData<T>>
      analyzedInfo = nodeAnalyzer(node);

    AnalyzeState state = std::get<0>(analyzedInfo);
    if (state.IsAnalyzing()) {
      // Descdent nodes of subtree still unanalyzed
      // need to analyze them recursively.
      std::vector<T> children = node.getChildren();

      std::for_each(
        children.cbegin(), children.cend(),
        [&](const T& child) {
          AnalyzeData<T> data = DoAnalyze(child, nodeAnalyzer);
          std::get<1>(analyzedInfo) =
            AnalyzeData<T>::merge(std::get<1>(analyzedInfo, data));
        });

      return std::get<1>(analyzedInfo);
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
