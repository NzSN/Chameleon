
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
      "IDENTIFIER", "COLON", "OPENBRACE", "TRANSFORM", "WS", "CODEBYTES", 
      "CLOSEBRACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "PROGRAM"
    },
    std::vector<std::string>{
      "", "", "':'", "'{'", "'=>'", "", "", "'}'"
    },
    std::vector<std::string>{
      "", "IDENTIFIER", "COLON", "OPENBRACE", "TRANSFORM", "WS", "CODEBYTES", 
      "CLOSEBRACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,7,52,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,
  	6,7,6,1,0,1,0,5,0,19,8,0,10,0,12,0,22,9,0,1,1,1,1,1,2,1,2,1,2,1,2,1,3,
  	1,3,1,3,1,4,4,4,34,8,4,11,4,12,4,35,1,4,1,4,1,5,1,5,1,5,1,5,1,5,4,5,45,
  	8,5,11,5,12,5,46,1,6,1,6,1,6,1,6,0,0,7,2,1,4,2,6,3,8,4,10,5,12,6,14,7,
  	2,0,1,4,2,0,65,90,97,122,3,0,48,57,65,90,97,122,3,0,9,10,13,13,32,32,
  	2,0,123,123,125,125,55,0,2,1,0,0,0,0,4,1,0,0,0,0,6,1,0,0,0,0,8,1,0,0,
  	0,0,10,1,0,0,0,1,12,1,0,0,0,1,14,1,0,0,0,2,16,1,0,0,0,4,23,1,0,0,0,6,
  	25,1,0,0,0,8,29,1,0,0,0,10,33,1,0,0,0,12,44,1,0,0,0,14,48,1,0,0,0,16,
  	20,7,0,0,0,17,19,7,1,0,0,18,17,1,0,0,0,19,22,1,0,0,0,20,18,1,0,0,0,20,
  	21,1,0,0,0,21,3,1,0,0,0,22,20,1,0,0,0,23,24,5,58,0,0,24,5,1,0,0,0,25,
  	26,5,123,0,0,26,27,1,0,0,0,27,28,6,2,0,0,28,7,1,0,0,0,29,30,5,61,0,0,
  	30,31,5,62,0,0,31,9,1,0,0,0,32,34,7,2,0,0,33,32,1,0,0,0,34,35,1,0,0,0,
  	35,33,1,0,0,0,35,36,1,0,0,0,36,37,1,0,0,0,37,38,6,4,1,0,38,11,1,0,0,0,
  	39,45,8,3,0,0,40,41,5,92,0,0,41,45,5,123,0,0,42,43,5,92,0,0,43,45,5,125,
  	0,0,44,39,1,0,0,0,44,40,1,0,0,0,44,42,1,0,0,0,45,46,1,0,0,0,46,44,1,0,
  	0,0,46,47,1,0,0,0,47,13,1,0,0,0,48,49,5,125,0,0,49,50,1,0,0,0,50,51,6,
  	6,2,0,51,15,1,0,0,0,6,0,1,20,35,44,46,3,2,1,0,6,0,0,2,0,0
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
