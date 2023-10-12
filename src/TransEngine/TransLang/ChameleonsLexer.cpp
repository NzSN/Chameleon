
// Generated from ./ChameleonsLexer.g4 by ANTLR 4.13.1


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
      "IDENTIFIER", "COLON", "OPENBRACE", "BEGIN_TERM", "TRANSFORM", "WS", 
      "TERM_VAR", "TERM_FUN", "END_TERM", "CODEBYTES", "CLOSEBRACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "TERM", "PROGRAM"
    },
    std::vector<std::string>{
      "", "", "':'", "'{|'", "", "'=>'", "", "", "", "", "", "'|}'"
    },
    std::vector<std::string>{
      "", "IDENTIFIER", "COLON", "OPENBRACE", "BEGIN_TERM", "TRANSFORM", 
      "WS", "TERM_VAR", "TERM_FUN", "END_TERM", "CODEBYTES", "CLOSEBRACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,11,85,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,1,0,1,0,5,0,28,8,0,10,0,
  	12,0,31,9,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,
  	5,4,5,48,8,5,11,5,12,5,49,1,5,1,5,1,6,1,6,5,6,56,8,6,10,6,12,6,59,9,6,
  	1,7,1,7,5,7,63,8,7,10,7,12,7,66,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,
  	9,4,9,77,8,9,11,9,12,9,78,1,10,1,10,1,10,1,10,1,10,0,0,11,3,1,5,2,7,3,
  	9,4,11,5,13,6,15,7,17,8,19,9,21,10,23,11,3,0,1,2,4,2,0,65,90,97,122,3,
  	0,48,57,65,90,97,122,3,0,9,10,13,13,32,32,1,0,124,124,88,0,3,1,0,0,0,
  	0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,1,15,1,
  	0,0,0,1,17,1,0,0,0,1,19,1,0,0,0,2,21,1,0,0,0,2,23,1,0,0,0,3,25,1,0,0,
  	0,5,32,1,0,0,0,7,34,1,0,0,0,9,39,1,0,0,0,11,43,1,0,0,0,13,47,1,0,0,0,
  	15,53,1,0,0,0,17,60,1,0,0,0,19,69,1,0,0,0,21,76,1,0,0,0,23,80,1,0,0,0,
  	25,29,7,0,0,0,26,28,7,1,0,0,27,26,1,0,0,0,28,31,1,0,0,0,29,27,1,0,0,0,
  	29,30,1,0,0,0,30,4,1,0,0,0,31,29,1,0,0,0,32,33,5,58,0,0,33,6,1,0,0,0,
  	34,35,5,123,0,0,35,36,5,124,0,0,36,37,1,0,0,0,37,38,6,2,0,0,38,8,1,0,
  	0,0,39,40,5,37,0,0,40,41,1,0,0,0,41,42,6,3,1,0,42,10,1,0,0,0,43,44,5,
  	61,0,0,44,45,5,62,0,0,45,12,1,0,0,0,46,48,7,2,0,0,47,46,1,0,0,0,48,49,
  	1,0,0,0,49,47,1,0,0,0,49,50,1,0,0,0,50,51,1,0,0,0,51,52,6,5,2,0,52,14,
  	1,0,0,0,53,57,7,0,0,0,54,56,7,1,0,0,55,54,1,0,0,0,56,59,1,0,0,0,57,55,
  	1,0,0,0,57,58,1,0,0,0,58,16,1,0,0,0,59,57,1,0,0,0,60,64,7,0,0,0,61,63,
  	7,1,0,0,62,61,1,0,0,0,63,66,1,0,0,0,64,62,1,0,0,0,64,65,1,0,0,0,65,67,
  	1,0,0,0,66,64,1,0,0,0,67,68,1,0,0,0,68,18,1,0,0,0,69,70,5,37,0,0,70,71,
  	1,0,0,0,71,72,6,8,3,0,72,20,1,0,0,0,73,77,8,3,0,0,74,75,5,92,0,0,75,77,
  	5,124,0,0,76,73,1,0,0,0,76,74,1,0,0,0,77,78,1,0,0,0,78,76,1,0,0,0,78,
  	79,1,0,0,0,79,22,1,0,0,0,80,81,5,124,0,0,81,82,5,125,0,0,82,83,1,0,0,
  	0,83,84,6,10,3,0,84,24,1,0,0,0,9,0,1,2,29,49,57,64,76,78,4,2,2,0,2,1,
  	0,6,0,0,2,0,0
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
