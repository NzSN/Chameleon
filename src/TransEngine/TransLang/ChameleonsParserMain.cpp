#include <unordered_map>
#include "ChameleonsParserMain-inl.h"

namespace TransEngine {
namespace Compiler {

std::unordered_map<std::string, Base::GptSupportLang> langs = {
  {"TestLang", Base::GptSupportLang::TESTLANG}
};

Base::GptSupportLang toLangID(std::string langID) {
  return langs[langID];
}

} // Compiler
} // TransEngine
