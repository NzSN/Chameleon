
// Generated from ./ChameleonsParser.g4 by ANTLR 4.13.1


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
      "prog", "targetSection", "ruleSection", "strategySection", "rewriteRules", 
      "rewriteRule", "sourcePattern", "targetPattern", "condExprs", "condExpr"
    },
    std::vector<std::string>{
      "", "'TARGET:'", "'Rules:'", "'STRATEGIES'", "'where'", "", "", "", 
      "", "':'", "'{|'", "", "'=>'", "", "", "'|}'"
    },
    std::vector<std::string>{
      "", "TARGET_TAG", "RULE_TAG", "STRATEGY_TAG", "WHERE", "LOGICOP", 
      "ORDEROP", "NUMBER", "IDENTIFIER", "COLON", "OPENBRACE", "TERM_VAR", 
      "TRANSFORM", "WS", "CODEBYTES", "CLOSEBRACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,15,87,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,28,8,0,1,1,1,1,1,
  	1,1,2,1,2,1,2,1,3,1,3,1,4,1,4,1,4,1,4,3,4,42,8,4,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,
  	5,66,8,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,1,8,3,8,77,8,8,1,9,1,9,1,9,1,
  	9,1,9,1,9,3,9,85,8,9,1,9,0,0,10,0,2,4,6,8,10,12,14,16,18,0,0,81,0,27,
  	1,0,0,0,2,29,1,0,0,0,4,32,1,0,0,0,6,35,1,0,0,0,8,41,1,0,0,0,10,65,1,0,
  	0,0,12,67,1,0,0,0,14,69,1,0,0,0,16,76,1,0,0,0,18,84,1,0,0,0,20,21,3,2,
  	1,0,21,22,3,4,2,0,22,28,1,0,0,0,23,24,3,2,1,0,24,25,3,4,2,0,25,26,3,6,
  	3,0,26,28,1,0,0,0,27,20,1,0,0,0,27,23,1,0,0,0,28,1,1,0,0,0,29,30,5,1,
  	0,0,30,31,5,8,0,0,31,3,1,0,0,0,32,33,5,2,0,0,33,34,3,8,4,0,34,5,1,0,0,
  	0,35,36,5,3,0,0,36,7,1,0,0,0,37,42,3,10,5,0,38,39,3,10,5,0,39,40,3,8,
  	4,0,40,42,1,0,0,0,41,37,1,0,0,0,41,38,1,0,0,0,42,9,1,0,0,0,43,44,5,8,
  	0,0,44,45,5,9,0,0,45,46,5,10,0,0,46,47,3,12,6,0,47,48,5,15,0,0,48,49,
  	5,12,0,0,49,50,5,10,0,0,50,51,3,14,7,0,51,52,5,15,0,0,52,66,1,0,0,0,53,
  	54,5,8,0,0,54,55,5,9,0,0,55,56,5,10,0,0,56,57,3,12,6,0,57,58,5,15,0,0,
  	58,59,5,12,0,0,59,60,5,10,0,0,60,61,3,14,7,0,61,62,5,15,0,0,62,63,5,4,
  	0,0,63,64,3,16,8,0,64,66,1,0,0,0,65,43,1,0,0,0,65,53,1,0,0,0,66,11,1,
  	0,0,0,67,68,5,14,0,0,68,13,1,0,0,0,69,70,5,14,0,0,70,15,1,0,0,0,71,77,
  	3,18,9,0,72,73,3,18,9,0,73,74,5,5,0,0,74,75,3,16,8,0,75,77,1,0,0,0,76,
  	71,1,0,0,0,76,72,1,0,0,0,77,17,1,0,0,0,78,79,5,11,0,0,79,80,5,6,0,0,80,
  	85,5,11,0,0,81,82,5,11,0,0,82,83,5,6,0,0,83,85,5,7,0,0,84,78,1,0,0,0,
  	84,81,1,0,0,0,85,19,1,0,0,0,5,27,41,65,76,84
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


//----------------- ProgContext ------------------------------------------------------------------

ChameleonsParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChameleonsParser::TargetSectionContext* ChameleonsParser::ProgContext::targetSection() {
  return getRuleContext<ChameleonsParser::TargetSectionContext>(0);
}

ChameleonsParser::RuleSectionContext* ChameleonsParser::ProgContext::ruleSection() {
  return getRuleContext<ChameleonsParser::RuleSectionContext>(0);
}

ChameleonsParser::StrategySectionContext* ChameleonsParser::ProgContext::strategySection() {
  return getRuleContext<ChameleonsParser::StrategySectionContext>(0);
}


size_t ChameleonsParser::ProgContext::getRuleIndex() const {
  return ChameleonsParser::RuleProg;
}

void ChameleonsParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void ChameleonsParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}

