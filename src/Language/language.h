#include <concepts>
#include <string>
#include <memory>

#ifndef LANGUAGE_H
#define LANGUAGE_H

namespace Language {

template<typename T>
concept Treelike = requires(T t) {
  { t.children } -> std::ranges::range;
} || requires(T t) {
  { t.children() } -> std::ranges::range;
};
template<typename T, typename TR>
concept Parser = Treelike<TR> &&
  requires(T t, std::string sentences) {
    { t.parse(sentences) } -> std::same_as<TR*>;
};

// Entity to represent sentences of Language correspond
// to Parser 'P'. It provide syntatic information of
// the sentences that used to materialize it.
template<Treelike T, Parser<T> P>
class Language {
public:
  // Semantic of Language is to transform
  // sentences into entity that able to used
  // by transform steps, GenericParseTree Mapping or
  // code Analyze..., so constructed without arguments
  // is nonsense.
  Language() = delete;

  Language(std::string sentence): tree_{} {
    parser_ = std::make_unique<P>();
    tree_ = parser_->parse(sentence);
  };

  T* tree() {
    return tree_;
  }

private:
  T* tree_;
  std::unique_ptr<P> parser_;
};

} // Language

#endif /* LANGUAGE_H */
