#ifndef REFL_H
#define REFL_H

#include <string>
#include <vector>
#include <optional>
#include <algorithm>

namespace Utility {

/////////////////////////////////////////////////////////////////////////////
//               A Simple reflection to mapping string to objects          //
/////////////////////////////////////////////////////////////////////////////

template<typename T>
class VarScopeGuard;

// Var does not gurantee to manage memory point by data.
struct Var {
  Var(): data{} {}
  Var(void* ptr): data{ptr} {}

  Var(const Var& other) {
    data = other.data;
  }

  template<typename T>
  T* convert() const {
    return reinterpret_cast<T*>(data);
  }

private:
  template<typename T>
  friend class VarScopeGuard;

  void* data;
};

template<typename T>
class VarScopeGuard {
public:
  VarScopeGuard(Var data):
    data_{data} {}
  VarScopeGuard(std::optional<Var> data):
    data_{} {

    if (data.has_value()) {
      data_.data = data.value().data;
    }
  }
  ~VarScopeGuard() {
    if (data_.data) {
      delete reinterpret_cast<T*>(data_.data);
    }
  }
private:
  Var data_;
};


struct Type {
  using Constructor = Var(*)();

  std::string name;
  Constructor ctor;
};

#define Stringify(...) #__VA_ARGS__

class Reflection {
public:
  static void registering(std::string name, Var(*ctor)()) {
    types.push_back(Type{name, ctor});
  }

  static std::optional<Var> construct(std::string type) {
    auto found_iter = std::find_if(types.begin(), types.end(),
                                [&](const Type& t) -> bool {
                                  return t.name == type;
                                });
    if (found_iter != types.end()) {
      return found_iter->ctor();
    } else {
      return std::nullopt;
    }
  }
private:
  static std::vector<Type> types;
};

inline std::vector<Type> Reflection::types = {};

} // Utility

#endif /* REFL_H */
