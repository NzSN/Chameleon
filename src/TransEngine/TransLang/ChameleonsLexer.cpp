
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
      "TARGET_TAG", "RULE_TAG", "STRATEGY_TAG", "WHERE", "IDENTIFIER", "COLON", 
      "OPENBRACE", "TRANSFORM", "WS", "CODEBYTES", "CLOSEBRACE", "WHERE_EXPR_SEPERATOR", 
      "LOGICOP", "ORDEROP", "ASSIGN", "LBRACE", "RBRACE", "COMMA", "STRING", 
      "TERM_VAR", "WS_WHERE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "PROGRAM", "WHERE_CLAUSE"
    },
    std::vector<std::string>{
      "", "'TARGET:'", "'RULES:'", "'STRATEGIES'", "'where'", "", "':'", 
      "'{|'", "'=>'", "", "", "'|}'", "';'", "", "", "':='", "'('", "')'", 
      "','"
    },
    std::vector<std::string>{
      "", "TARGET_TAG", "RULE_TAG", "STRATEGY_TAG", "WHERE", "IDENTIFIER", 
      "COLON", "OPENBRACE", "TRANSFORM", "WS", "CODEBYTES", "CLOSEBRACE", 
      "WHERE_EXPR_SEPERATOR", "LOGICOP", "ORDEROP", "ASSIGN", "LBRACE", 
      "RBRACE", "COMMA", "STRING", "TERM_VAR", "WS_WHERE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,21,163,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,
  	7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,
  	7,20,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,4,1,4,5,4,82,8,4,10,4,12,4,85,9,4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,
  	1,7,1,7,1,8,4,8,98,8,8,11,8,12,8,99,1,8,1,8,1,9,1,9,1,9,4,9,107,8,9,11,
  	9,12,9,108,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,3,12,126,8,12,1,13,1,13,1,13,1,13,1,13,3,13,133,8,13,1,
  	14,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,4,18,146,8,18,11,
  	18,12,18,147,1,18,1,18,1,19,4,19,153,8,19,11,19,12,19,154,1,20,4,20,158,
  	8,20,11,20,12,20,159,1,20,1,20,0,0,21,3,1,5,2,7,3,9,4,11,5,13,6,15,7,
  	17,8,19,9,21,10,23,11,25,12,27,13,29,14,31,15,33,16,35,17,37,18,39,19,
  	41,20,43,21,3,0,1,2,5,2,0,65,90,97,122,3,0,48,57,65,90,97,122,3,0,9,10,
  	13,13,32,32,1,0,124,124,4,0,32,32,48,57,65,90,97,122,171,0,3,1,0,0,0,
  	0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,
  	0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,1,21,1,0,0,0,1,23,1,0,0,0,2,25,1,0,0,
  	0,2,27,1,0,0,0,2,29,1,0,0,0,2,31,1,0,0,0,2,33,1,0,0,0,2,35,1,0,0,0,2,
  	37,1,0,0,0,2,39,1,0,0,0,2,41,1,0,0,0,2,43,1,0,0,0,3,45,1,0,0,0,5,53,1,
  	0,0,0,7,60,1,0,0,0,9,71,1,0,0,0,11,79,1,0,0,0,13,86,1,0,0,0,15,88,1,0,
  	0,0,17,93,1,0,0,0,19,97,1,0,0,0,21,106,1,0,0,0,23,110,1,0,0,0,25,115,
  	1,0,0,0,27,125,1,0,0,0,29,132,1,0,0,0,31,134,1,0,0,0,33,137,1,0,0,0,35,
  	139,1,0,0,0,37,141,1,0,0,0,39,143,1,0,0,0,41,152,1,0,0,0,43,157,1,0,0,
  	0,45,46,5,84,0,0,46,47,5,65,0,0,47,48,5,82,0,0,48,49,5,71,0,0,49,50,5,
  	69,0,0,50,51,5,84,0,0,51,52,5,58,0,0,52,4,1,0,0,0,53,54,5,82,0,0,54,55,
  	5,85,0,0,55,56,5,76,0,0,56,57,5,69,0,0,57,58,5,83,0,0,58,59,5,58,0,0,
  	59,6,1,0,0,0,60,61,5,83,0,0,61,62,5,84,0,0,62,63,5,82,0,0,63,64,5,65,
  	0,0,64,65,5,84,0,0,65,66,5,69,0,0,66,67,5,71,0,0,67,68,5,73,0,0,68,69,
  	5,69,0,0,69,70,5,83,0,0,70,8,1,0,0,0,71,72,5,119,0,0,72,73,5,104,0,0,
  	73,74,5,101,0,0,74,75,5,114,0,0,75,76,5,101,0,0,76,77,1,0,0,0,77,78,6,
  	3,0,0,78,10,1,0,0,0,79,83,7,0,0,0,80,82,7,1,0,0,81,80,1,0,0,0,82,85,1,
  	0,0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,12,1,0,0,0,85,83,1,0,0,0,86,87,5,
  	58,0,0,87,14,1,0,0,0,88,89,5,123,0,0,89,90,5,124,0,0,90,91,1,0,0,0,91,
  	92,6,6,1,0,92,16,1,0,0,0,93,94,5,61,0,0,94,95,5,62,0,0,95,18,1,0,0,0,
  	96,98,7,2,0,0,97,96,1,0,0,0,98,99,1,0,0,0,99,97,1,0,0,0,99,100,1,0,0,
  	0,100,101,1,0,0,0,101,102,6,8,2,0,102,20,1,0,0,0,103,107,8,3,0,0,104,
  	105,5,92,0,0,105,107,5,124,0,0,106,103,1,0,0,0,106,104,1,0,0,0,107,108,
  	1,0,0,0,108,106,1,0,0,0,108,109,1,0,0,0,109,22,1,0,0,0,110,111,5,124,
  	0,0,111,112,5,125,0,0,112,113,1,0,0,0,113,114,6,10,3,0,114,24,1,0,0,0,
  	115,116,5,59,0,0,116,26,1,0,0,0,117,118,5,65,0,0,118,119,5,78,0,0,119,
  	126,5,68,0,0,120,121,5,79,0,0,121,126,5,82,0,0,122,123,5,78,0,0,123,124,
  	5,79,0,0,124,126,5,84,0,0,125,117,1,0,0,0,125,120,1,0,0,0,125,122,1,0,
  	0,0,126,28,1,0,0,0,127,133,2,60,62,0,128,129,5,60,0,0,129,133,5,61,0,
  	0,130,131,5,62,0,0,131,133,5,61,0,0,132,127,1,0,0,0,132,128,1,0,0,0,132,
  	130,1,0,0,0,133,30,1,0,0,0,134,135,5,58,0,0,135,136,5,61,0,0,136,32,1,
  	0,0,0,137,138,5,40,0,0,138,34,1,0,0,0,139,140,5,41,0,0,140,36,1,0,0,0,
  	141,142,5,44,0,0,142,38,1,0,0,0,143,145,5,34,0,0,144,146,7,4,0,0,145,
  	144,1,0,0,0,146,147,1,0,0,0,147,145,1,0,0,0,147,148,1,0,0,0,148,149,1,
  	0,0,0,149,150,5,34,0,0,150,40,1,0,0,0,151,153,7,0,0,0,152,151,1,0,0,0,
  	153,154,1,0,0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,42,1,0,0,0,156,158,
  	7,2,0,0,157,156,1,0,0,0,158,159,1,0,0,0,159,157,1,0,0,0,159,160,1,0,0,
  	0,160,161,1,0,0,0,161,162,6,20,2,0,162,44,1,0,0,0,12,0,1,2,83,99,106,
  	108,125,132,147,154,159,4,2,2,0,2,1,0,6,0,0,2,0,0
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
