#ifndef API_PROGRAM_H
#define API_PROGRAM_H

#include <ranges>

#include "Base/langs.h"
#include "Base/langsInfo.h"
#include "Rule.h"

namespace Chameleon::api {

namespace Compiler = TransEngine::Compiler;

template<Base::isLangType lang>
struct Program {
  Program(): program{Base::LangArg<lang>::langEnum} {}

  template<typename T>
  requires std::ranges::range<T> &&
           std::same_as<std::ranges::range_value_t<T>, Rule<lang>>
  Program(T t): program{Base::LangArg<lang>::langEnum} {
    using Arg = typename Base::LangArg<lang>;

    for (auto iter = std::ranges::begin(t);
       iter != std::ranges::end(t);
       ++iter) {

      RewriteSys::StrategySeq<typename Arg::Adapter> seq =
        iter->toStrategy();
      for (auto& s: seq) {
        program.write(std::move(s));
      }
    }
  }

  using Adapter = Base::LangArg<lang>::Adapter;
  std::optional<Base::ParseTree<Adapter>>
  operator()(Base::ParseTree<Adapter>& tree) {
    return program(tree);
  }

private:
  Compiler::Program program;
};


} // Chameleon::api


#endif /* API_PROGRAM_H */
