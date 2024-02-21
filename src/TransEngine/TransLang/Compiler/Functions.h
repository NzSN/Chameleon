#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cassert>
#include "utility.h"

#include "Base/generic_parsetree_antlr4_gc.h"

#include "TransEngine/Rewrite/Expr/Expr.h"
#include "TransEngine/Rewrite/Environment.h"

namespace Chameleon {

using ExprTerm = TransEngine::Expression::Term;
using ExprVal  = TransEngine::Expression::Value;
using ExprArg  = TransEngine::Expression::Arguments;
using ExprFunc = TransEngine::Expression::Function;

template<Base::Layer T>
using RewriteTerm = TransEngine::Rewrite::Term<T>;

///////////////////////////////////////////////////////////////////////////////
//                              Common Functions                             //
///////////////////////////////////////////////////////////////////////////////
template<Base::Layer T>
Base::ParseTree<T>* gptFromExprTerm(ExprTerm* term) {
  return &term->term->tree.get();
}

template<typename... EXPECT>
bool typeCheckUnion(EXPECT&...);

template<>
inline bool typeCheckUnion(const std::type_info& type) {
  return false;
}

template<typename T, typename... EXPECTS>
bool typeCheckUnion(const std::type_info& type) {
  return (type == typeid(T)) || typeCheckUnion<EXPECTS...>(type);
}

template<typename... EXPECTS>
bool assertMetaType(Base::ParseTree<Base::Antlr4Node>* node) {
  const std::type_info& type = typeid(*node->getMetaMutable().tree());

  return typeCheckUnion<EXPECTS...>(type);
}

/////////////////////////////////////////////////////////////////////////////
//                            TestLang Functions                           //
/////////////////////////////////////////////////////////////////////////////

#define TESTLANG_FUNCTIONS(V) \
  V(Plus)

// Plus :: Term -> Term
struct Plus: public TransEngine::Expression::Function {
  Plus() {}

  std::unique_ptr<TransEngine::Expression::Value> operator()(
    TransEngine::Expression::Arguments* args,
    TransEngine::Rewrite::Environment<Base::Antlr4Node>* env) {

    if (args->args.size() != 1) {
      return nullptr;
    }

    // Try to convert the text presentation to integer,
    // no effects if failed to convert.
    if (!ExprVal::isTerm(*args->args[0])) {
      return nullptr;
    }

    Base::ParseTree<Base::Antlr4Node>* gpt =
      gptFromExprTerm<Base::Antlr4Node>(
        dynamic_cast<ExprTerm*>(args->args[0].get()));

    int number{};
    std::string numberMaybe = gpt->getText();

    try {
      number = std::stoi(numberMaybe);
      ++number;
    } catch (const std::invalid_argument& e) {
      return nullptr;
    } catch (const std::out_of_range& e) {
      return nullptr;
    }

    // After that reconstruct a Term from the new number
    std::unique_ptr<Base::ParseTree<Base::Antlr4Node>>
      gptCopy = gpt->clone();

    // Replace the original node by the copy node
    //
    // FIXME: If parser does not to manage the resource of
    //        the original node once it has been replaced
    //        and those resource should be reclaim here.
    // gpt->setNode(*gptCopy);

    // The type of underlying tree node should be antlr4::tree::ExprContext.
    bool isCorrectType = assertMetaType<
      TestLangParser::ExprContext,
      Utility::TypeMapping<TestLangParser::ExprContext>::type>(gptCopy.get());

    if (!isCorrectType) {
      return nullptr;
    }

    TestLangParser::ExprContext* context =
      dynamic_cast<TestLangParser::ExprContext*>(
        gptCopy->getMetaMutable().tree());

    antlr4::tree::TerminalNode* node = context->INT();

    antlr4::CommonToken* token =
      dynamic_cast<antlr4::CommonToken*>(node->getSymbol());
    if (!token) {
      // Underlying type is not an antlr4::CommonToken
      return nullptr;
    }

    token->setText(std::to_string(number));

    // Create Term from gptCopy.
    RewriteTerm<Base::Antlr4Node> rTerm{*gptCopy};

    env->holdResource(std::move(gptCopy));

    return std::make_unique<ExprTerm>(rTerm);
  }
};

/////////////////////////////////////////////////////////////////////////////
//                                   WGSL                                  //
/////////////////////////////////////////////////////////////////////////////
#define WGSL_FUNCTIONS(V) \
  V(RandomIdent)

using WGSLTree = Base::Antlr4Node;
using WGSLGpt  = Base::ParseTree<WGSLTree>;

struct RandomIdent: public ExprFunc {
  std::unique_ptr<ExprVal> operator()(
    ExprArg* args,
    TransEngine::Rewrite::Environment<WGSLTree>* env) {

    assertm(args && env, "null pointer");

    WGSLGpt* gpt = gptFromExprTerm<WGSLTree>(
      dynamic_cast<ExprTerm*>(args->args[0].get()));
    std::unique_ptr<WGSLGpt> copy = gpt->clone();

    bool isCorrectType = assertMetaType<
      WGSLParser::IdentContext,
      Utility::TypeMapping<WGSLParser::IdentContext>::type>(copy.get());
    if (!isCorrectType) {
      return nullptr;
    }

    WGSLParser::IdentContext* context =
      dynamic_cast<WGSLParser::IdentContext*>(
        copy->getMetaMutable().tree());
    antlr4::CommonToken* token =
      dynamic_cast<antlr4::CommonToken*>(
        context->Ident_pattern_token()->getSymbol());

    srand((unsigned)time(NULL) * getpid());
    token->setText(Utility::gen_random(5));

    RewriteTerm<WGSLTree> term{*copy};
    env->holdResource(std::move(copy));

    return std::make_unique<ExprTerm>(term);
  }

private:
};

} // Chameleon

#endif /* FUNCTIONS_H */
