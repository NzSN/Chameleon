/* This file contains tools to generate deep copy listener
 * for antlr trees. */

#ifndef GENERIC_PARSETREE_ANTLR4_DEEPCOPY_H
#define GENERIC_PARSETREE_ANTLR4_DEEPCOPY_H

#include "Base/config.h"
#include "Base/defines.h"

#include <iostream>
#include <functional>
#include <string.h>
#include <map>
#include <exception>
#include <tuple>
#include <concepts>
#include <optional>

#include "utility.h"
#include "antlr4-runtime.h"

#include "Base/generic_parsetree_antlr4_gc.h"

namespace Antlr4DeepCopy {

struct FAILED_TO_MAPPING_TO_CAT_THECOPY: std::exception {
  ~FAILED_TO_MAPPING_TO_CAT_THECOPY() {}

  const char* what() const noexcept {
    return "Unable to mapping to category thecopy";
  }
};

template<typename T>
struct FAILED_TO_MAPPING: std::exception {
  FAILED_TO_MAPPING(T from, T to):
    msg{"Failed to mapping"} {}
  ~FAILED_TO_MAPPING() {}

  const char* what() const noexcept {
    return msg.c_str();
  }

  std::string msg;
};

/* A Functor maps original nodes to duplicated
 * nodes.
 *
 * CopyRealm :: T -> CopyRealm T */
template<typename T>
//requires Utility::Hashable<T>
class CopyRealm: Utility::Functor<CopyRealm, T> {
public:
  CopyRealm(T a): Utility::Functor<CopyRealm, T>(a) {}

  std::optional<T> operator()() {
    if (mappings_.contains(this->a)) {
      return mappings_[this->a];
    } else {
      return std::nullopt;
    }
  }

  using F = std::function<T(T)>;
  using G = std::function<CopyRealm<T>(CopyRealm<T>)>;
  G operator()(F f) const {
    return [&](CopyRealm<T> f_a) {
      return CopyRealm<T>(f(f_a.a));
    };
  }

  static void mapping(T from, T to) {
    if (!mappings_.contains(from)) {
      mappings_[from] = to;
    } else if (mappings_[from] == to) {
      return;
    } else {
      throw FAILED_TO_MAPPING(from, to);
    }
  }

