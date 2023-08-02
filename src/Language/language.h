#include <concepts>
#include <string>

#ifndef LANGUAGE_H
#define LANGUAGE_H

namespace Language {

template<typename T>
concept TreelikeStruct = requires(T t) {
  { t.childs() } -> std::ranges::range;
};

template<typename T, typename TR>
concept Parser = TreelikeStruct<TR> && requires(T t, std::string sentences) {
  { t.parse(sentences) } -> std::same_as<TR>;
};


template<TreelikeStruct T, Parser<T> P>
class Language {
public:
  // The caller of Language<T,P>::parse should
  // not owning the parsetree return from it. Due
  // to the varity of exists parsers, the parsetree
  // may owning by another entity reside in the
  // parser we used to parse the input sentences.
  T* parse(std::string sentences);


};


} // Language

#endif /* LANGUAGE_H */
