
// Generated from ChameleonsParser.g4 by ANTLR 4.13.0


#include "ChameleonsParserListener.h"

#include "ChameleonsParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ChameleonsParserStaticData final {
  ChameleonsParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ChameleonsParserStaticData(const ChameleonsParserStaticData&) = delete;
  ChameleonsParserStaticData(ChameleonsParserStaticData&&) = delete;
  ChameleonsParserStaticData& operator=(const ChameleonsParserStaticData&) = delete;
  ChameleonsParserStaticData& operator=(ChameleonsParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag chameleonsparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ChameleonsParserStaticData *chameleonsparserParserStaticData = nullptr;

void chameleonsparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chameleonsparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(chameleonsparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ChameleonsParserStaticData>(
    std::vector<std::string>{
      "migrate", "migrateRules", "migrateRule", "originCode", "targetCode"
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
  	4,1,7,33,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,1,0,1,0,1,1,1,1,1,1,
  	1,1,3,1,17,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,4,1,
  	4,1,4,0,0,5,0,2,4,6,8,0,0,28,0,10,1,0,0,0,2,16,1,0,0,0,4,18,1,0,0,0,6,
  	28,1,0,0,0,8,30,1,0,0,0,10,11,3,2,1,0,11,1,1,0,0,0,12,17,3,4,2,0,13,14,
  	3,4,2,0,14,15,3,2,1,0,15,17,1,0,0,0,16,12,1,0,0,0,16,13,1,0,0,0,17,3,
  	1,0,0,0,18,19,5,1,0,0,19,20,5,2,0,0,20,21,5,3,0,0,21,22,3,6,3,0,22,23,
  	5,7,0,0,23,24,5,4,0,0,24,25,5,3,0,0,25,26,3,8,4,0,26,27,5,7,0,0,27,5,
  	1,0,0,0,28,29,5,6,0,0,29,7,1,0,0,0,30,31,5,6,0,0,31,9,1,0,0,0,1,16
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chameleonsparserParserStaticData = staticData.release();
}

}

ChameleonsParser::ChameleonsParser(TokenStream *input) : ChameleonsParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ChameleonsParser::ChameleonsParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ChameleonsParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *chameleonsparserParserStaticData->atn, chameleonsparserParserStaticData->decisionToDFA, chameleonsparserParserStaticData->sharedContextCache, options);
}

ChameleonsParser::~ChameleonsParser() {
  delete _interpreter;
}

const atn::ATN& ChameleonsParser::getATN() const {
  return *chameleonsparserParserStaticData->atn;
}

std::string ChameleonsParser::getGrammarFileName() const {
  return "ChameleonsParser.g4";
}

const std::vector<std::string>& ChameleonsParser::getRuleNames() const {
  return chameleonsparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& ChameleonsParser::getVocabulary() const {
  return chameleonsparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ChameleonsParser::getSerializedATN() const {
  return chameleonsparserParserStaticData->serializedATN;
}


//----------------- MigrateContext ------------------------------------------------------------------

ChameleonsParser::MigrateContext::MigrateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChameleonsParser::MigrateRulesContext* ChameleonsParser::MigrateContext::migrateRules() {
  return getRuleContext<ChameleonsParser::MigrateRulesContext>(0);
}


size_t ChameleonsParser::MigrateContext::getRuleIndex() const {
  return ChameleonsParser::RuleMigrate;
}

void ChameleonsParser::MigrateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMigrate(this);
}

void ChameleonsParser::MigrateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMigrate(this);
}

ChameleonsParser::MigrateContext* ChameleonsParser::migrate() {
  MigrateContext *_localctx = _tracker.createInstance<MigrateContext>(_ctx, getState());
  enterRule(_localctx, 0, ChameleonsParser::RuleMigrate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(10);
    migrateRules();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MigrateRulesContext ------------------------------------------------------------------

ChameleonsParser::MigrateRulesContext::MigrateRulesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChameleonsParser::MigrateRuleContext* ChameleonsParser::MigrateRulesContext::migrateRule() {
  return getRuleContext<ChameleonsParser::MigrateRuleContext>(0);
}

ChameleonsParser::MigrateRulesContext* ChameleonsParser::MigrateRulesContext::migrateRules() {
  return getRuleContext<ChameleonsParser::MigrateRulesContext>(0);
}


size_t ChameleonsParser::MigrateRulesContext::getRuleIndex() const {
  return ChameleonsParser::RuleMigrateRules;
}

void ChameleonsParser::MigrateRulesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMigrateRules(this);
}

void ChameleonsParser::MigrateRulesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMigrateRules(this);
}

