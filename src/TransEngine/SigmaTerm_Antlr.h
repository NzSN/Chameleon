#ifndef SIGMATERM_ANTLR_H
#define SIGMATERM_ANTLR_H

#include <string>
#include <typeinfo>

#include "Base/langs.h"
#include "Base/generic_parsetree_antlr4.h"
#include "Misc/testLanguage/TestLangParser.h"
#include "parsers/wgsl/WGSLParser.h"
#include "Base/generic_parsetree_antlr4_gc.h"

namespace Chameleon::SIGMA_TERM {

template<Base::SUPPORTED_LANGUAGE LANG = Base::SUPPORTED_LANGUAGE::TESTLANG>
requires Base::isTestLang<LANG>
bool isTermVar(Base::Antlr4Node& node) {
  std::string literal = node.getText();

  const std::type_info& info = typeid(*node.tree());

  if (info == typeid(TestLangParser::ExprContext) ||
      info == typeid(Utility::TypeMapping<TestLangParser::ExprContext>::type)) {
    if (literal.size() != 1) {
      return false;
    }
    char c = literal[0];

    return 'a' <= c && c <= 'z';
  } else {
    return false;
  }
}

template<Base::SUPPORTED_LANGUAGE LANG = Base::SUPPORTED_LANGUAGE::TESTLANG>
requires Base::isWGSL<LANG>
bool isTermVar(Base::Antlr4Node& node) {
  std::string literal = node.getText();

  const std::type_info& info = typeid(*node.tree());

  if (info == typeid(WGSLParser::IdentContext) ||
      info == typeid(Utility::TypeMapping<WGSLParser::IdentContext>::type)) {
    return literal.size() == 1 && literal[0] >= 'a' && literal[0] <= 'z';
  } else {
    return false;
  }
}

} // SIGMA_TERM

#endif /* SIGMATERM_ANTLR_H */
