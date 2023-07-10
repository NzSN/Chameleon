
// Generated from ChameleonsLexer.g4 by ANTLR 4.13.0


#include "ChameleonsLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct ChameleonsLexerStaticData final {
  ChameleonsLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ChameleonsLexerStaticData(const ChameleonsLexerStaticData&) = delete;
  ChameleonsLexerStaticData(ChameleonsLexerStaticData&&) = delete;
  ChameleonsLexerStaticData& operator=(const ChameleonsLexerStaticData&) = delete;
  ChameleonsLexerStaticData& operator=(ChameleonsLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag chameleonslexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ChameleonsLexerStaticData *chameleonslexerLexerStaticData = nullptr;

void chameleonslexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chameleonslexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(chameleonslexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ChameleonsLexerStaticData>(
    std::vector<std::string>{
      "IDENTIFIER", "CODEBYTES", "COLON", "OPENBRACE", "CLOSEBRACE", "TRANSFORM"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "", "':'", "'{'", "'}'", "'=>'"
    },
    std::vector<std::string>{
      "", "IDENTIFIER", "CODEBYTES", "COLON", "OPENBRACE", "CLOSEBRACE", 
      "TRANSFORM"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,6,36,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,1,0,1,0,
  	5,0,16,8,0,10,0,12,0,19,9,0,1,1,1,1,1,1,4,1,24,8,1,11,1,12,1,25,1,2,1,
  	2,1,3,1,3,1,4,1,4,1,5,1,5,1,5,0,0,6,1,1,3,2,5,3,7,4,9,5,11,6,1,0,3,2,
  	0,65,90,97,122,3,0,48,57,65,90,97,122,3,0,94,94,123,123,125,125,38,0,
  	1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,
  	0,1,13,1,0,0,0,3,23,1,0,0,0,5,27,1,0,0,0,7,29,1,0,0,0,9,31,1,0,0,0,11,
  	33,1,0,0,0,13,17,7,0,0,0,14,16,7,1,0,0,15,14,1,0,0,0,16,19,1,0,0,0,17,
  	15,1,0,0,0,17,18,1,0,0,0,18,2,1,0,0,0,19,17,1,0,0,0,20,24,7,2,0,0,21,
  	22,5,92,0,0,22,24,5,125,0,0,23,20,1,0,0,0,23,21,1,0,0,0,24,25,1,0,0,0,
  	25,23,1,0,0,0,25,26,1,0,0,0,26,4,1,0,0,0,27,28,5,58,0,0,28,6,1,0,0,0,
  	29,30,5,123,0,0,30,8,1,0,0,0,31,32,5,125,0,0,32,10,1,0,0,0,33,34,5,61,
  	0,0,34,35,5,62,0,0,35,12,1,0,0,0,4,0,17,23,25,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chameleonslexerLexerStaticData = staticData.release();
}

}

ChameleonsLexer::ChameleonsLexer(CharStream *input) : Lexer(input) {
  ChameleonsLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *chameleonslexerLexerStaticData->atn, chameleonslexerLexerStaticData->decisionToDFA, chameleonslexerLexerStaticData->sharedContextCache);
}

ChameleonsLexer::~ChameleonsLexer() {
  delete _interpreter;
}

std::string ChameleonsLexer::getGrammarFileName() const {
  return "ChameleonsLexer.g4";
}

const std::vector<std::string>& ChameleonsLexer::getRuleNames() const {
  return chameleonslexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& ChameleonsLexer::getChannelNames() const {
  return chameleonslexerLexerStaticData->channelNames;
}

const std::vector<std::string>& ChameleonsLexer::getModeNames() const {
  return chameleonslexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& ChameleonsLexer::getVocabulary() const {
  return chameleonslexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ChameleonsLexer::getSerializedATN() const {
  return chameleonslexerLexerStaticData->serializedATN;
}

const atn::ATN& ChameleonsLexer::getATN() const {
  return *chameleonslexerLexerStaticData->atn;
}




void ChameleonsLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chameleonslexerLexerInitialize();
#else
  ::antlr4::internal::call_once(chameleonslexerLexerOnceFlag, chameleonslexerLexerInitialize);
#endif
}
