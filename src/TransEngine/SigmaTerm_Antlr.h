#ifndef SIGMATERM_ANTLR_H
#define SIGMATERM_ANTLR_H

#include <format>
#include <type_traits>
#include <string>
#include <typeinfo>

#include "Base/langs.h"
#include "Base/generic_parsetree_antlr4.h"

#include "Misc/testLanguage/TestLangParser.h"
#include "parsers/wgsl/WGSLParser.h"

namespace SIGMA_TERM {

template<int LANG=Base::SUPPORTED_LANGUAGE::TESTLANG,
         typename = std::enable_if_t<LANG == Base::SUPPORTED_LANGUAGE::TESTLANG>>
bool isTermVar(Base::Antlr4Node& node) {
  std::string literal = node.getText();
  if (typeid(*node.tree()) == typeid(TestLangParser::ExprContext)) {
    if (literal.size() != 1) {
      return false;
    }
    char c = literal[0];

    return 'a' <= c && c <= 'z';
  } else {
    return false;
  }
}

template<int LANG=Base::SUPPORTED_LANGUAGE::TESTLANG,
         typename = std::enable_if_t<LANG == Base::SUPPORTED_LANGUAGE::WGSL>,
         int = 1>
bool isTermVar(Base::Antlr4Node& node) {
  std::string literal = node.getText();
  if (typeid(*node.tree()) == typeid(WGSLParser::IdentContext)) {
    if (literal.size() != 3) return false;
    return literal[0] == '_' && literal[1] == '_';
  } else {
    return false;
  }

  std::unreachable();
}


} // SIGMA_TERM

#endif /* SIGMATERM_ANTLR_H */
