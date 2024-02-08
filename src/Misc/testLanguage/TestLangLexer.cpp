
// Generated from ./TestLang.g4 by ANTLR 4.13.0


#include "TestLangLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct TestLangLexerStaticData final {
  TestLangLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TestLangLexerStaticData(const TestLangLexerStaticData&) = delete;
  TestLangLexerStaticData(TestLangLexerStaticData&&) = delete;
  TestLangLexerStaticData& operator=(const TestLangLexerStaticData&) = delete;
  TestLangLexerStaticData& operator=(TestLangLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag testlanglexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
TestLangLexerStaticData *testlanglexerLexerStaticData = nullptr;

void testlanglexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (testlanglexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(testlanglexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TestLangLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "NEWLINE", "INT", 
      "PLACEHOLDER", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'*'", "'/'", "'+'", "'-'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "NEWLINE", "INT", "PLACEHOLDER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,10,52,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,
  	1,5,1,6,4,6,35,8,6,11,6,12,6,36,1,7,4,7,40,8,7,11,7,12,7,41,1,8,1,8,1,
  	9,4,9,47,8,9,11,9,12,9,48,1,9,1,9,0,0,10,1,1,3,2,5,3,7,4,9,5,11,6,13,
  	7,15,8,17,9,19,10,1,0,4,2,0,10,10,13,13,1,0,48,57,1,0,97,122,3,0,9,10,
  	13,13,32,32,54,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,
  	0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,
  	0,1,21,1,0,0,0,3,23,1,0,0,0,5,25,1,0,0,0,7,27,1,0,0,0,9,29,1,0,0,0,11,
  	31,1,0,0,0,13,34,1,0,0,0,15,39,1,0,0,0,17,43,1,0,0,0,19,46,1,0,0,0,21,
  	22,5,42,0,0,22,2,1,0,0,0,23,24,5,47,0,0,24,4,1,0,0,0,25,26,5,43,0,0,26,
  	6,1,0,0,0,27,28,5,45,0,0,28,8,1,0,0,0,29,30,5,40,0,0,30,10,1,0,0,0,31,
  	32,5,41,0,0,32,12,1,0,0,0,33,35,7,0,0,0,34,33,1,0,0,0,35,36,1,0,0,0,36,
  	34,1,0,0,0,36,37,1,0,0,0,37,14,1,0,0,0,38,40,7,1,0,0,39,38,1,0,0,0,40,
  	41,1,0,0,0,41,39,1,0,0,0,41,42,1,0,0,0,42,16,1,0,0,0,43,44,7,2,0,0,44,
  	18,1,0,0,0,45,47,7,3,0,0,46,45,1,0,0,0,47,48,1,0,0,0,48,46,1,0,0,0,48,
  	49,1,0,0,0,49,50,1,0,0,0,50,51,6,9,0,0,51,20,1,0,0,0,4,0,36,41,48,1,6,
  	0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  testlanglexerLexerStaticData = staticData.release();
}

}

TestLangLexer::TestLangLexer(CharStream *input) : Lexer(input) {
  TestLangLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *testlanglexerLexerStaticData->atn, testlanglexerLexerStaticData->decisionToDFA, testlanglexerLexerStaticData->sharedContextCache);
}

TestLangLexer::~TestLangLexer() {
  delete _interpreter;
}

std::string TestLangLexer::getGrammarFileName() const {
  return "TestLang.g4";
}

const std::vector<std::string>& TestLangLexer::getRuleNames() const {
  return testlanglexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& TestLangLexer::getChannelNames() const {
  return testlanglexerLexerStaticData->channelNames;
}

const std::vector<std::string>& TestLangLexer::getModeNames() const {
  return testlanglexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& TestLangLexer::getVocabulary() const {
  return testlanglexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TestLangLexer::getSerializedATN() const {
  return testlanglexerLexerStaticData->serializedATN;
}

const atn::ATN& TestLangLexer::getATN() const {
  return *testlanglexerLexerStaticData->atn;
}




void TestLangLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  testlanglexerLexerInitialize();
#else
  ::antlr4::internal::call_once(testlanglexerLexerOnceFlag, testlanglexerLexerInitialize);
#endif
}