  static void clear() {
    mappings_.clear();
  }

private:
  inline static std::unordered_map<T, T> mappings_{};
};

using TreeNode = antlr4::tree::ParseTree;
using TerminalNode = antlr4::tree::TerminalNodeImpl;

inline TerminalNode* copyTerminalNode(TerminalNode* orig) {
  if (!orig) { return nullptr; }
  TerminalNode* copy = new antlr4::tree::TerminalNodeImpl(orig->getSymbol());

  std::optional<TreeNode*> parent = CopyRealm<TreeNode*>(orig->parent)();
  copy->setParent(
    dynamic_cast<antlr4::RuleContext*>(
      parent.has_value() ? parent.value() : nullptr));

  return copy;
}

/* PRECOND:  orig->parent != nullptr &&
 *           CopyRealm<TreeNode*>(orig->parent).has_value() &&
 *           CopyRealm<TreeNode*>(orig).value() == copy &&
 *           copy \notin CopyRealm<TreeNode*>(orig->parent).value()->children
 * POSTCOND: CopyRealm<TreeNode*>(orig->parent)() == copy->parent */
inline bool buildUpConnect(TreeNode* orig, TreeNode* copy) {
  std::optional<TreeNode*>
    parentMaybe = CopyRealm<TreeNode*>(orig->parent)(),
    imgOfOrigMaybe = CopyRealm<TreeNode*>(orig)();

  if (orig->parent == nullptr     ||
      !parentMaybe.has_value()    ||
      !imgOfOrigMaybe.has_value() ||
      imgOfOrigMaybe.value() != copy) {
    return false;
  }

  TreeNode* parent = parentMaybe.value();
  bool binded = std::ranges::contains(
    parent->children, copy);

  if (!binded) {
    parentMaybe.value()->children.push_back(copy);

    // Handle GC Reference
    Base::GC::GCObject* parentGC =
      dynamic_cast<Base::GC::GCObject*>(parent);
    Base::GC::GCObject* copyGC =
      dynamic_cast<Base::GC::GCObject*>(copy);

    if (!parentGC && !copyGC) {
      parentGC->reach(copyGC);
    }
  }

  return true;
}

#define _NSS(X) Antlr4DeepCopy::X
#define _C(CTX) CTX##Context
#define __C(PARSER, CTX, LANG) PARSER::_C(CTX)
#define __C_PTR(PARSER, CTX, LANG) __C(PARSER,CTX,LANG)*
#define __NEW(T, ...) Base::genericNew<T>(__VA_ARGS__)
#define _MAP(T) Utility::TypeMapping<T>::type

#define COPY_ANTLR4_NON_TERMINAL(LANG, PARSER, ENTRY, CTX)                     \
  void enter##CTX(PARSER::_C(CTX) *ctx) {                                      \
    __C_PTR(PARSER,CTX,LANG) copy;                                             \
    if (std::string(#ENTRY) == std::string(#CTX)) {                            \
      /* ENTRY should has no parent. */                                        \
      copy = __NEW(_MAP(__C(PARSER,CTX,LANG)), nullptr, -1);                   \
      /* Build mapping between them */                                         \
      _NSS(CopyRealm)<_NSS(TreeNode)*>::mapping(ctx, copy);                    \
    } else {                                                                   \
      auto node = _NSS(CopyRealm)<_NSS(TreeNode)*>(ctx->parent)();             \
      if (node.has_value()) {                                                  \
        copy = __NEW(_MAP(__C(PARSER,CTX,LANG)),                               \
                     dynamic_cast<antlr4::ParserRuleContext*>(node.value()),   \
                     ctx->invokingState);                                      \
        /* Mapping should be made before buildup connect to parent */          \
        /* otherwise violate precondition of buildUpConnect() */               \
        _NSS(CopyRealm)<_NSS(TreeNode)*>::mapping(ctx, copy);                  \
        _NSS(buildUpConnect)(ctx, copy);                                       \
      } else {                                                                 \
        copy = __NEW(_MAP(__C(PARSER,CTX,LANG)), nullptr, ctx->invokingState); \
        _NSS(CopyRealm)<_NSS(TreeNode)*>::mapping(ctx, copy);                  \
      }                                                                        \
    }                                                                          \
  }                                                                            \
  void exit##CTX(PARSER::CTX##Context *ctx) {}

#define COPY_ANTLR4_TERMINAL                                           \
  void visitTerminal(antlr4::tree::TerminalNode *node) {               \
    antlr4::tree::TerminalNodeImpl* copy =                             \
      __NEW(_MAP(antlr4::tree::TerminalNodeImpl), node->getSymbol());  \
    std::optional<_NSS(TreeNode)*> parent =                            \
      _NSS(CopyRealm)<_NSS(TreeNode)*>(node->parent)();                \
    if (parent.has_value()) {                                          \
      copy->setParent(                                                 \
        dynamic_cast<antlr4::RuleContext*>(parent.value()));           \
      _NSS(CopyRealm)<_NSS(TreeNode)*>::mapping(node, copy);           \
      _NSS(buildUpConnect(dynamic_cast<_NSS(TreeNode)*>(node), copy)); \
    } else {                                                           \
      _NSS(CopyRealm)<_NSS(TreeNode)*>::mapping(node, copy);           \
    }                                                                  \
  }

#define DEEPCOPY_IMPL(BASE_LISTENER, CTXs)                             \
  struct __LISTENER: public BASE_LISTENER {                            \
    CTXs(COPY_ANTLR4_NON_TERMINAL);                                    \
    COPY_ANTLR4_TERMINAL;                                              \
  };                                                                   \
  inline _NSS(TreeNode)* clone(_NSS(TreeNode)* tree) {                 \
    __LISTENER listener;                                               \
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);      \
                                                                       \
    std::optional<_NSS(TreeNode)*> copyRoot = _NSS(CopyRealm)(tree)(); \
    _NSS(CopyRealm)<_NSS(TreeNode)*>::clear();                         \
                                                                       \
    return copyRoot.has_value() ?                                      \
    copyRoot.value() : nullptr;                                        \
  }

} // Antlr4DeepCopy

#endif /* GENERIC_PARSETREE_ANTLR4_DEEPCOPY_H */
