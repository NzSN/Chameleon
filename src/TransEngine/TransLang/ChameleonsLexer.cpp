
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
      "TARGET_TAG", "RULE_TAG", "STRATEGY_TAG", "WHERE", "LOGICOP", "ORDEROP", 
      "NUMBER", "IDENTIFIER", "COLON", "OPENBRACE", "TERM_VAR", "TRANSFORM", 
      "WS", "CODEBYTES", "CLOSEBRACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "PROGRAM"
    },
    std::vector<std::string>{
      "", "'TARGET:'", "'RULES:'", "'STRATEGIES'", "'where'", "", "", "", 
      "", "':'", "'{|'", "", "'=>'", "", "", "'|}'"
    },
    std::vector<std::string>{
      "", "TARGET_TAG", "RULE_TAG", "STRATEGY_TAG", "WHERE", "LOGICOP", 
      "ORDEROP", "NUMBER", "IDENTIFIER", "COLON", "OPENBRACE", "TERM_VAR", 
      "TRANSFORM", "WS", "CODEBYTES", "CLOSEBRACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,15,128,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,
  	2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,
  	13,2,14,7,14,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,73,8,4,1,5,1,5,1,5,1,5,1,5,3,5,
  	80,8,5,1,6,4,6,83,8,6,11,6,12,6,84,1,7,1,7,5,7,89,8,7,10,7,12,7,92,9,
  	7,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,10,1,10,4,10,103,8,10,11,10,12,10,104,
  	1,11,1,11,1,11,1,12,4,12,111,8,12,11,12,12,12,112,1,12,1,12,1,13,1,13,
  	1,13,4,13,120,8,13,11,13,12,13,121,1,14,1,14,1,14,1,14,1,14,0,0,15,2,
  	1,4,2,6,3,8,4,10,5,12,6,14,7,16,8,18,9,20,10,22,11,24,12,26,13,28,14,
  	30,15,2,0,1,5,1,0,48,57,2,0,65,90,97,122,3,0,48,57,65,90,97,122,3,0,9,
  	10,13,13,32,32,1,0,124,124,136,0,2,1,0,0,0,0,4,1,0,0,0,0,6,1,0,0,0,0,
  	8,1,0,0,0,0,10,1,0,0,0,0,12,1,0,0,0,0,14,1,0,0,0,0,16,1,0,0,0,0,18,1,
  	0,0,0,0,20,1,0,0,0,0,22,1,0,0,0,0,24,1,0,0,0,0,26,1,0,0,0,1,28,1,0,0,
  	0,1,30,1,0,0,0,2,32,1,0,0,0,4,40,1,0,0,0,6,47,1,0,0,0,8,58,1,0,0,0,10,
  	72,1,0,0,0,12,79,1,0,0,0,14,82,1,0,0,0,16,86,1,0,0,0,18,93,1,0,0,0,20,
  	95,1,0,0,0,22,100,1,0,0,0,24,106,1,0,0,0,26,110,1,0,0,0,28,119,1,0,0,
  	0,30,123,1,0,0,0,32,33,5,84,0,0,33,34,5,65,0,0,34,35,5,82,0,0,35,36,5,
  	71,0,0,36,37,5,69,0,0,37,38,5,84,0,0,38,39,5,58,0,0,39,3,1,0,0,0,40,41,
  	5,82,0,0,41,42,5,85,0,0,42,43,5,76,0,0,43,44,5,69,0,0,44,45,5,83,0,0,
  	45,46,5,58,0,0,46,5,1,0,0,0,47,48,5,83,0,0,48,49,5,84,0,0,49,50,5,82,
  	0,0,50,51,5,65,0,0,51,52,5,84,0,0,52,53,5,69,0,0,53,54,5,71,0,0,54,55,
  	5,73,0,0,55,56,5,69,0,0,56,57,5,83,0,0,57,7,1,0,0,0,58,59,5,119,0,0,59,
  	60,5,104,0,0,60,61,5,101,0,0,61,62,5,114,0,0,62,63,5,101,0,0,63,9,1,0,
  	0,0,64,65,5,65,0,0,65,66,5,78,0,0,66,73,5,68,0,0,67,68,5,79,0,0,68,73,
  	5,82,0,0,69,70,5,78,0,0,70,71,5,79,0,0,71,73,5,84,0,0,72,64,1,0,0,0,72,
  	67,1,0,0,0,72,69,1,0,0,0,73,11,1,0,0,0,74,80,2,60,62,0,75,76,5,60,0,0,
  	76,80,5,61,0,0,77,78,5,62,0,0,78,80,5,61,0,0,79,74,1,0,0,0,79,75,1,0,
  	0,0,79,77,1,0,0,0,80,13,1,0,0,0,81,83,7,0,0,0,82,81,1,0,0,0,83,84,1,0,
  	0,0,84,82,1,0,0,0,84,85,1,0,0,0,85,15,1,0,0,0,86,90,7,1,0,0,87,89,7,2,
  	0,0,88,87,1,0,0,0,89,92,1,0,0,0,90,88,1,0,0,0,90,91,1,0,0,0,91,17,1,0,
  	0,0,92,90,1,0,0,0,93,94,5,58,0,0,94,19,1,0,0,0,95,96,5,123,0,0,96,97,
  	5,124,0,0,97,98,1,0,0,0,98,99,6,9,0,0,99,21,1,0,0,0,100,102,5,37,0,0,
  	101,103,7,1,0,0,102,101,1,0,0,0,103,104,1,0,0,0,104,102,1,0,0,0,104,105,
  	1,0,0,0,105,23,1,0,0,0,106,107,5,61,0,0,107,108,5,62,0,0,108,25,1,0,0,
  	0,109,111,7,3,0,0,110,109,1,0,0,0,111,112,1,0,0,0,112,110,1,0,0,0,112,
  	113,1,0,0,0,113,114,1,0,0,0,114,115,6,12,1,0,115,27,1,0,0,0,116,120,8,
  	4,0,0,117,118,5,92,0,0,118,120,5,124,0,0,119,116,1,0,0,0,119,117,1,0,
  	0,0,120,121,1,0,0,0,121,119,1,0,0,0,121,122,1,0,0,0,122,29,1,0,0,0,123,
  	124,5,124,0,0,124,125,5,125,0,0,125,126,1,0,0,0,126,127,6,14,2,0,127,
  	31,1,0,0,0,10,0,1,72,79,84,90,104,112,119,121,3,2,1,0,6,0,0,2,0,0
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
