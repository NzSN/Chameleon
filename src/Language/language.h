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


template<Treelike T, Parser<T> P>
class Language {
public:
  // Default constructor may be implicit delted
  // just make it explicit so interface could be
  // consistency even if 'P' is varing.
  Language() = delete;

  Language(std::string sentence): tree_{} {
    parser_ = std::make_unique<P>(sentence);
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
