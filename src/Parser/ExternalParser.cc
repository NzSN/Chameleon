#include "ExternalParser.h"

namespace Parser {
std::vector<TestLangExt::EnvPtr> TestLangExt::envs;
antlr4::tree::ParseTree* TestLangExt::tree = nullptr;
} // Parser
