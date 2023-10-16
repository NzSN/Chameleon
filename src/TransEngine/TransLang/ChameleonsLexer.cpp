
// Generated from ./ChameleonsLexer.g4 by ANTLR 4.13.0


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
      "WHERE", "LOGICOP", "ORDEROP", "NUMBER", "IDENTIFIER", "COLON", "OPENBRACE", 
      "TERM_VAR", "TRANSFORM", "WS", "CODEBYTES", "CLOSEBRACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "PROGRAM"
    },
    std::vector<std::string>{
      "", "'where'", "", "", "", "", "':'", "'{|'", "", "'=>'", "", "", 
      "'|}'"
    },
    std::vector<std::string>{
      "", "WHERE", "LOGICOP", "ORDEROP", "NUMBER", "IDENTIFIER", "COLON", 
      "OPENBRACE", "TERM_VAR", "TRANSFORM", "WS", "CODEBYTES", "CLOSEBRACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,12,96,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,
  	6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,1,0,1,0,1,0,1,0,1,0,
  	1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,41,8,1,1,2,1,2,1,2,1,2,1,2,3,
  	2,48,8,2,1,3,4,3,51,8,3,11,3,12,3,52,1,4,1,4,5,4,57,8,4,10,4,12,4,60,
  	9,4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,4,7,71,8,7,11,7,12,7,72,1,8,1,
  	8,1,8,1,9,4,9,79,8,9,11,9,12,9,80,1,9,1,9,1,10,1,10,1,10,4,10,88,8,10,
  	11,10,12,10,89,1,11,1,11,1,11,1,11,1,11,0,0,12,2,1,4,2,6,3,8,4,10,5,12,
  	6,14,7,16,8,18,9,20,10,22,11,24,12,2,0,1,5,1,0,48,57,2,0,65,90,97,122,
  	3,0,48,57,65,90,97,122,3,0,9,10,13,13,32,32,1,0,124,124,104,0,2,1,0,0,
  	0,0,4,1,0,0,0,0,6,1,0,0,0,0,8,1,0,0,0,0,10,1,0,0,0,0,12,1,0,0,0,0,14,
  	1,0,0,0,0,16,1,0,0,0,0,18,1,0,0,0,0,20,1,0,0,0,1,22,1,0,0,0,1,24,1,0,
  	0,0,2,26,1,0,0,0,4,40,1,0,0,0,6,47,1,0,0,0,8,50,1,0,0,0,10,54,1,0,0,0,
  	12,61,1,0,0,0,14,63,1,0,0,0,16,68,1,0,0,0,18,74,1,0,0,0,20,78,1,0,0,0,
  	22,87,1,0,0,0,24,91,1,0,0,0,26,27,5,119,0,0,27,28,5,104,0,0,28,29,5,101,
  	0,0,29,30,5,114,0,0,30,31,5,101,0,0,31,3,1,0,0,0,32,33,5,65,0,0,33,34,
  	5,78,0,0,34,41,5,68,0,0,35,36,5,79,0,0,36,41,5,82,0,0,37,38,5,78,0,0,
  	38,39,5,79,0,0,39,41,5,84,0,0,40,32,1,0,0,0,40,35,1,0,0,0,40,37,1,0,0,
  	0,41,5,1,0,0,0,42,48,2,60,62,0,43,44,5,60,0,0,44,48,5,61,0,0,45,46,5,
  	62,0,0,46,48,5,61,0,0,47,42,1,0,0,0,47,43,1,0,0,0,47,45,1,0,0,0,48,7,
  	1,0,0,0,49,51,7,0,0,0,50,49,1,0,0,0,51,52,1,0,0,0,52,50,1,0,0,0,52,53,
  	1,0,0,0,53,9,1,0,0,0,54,58,7,1,0,0,55,57,7,2,0,0,56,55,1,0,0,0,57,60,
  	1,0,0,0,58,56,1,0,0,0,58,59,1,0,0,0,59,11,1,0,0,0,60,58,1,0,0,0,61,62,
  	5,58,0,0,62,13,1,0,0,0,63,64,5,123,0,0,64,65,5,124,0,0,65,66,1,0,0,0,
  	66,67,6,6,0,0,67,15,1,0,0,0,68,70,5,37,0,0,69,71,7,1,0,0,70,69,1,0,0,
  	0,71,72,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,73,17,1,0,0,0,74,75,5,61,
  	0,0,75,76,5,62,0,0,76,19,1,0,0,0,77,79,7,3,0,0,78,77,1,0,0,0,79,80,1,
  	0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,82,1,0,0,0,82,83,6,9,1,0,83,21,1,
  	0,0,0,84,88,8,4,0,0,85,86,5,92,0,0,86,88,5,124,0,0,87,84,1,0,0,0,87,85,
  	1,0,0,0,88,89,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,23,1,0,0,0,91,92,
  	5,124,0,0,92,93,5,125,0,0,93,94,1,0,0,0,94,95,6,11,2,0,95,25,1,0,0,0,
  	10,0,1,40,47,52,58,72,80,87,89,3,2,1,0,6,0,0,2,0,0
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