ChameleonsParser::ProgContext* ChameleonsParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, ChameleonsParser::RuleProg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(27);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(20);
      targetSection();
      setState(21);
      ruleSection();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(23);
      targetSection();
      setState(24);
      ruleSection();
      setState(25);
      strategySection();
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

//----------------- TargetSectionContext ------------------------------------------------------------------

ChameleonsParser::TargetSectionContext::TargetSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::TargetSectionContext::TARGET_TAG() {
  return getToken(ChameleonsParser::TARGET_TAG, 0);
}

tree::TerminalNode* ChameleonsParser::TargetSectionContext::IDENTIFIER() {
  return getToken(ChameleonsParser::IDENTIFIER, 0);
}


size_t ChameleonsParser::TargetSectionContext::getRuleIndex() const {
  return ChameleonsParser::RuleTargetSection;
}

void ChameleonsParser::TargetSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTargetSection(this);
}

void ChameleonsParser::TargetSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTargetSection(this);
}

ChameleonsParser::TargetSectionContext* ChameleonsParser::targetSection() {
  TargetSectionContext *_localctx = _tracker.createInstance<TargetSectionContext>(_ctx, getState());
  enterRule(_localctx, 2, ChameleonsParser::RuleTargetSection);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(29);
    match(ChameleonsParser::TARGET_TAG);
    setState(30);
    match(ChameleonsParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleSectionContext ------------------------------------------------------------------

ChameleonsParser::RuleSectionContext::RuleSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::RuleSectionContext::RULE_TAG() {
  return getToken(ChameleonsParser::RULE_TAG, 0);
}

ChameleonsParser::RewriteRulesContext* ChameleonsParser::RuleSectionContext::rewriteRules() {
  return getRuleContext<ChameleonsParser::RewriteRulesContext>(0);
}


size_t ChameleonsParser::RuleSectionContext::getRuleIndex() const {
  return ChameleonsParser::RuleRuleSection;
}

void ChameleonsParser::RuleSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleSection(this);
}

void ChameleonsParser::RuleSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleSection(this);
}

ChameleonsParser::RuleSectionContext* ChameleonsParser::ruleSection() {
  RuleSectionContext *_localctx = _tracker.createInstance<RuleSectionContext>(_ctx, getState());
  enterRule(_localctx, 4, ChameleonsParser::RuleRuleSection);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    match(ChameleonsParser::RULE_TAG);
    setState(33);
    rewriteRules();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StrategySectionContext ------------------------------------------------------------------

ChameleonsParser::StrategySectionContext::StrategySectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::StrategySectionContext::STRATEGY_TAG() {
  return getToken(ChameleonsParser::STRATEGY_TAG, 0);
}


size_t ChameleonsParser::StrategySectionContext::getRuleIndex() const {
  return ChameleonsParser::RuleStrategySection;
}

void ChameleonsParser::StrategySectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrategySection(this);
}

void ChameleonsParser::StrategySectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrategySection(this);
}

ChameleonsParser::StrategySectionContext* ChameleonsParser::strategySection() {
  StrategySectionContext *_localctx = _tracker.createInstance<StrategySectionContext>(_ctx, getState());
  enterRule(_localctx, 6, ChameleonsParser::RuleStrategySection);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(35);
    match(ChameleonsParser::STRATEGY_TAG);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RewriteRulesContext ------------------------------------------------------------------

ChameleonsParser::RewriteRulesContext::RewriteRulesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChameleonsParser::RewriteRuleContext* ChameleonsParser::RewriteRulesContext::rewriteRule() {
  return getRuleContext<ChameleonsParser::RewriteRuleContext>(0);
}

ChameleonsParser::RewriteRulesContext* ChameleonsParser::RewriteRulesContext::rewriteRules() {
  return getRuleContext<ChameleonsParser::RewriteRulesContext>(0);
}


size_t ChameleonsParser::RewriteRulesContext::getRuleIndex() const {
  return ChameleonsParser::RuleRewriteRules;
}

void ChameleonsParser::RewriteRulesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRewriteRules(this);
}

void ChameleonsParser::RewriteRulesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRewriteRules(this);
}

