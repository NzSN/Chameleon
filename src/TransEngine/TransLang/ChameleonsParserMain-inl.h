#include <stdexcept>

#include "ChameleonsParserMain.h"
#include "ChameleonsLexer.h"
#include "ChameleonsParser.h"
#include "ChameleonsParserBaseListener.h"

#include "Base/generic_parsetree_metas.h"
#include "TransEngine/Rewrite/Environment.h"

namespace TransEngine {
namespace Compiler {

template<typename T>
Base::GenericParseTree<T>
Program<T>::operator()(Base::GenericParseTree<T>& tree,
                       Analyzer::AnalyzeData<T>& metaInfo) {}

template<typename T>
Base::GenericParseTree<T>
Program<T>::operator()(Base::GenericParseTree<T>& tree) {}

/////////////////////////////////////////////////////////////////////////////
//                                 Compiler                                //
/////////////////////////////////////////////////////////////////////////////

struct CompileListener: public ChameleonsParserBaseListener {
  void enterProg(ChameleonsParser::ProgContext *ctx) {
    // Sections that required to form
    // a minimal Chameleons Program.
    //
    // Strategies section is optional so
    // no need to check.
    if (ctx->targetSection() == nullptr) {
      throw std::runtime_error(
        "TARGET Section is required\n");
    }
    if (ctx->ruleSection() == nullptr) {
      throw std::runtime_error(
        "RULE Section is required\n");
    }

    // Next to determine which target language
    // the program need to deal with.
    targetLang =
      ctx->targetSection()
         ->IDENTIFIER()
         ->getText();


  }

  std::string targetLang;
};

template<typename T>
Program<T> Compiler<T>::compile(std::istream& stream) {
  antlr4::ANTLRInputStream input(stream);
  ChameleonsLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  ChameleonsParser parser(&tokens);

  antlr4::tree::ParseTree *tree = parser.prog();

  // Use listener or visitor to traverse Chameleons
  // ParseTree then translate into Program.

  CompileListener listener;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
}


} // Compiler
} // TransEngine