ChameleonsParser::MigrateRulesContext* ChameleonsParser::migrateRules() {
  MigrateRulesContext *_localctx = _tracker.createInstance<MigrateRulesContext>(_ctx, getState());
  enterRule(_localctx, 2, ChameleonsParser::RuleMigrateRules);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(16);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(12);
      migrateRule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(13);
      migrateRule();
      setState(14);
      migrateRules();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MigrateRuleContext ------------------------------------------------------------------

ChameleonsParser::MigrateRuleContext::MigrateRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::MigrateRuleContext::IDENTIFIER() {
  return getToken(ChameleonsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChameleonsParser::MigrateRuleContext::COLON() {
  return getToken(ChameleonsParser::COLON, 0);
}

std::vector<tree::TerminalNode *> ChameleonsParser::MigrateRuleContext::OPENBRACE() {
  return getTokens(ChameleonsParser::OPENBRACE);
}

tree::TerminalNode* ChameleonsParser::MigrateRuleContext::OPENBRACE(size_t i) {
  return getToken(ChameleonsParser::OPENBRACE, i);
}

ChameleonsParser::OriginCodeContext* ChameleonsParser::MigrateRuleContext::originCode() {
  return getRuleContext<ChameleonsParser::OriginCodeContext>(0);
}

std::vector<tree::TerminalNode *> ChameleonsParser::MigrateRuleContext::CLOSEBRACE() {
  return getTokens(ChameleonsParser::CLOSEBRACE);
}

tree::TerminalNode* ChameleonsParser::MigrateRuleContext::CLOSEBRACE(size_t i) {
  return getToken(ChameleonsParser::CLOSEBRACE, i);
}

tree::TerminalNode* ChameleonsParser::MigrateRuleContext::TRANSFORM() {
  return getToken(ChameleonsParser::TRANSFORM, 0);
}

ChameleonsParser::TargetCodeContext* ChameleonsParser::MigrateRuleContext::targetCode() {
  return getRuleContext<ChameleonsParser::TargetCodeContext>(0);
}


size_t ChameleonsParser::MigrateRuleContext::getRuleIndex() const {
  return ChameleonsParser::RuleMigrateRule;
}

void ChameleonsParser::MigrateRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMigrateRule(this);
}

void ChameleonsParser::MigrateRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMigrateRule(this);
}

ChameleonsParser::MigrateRuleContext* ChameleonsParser::migrateRule() {
  MigrateRuleContext *_localctx = _tracker.createInstance<MigrateRuleContext>(_ctx, getState());
  enterRule(_localctx, 4, ChameleonsParser::RuleMigrateRule);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    match(ChameleonsParser::IDENTIFIER);
    setState(19);
    match(ChameleonsParser::COLON);
    setState(20);
    match(ChameleonsParser::OPENBRACE);
    setState(21);
    originCode();
    setState(22);
    match(ChameleonsParser::CLOSEBRACE);
    setState(23);
    match(ChameleonsParser::TRANSFORM);
    setState(24);
    match(ChameleonsParser::OPENBRACE);
    setState(25);
    targetCode();
    setState(26);
    match(ChameleonsParser::CLOSEBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OriginCodeContext ------------------------------------------------------------------

ChameleonsParser::OriginCodeContext::OriginCodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::OriginCodeContext::CODEBYTES() {
  return getToken(ChameleonsParser::CODEBYTES, 0);
}


size_t ChameleonsParser::OriginCodeContext::getRuleIndex() const {
  return ChameleonsParser::RuleOriginCode;
}

void ChameleonsParser::OriginCodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginCode(this);
}

void ChameleonsParser::OriginCodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginCode(this);
}

ChameleonsParser::OriginCodeContext* ChameleonsParser::originCode() {
  OriginCodeContext *_localctx = _tracker.createInstance<OriginCodeContext>(_ctx, getState());
  enterRule(_localctx, 6, ChameleonsParser::RuleOriginCode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    match(ChameleonsParser::CODEBYTES);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TargetCodeContext ------------------------------------------------------------------

ChameleonsParser::TargetCodeContext::TargetCodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::TargetCodeContext::CODEBYTES() {
  return getToken(ChameleonsParser::CODEBYTES, 0);
}


size_t ChameleonsParser::TargetCodeContext::getRuleIndex() const {
  return ChameleonsParser::RuleTargetCode;
}

void ChameleonsParser::TargetCodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTargetCode(this);
}

void ChameleonsParser::TargetCodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTargetCode(this);
}

ChameleonsParser::TargetCodeContext* ChameleonsParser::targetCode() {
  TargetCodeContext *_localctx = _tracker.createInstance<TargetCodeContext>(_ctx, getState());
  enterRule(_localctx, 8, ChameleonsParser::RuleTargetCode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    match(ChameleonsParser::CODEBYTES);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void ChameleonsParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chameleonsparserParserInitialize();
#else
  ::antlr4::internal::call_once(chameleonsparserParserOnceFlag, chameleonsparserParserInitialize);
#endif
}