ChameleonsParser::RewriteRulesContext* ChameleonsParser::rewriteRules() {
  RewriteRulesContext *_localctx = _tracker.createInstance<RewriteRulesContext>(_ctx, getState());
  enterRule(_localctx, 8, ChameleonsParser::RuleRewriteRules);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(41);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(37);
      rewriteRule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(38);
      rewriteRule();
      setState(39);
      rewriteRules();
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

//----------------- RewriteRuleContext ------------------------------------------------------------------

ChameleonsParser::RewriteRuleContext::RewriteRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::RewriteRuleContext::IDENTIFIER() {
  return getToken(ChameleonsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChameleonsParser::RewriteRuleContext::COLON() {
  return getToken(ChameleonsParser::COLON, 0);
}

std::vector<tree::TerminalNode *> ChameleonsParser::RewriteRuleContext::OPENBRACE() {
  return getTokens(ChameleonsParser::OPENBRACE);
}

tree::TerminalNode* ChameleonsParser::RewriteRuleContext::OPENBRACE(size_t i) {
  return getToken(ChameleonsParser::OPENBRACE, i);
}

ChameleonsParser::SourcePatternContext* ChameleonsParser::RewriteRuleContext::sourcePattern() {
  return getRuleContext<ChameleonsParser::SourcePatternContext>(0);
}

std::vector<tree::TerminalNode *> ChameleonsParser::RewriteRuleContext::CLOSEBRACE() {
  return getTokens(ChameleonsParser::CLOSEBRACE);
}

tree::TerminalNode* ChameleonsParser::RewriteRuleContext::CLOSEBRACE(size_t i) {
  return getToken(ChameleonsParser::CLOSEBRACE, i);
}

tree::TerminalNode* ChameleonsParser::RewriteRuleContext::TRANSFORM() {
  return getToken(ChameleonsParser::TRANSFORM, 0);
}

ChameleonsParser::TargetPatternContext* ChameleonsParser::RewriteRuleContext::targetPattern() {
  return getRuleContext<ChameleonsParser::TargetPatternContext>(0);
}

tree::TerminalNode* ChameleonsParser::RewriteRuleContext::WHERE() {
  return getToken(ChameleonsParser::WHERE, 0);
}

ChameleonsParser::CondExprsContext* ChameleonsParser::RewriteRuleContext::condExprs() {
  return getRuleContext<ChameleonsParser::CondExprsContext>(0);
}


size_t ChameleonsParser::RewriteRuleContext::getRuleIndex() const {
  return ChameleonsParser::RuleRewriteRule;
}

void ChameleonsParser::RewriteRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRewriteRule(this);
}

void ChameleonsParser::RewriteRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRewriteRule(this);
}

ChameleonsParser::RewriteRuleContext* ChameleonsParser::rewriteRule() {
  RewriteRuleContext *_localctx = _tracker.createInstance<RewriteRuleContext>(_ctx, getState());
  enterRule(_localctx, 10, ChameleonsParser::RuleRewriteRule);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(65);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(43);
      match(ChameleonsParser::IDENTIFIER);
      setState(44);
      match(ChameleonsParser::COLON);
      setState(45);
      match(ChameleonsParser::OPENBRACE);
      setState(46);
      sourcePattern();
      setState(47);
      match(ChameleonsParser::CLOSEBRACE);
      setState(48);
      match(ChameleonsParser::TRANSFORM);
      setState(49);
      match(ChameleonsParser::OPENBRACE);
      setState(50);
      targetPattern();
      setState(51);
      match(ChameleonsParser::CLOSEBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(53);
      match(ChameleonsParser::IDENTIFIER);
      setState(54);
      match(ChameleonsParser::COLON);
      setState(55);
      match(ChameleonsParser::OPENBRACE);
      setState(56);
      sourcePattern();
      setState(57);
      match(ChameleonsParser::CLOSEBRACE);
      setState(58);
      match(ChameleonsParser::TRANSFORM);
      setState(59);
      match(ChameleonsParser::OPENBRACE);
      setState(60);
      targetPattern();
      setState(61);
      match(ChameleonsParser::CLOSEBRACE);
      setState(62);
      match(ChameleonsParser::WHERE);
      setState(63);
      condExprs();
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

//----------------- SourcePatternContext ------------------------------------------------------------------

ChameleonsParser::SourcePatternContext::SourcePatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::SourcePatternContext::CODEBYTES() {
  return getToken(ChameleonsParser::CODEBYTES, 0);
}


size_t ChameleonsParser::SourcePatternContext::getRuleIndex() const {
  return ChameleonsParser::RuleSourcePattern;
}

void ChameleonsParser::SourcePatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourcePattern(this);
}

void ChameleonsParser::SourcePatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourcePattern(this);
}

ChameleonsParser::SourcePatternContext* ChameleonsParser::sourcePattern() {
  SourcePatternContext *_localctx = _tracker.createInstance<SourcePatternContext>(_ctx, getState());
  enterRule(_localctx, 12, ChameleonsParser::RuleSourcePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    match(ChameleonsParser::CODEBYTES);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TargetPatternContext ------------------------------------------------------------------

ChameleonsParser::TargetPatternContext::TargetPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChameleonsParser::TargetPatternContext::CODEBYTES() {
  return getToken(ChameleonsParser::CODEBYTES, 0);
}


size_t ChameleonsParser::TargetPatternContext::getRuleIndex() const {
  return ChameleonsParser::RuleTargetPattern;
}

void ChameleonsParser::TargetPatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTargetPattern(this);
}

void ChameleonsParser::TargetPatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTargetPattern(this);
}

ChameleonsParser::TargetPatternContext* ChameleonsParser::targetPattern() {
  TargetPatternContext *_localctx = _tracker.createInstance<TargetPatternContext>(_ctx, getState());
  enterRule(_localctx, 14, ChameleonsParser::RuleTargetPattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(ChameleonsParser::CODEBYTES);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondExprsContext ------------------------------------------------------------------

ChameleonsParser::CondExprsContext::CondExprsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChameleonsParser::CondExprContext* ChameleonsParser::CondExprsContext::condExpr() {
  return getRuleContext<ChameleonsParser::CondExprContext>(0);
}

tree::TerminalNode* ChameleonsParser::CondExprsContext::LOGICOP() {
  return getToken(ChameleonsParser::LOGICOP, 0);
}

ChameleonsParser::CondExprsContext* ChameleonsParser::CondExprsContext::condExprs() {
  return getRuleContext<ChameleonsParser::CondExprsContext>(0);
}


size_t ChameleonsParser::CondExprsContext::getRuleIndex() const {
  return ChameleonsParser::RuleCondExprs;
}

void ChameleonsParser::CondExprsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondExprs(this);
}

void ChameleonsParser::CondExprsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondExprs(this);
}

ChameleonsParser::CondExprsContext* ChameleonsParser::condExprs() {
  CondExprsContext *_localctx = _tracker.createInstance<CondExprsContext>(_ctx, getState());
  enterRule(_localctx, 16, ChameleonsParser::RuleCondExprs);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(71);
      condExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(72);
      condExpr();
      setState(73);
      match(ChameleonsParser::LOGICOP);
      setState(74);
      condExprs();
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

//----------------- CondExprContext ------------------------------------------------------------------

ChameleonsParser::CondExprContext::CondExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ChameleonsParser::CondExprContext::TERM_VAR() {
  return getTokens(ChameleonsParser::TERM_VAR);
}

tree::TerminalNode* ChameleonsParser::CondExprContext::TERM_VAR(size_t i) {
  return getToken(ChameleonsParser::TERM_VAR, i);
}

tree::TerminalNode* ChameleonsParser::CondExprContext::ORDEROP() {
  return getToken(ChameleonsParser::ORDEROP, 0);
}

tree::TerminalNode* ChameleonsParser::CondExprContext::NUMBER() {
  return getToken(ChameleonsParser::NUMBER, 0);
}


size_t ChameleonsParser::CondExprContext::getRuleIndex() const {
  return ChameleonsParser::RuleCondExpr;
}

void ChameleonsParser::CondExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondExpr(this);
}

void ChameleonsParser::CondExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ChameleonsParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondExpr(this);
}

ChameleonsParser::CondExprContext* ChameleonsParser::condExpr() {
  CondExprContext *_localctx = _tracker.createInstance<CondExprContext>(_ctx, getState());
  enterRule(_localctx, 18, ChameleonsParser::RuleCondExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(84);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(78);
      match(ChameleonsParser::TERM_VAR);
      setState(79);
      match(ChameleonsParser::ORDEROP);
      setState(80);
      match(ChameleonsParser::TERM_VAR);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(81);
      match(ChameleonsParser::TERM_VAR);
      setState(82);
      match(ChameleonsParser::ORDEROP);
      setState(83);
      match(ChameleonsParser::NUMBER);
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

void ChameleonsParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chameleonsparserParserInitialize();
#else
  ::antlr4::internal::call_once(chameleonsparserParserOnceFlag, chameleonsparserParserInitialize);
#endif
}
