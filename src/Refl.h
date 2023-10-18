#ifndef REFL_H
#define REFL_H

#include <string>
#include <map>
#include <memory>
#include <any>
#include <optional>

namespace Utility {
namespace Refl {

struct ReflItem {
  template<typename T>
  ReflItem(T src):
    inner_(new Inner<T>(std::forward<T>(src))) {}

  template<typename R>
  R operator()(std::any arg) {
    return (*inner_)(arg);
  }

  struct InnerBase {
    using ptr = std::unique_ptr<InnerBase>;
    virtual void operator()(std::any arg) const = 0;
  };
  template<typename T>
  struct Inner: InnerBase {
    Inner(T src): value_{src} {}

    template<typename R>
    R operator()(std::any arg) {
      return value_();
    }
  private:
    T value_;
  };

private:
  typename InnerBase::ptr inner_;
};

struct Refl {
  using TypeName = std::string;

  Refl& getInstance() {
    static Refl instance;
    return instance;
  }

  template<typename R>
  std::optional<R> reflect(TypeName name) {
    if (!types.contains(name)) {
      return std::nullopt;
    }

    ...
  }
private:
  std::map<TypeName, ReflItem> types;
};


} // Refl
} // Utility

#endif /* REFL_H */
