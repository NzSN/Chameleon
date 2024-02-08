
// Generated from ./TestLang.g4 by ANTLR 4.13.0


#include "TestLangListener.h"

#include "TestLangParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct TestLangParserStaticData final {
  TestLangParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TestLangParserStaticData(const TestLangParserStaticData&) = delete;
  TestLangParserStaticData(TestLangParserStaticData&&) = delete;
  TestLangParserStaticData& operator=(const TestLangParserStaticData&) = delete;
  TestLangParserStaticData& operator=(TestLangParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag testlangParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
TestLangParserStaticData *testlangParserStaticData = nullptr;

void testlangParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (testlangParserStaticData != nullptr) {
    return;
  }
#else
  assert(testlangParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TestLangParserStaticData>(
    std::vector<std::string>{
      "prog", "expr"
    },
    std::vector<std::string>{
      "", "'*'", "'/'", "'+'", "'-'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "NEWLINE", "INT", "PLACEHOLDER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,10,27,2,0,7,0,2,1,7,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,14,
  	8,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,22,8,1,10,1,12,1,25,9,1,1,1,0,1,2,2,0,
  	2,0,2,1,0,1,2,1,0,3,4,28,0,4,1,0,0,0,2,13,1,0,0,0,4,5,3,2,1,0,5,1,1,0,
  	0,0,6,7,6,1,-1,0,7,14,5,8,0,0,8,14,5,9,0,0,9,10,5,5,0,0,10,11,3,2,1,0,
  	11,12,5,6,0,0,12,14,1,0,0,0,13,6,1,0,0,0,13,8,1,0,0,0,13,9,1,0,0,0,14,
  	23,1,0,0,0,15,16,10,5,0,0,16,17,7,0,0,0,17,22,3,2,1,6,18,19,10,4,0,0,
  	19,20,7,1,0,0,20,22,3,2,1,5,21,15,1,0,0,0,21,18,1,0,0,0,22,25,1,0,0,0,
  	23,21,1,0,0,0,23,24,1,0,0,0,24,3,1,0,0,0,25,23,1,0,0,0,3,13,21,23
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  testlangParserStaticData = staticData.release();
}

}

TestLangParser::TestLangParser(TokenStream *input) : TestLangParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

TestLangParser::TestLangParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  TestLangParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *testlangParserStaticData->atn, testlangParserStaticData->decisionToDFA, testlangParserStaticData->sharedContextCache, options);
}

TestLangParser::~TestLangParser() {
  delete _interpreter;
}

const atn::ATN& TestLangParser::getATN() const {
  return *testlangParserStaticData->atn;
}

std::string TestLangParser::getGrammarFileName() const {
  return "TestLang.g4";
}

const std::vector<std::string>& TestLangParser::getRuleNames() const {
  return testlangParserStaticData->ruleNames;
}

const dfa::Vocabulary& TestLangParser::getVocabulary() const {
  return testlangParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TestLangParser::getSerializedATN() const {
  return testlangParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

TestLangParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TestLangParser::ExprContext* TestLangParser::ProgContext::expr() {
  return getRuleContext<TestLangParser::ExprContext>(0);
}


size_t TestLangParser::ProgContext::getRuleIndex() const {
  return TestLangParser::RuleProg;
}

void TestLangParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TestLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void TestLangParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TestLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}

TestLangParser::ProgContext* TestLangParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, TestLangParser::RuleProg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(4);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

TestLangParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TestLangParser::ExprContext::INT() {
  return getToken(TestLangParser::INT, 0);
}

tree::TerminalNode* TestLangParser::ExprContext::PLACEHOLDER() {
  return getToken(TestLangParser::PLACEHOLDER, 0);
}

std::vector<TestLangParser::ExprContext *> TestLangParser::ExprContext::expr() {
  return getRuleContexts<TestLangParser::ExprContext>();
}

TestLangParser::ExprContext* TestLangParser::ExprContext::expr(size_t i) {
  return getRuleContext<TestLangParser::ExprContext>(i);
}


size_t TestLangParser::ExprContext::getRuleIndex() const {
  return TestLangParser::RuleExpr;
}

void TestLangParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TestLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void TestLangParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TestLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


TestLangParser::ExprContext* TestLangParser::expr() {
   return expr(0);
}

TestLangParser::ExprContext* TestLangParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  TestLangParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  TestLangParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, TestLangParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(13);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TestLangParser::INT: {
        setState(7);
        match(TestLangParser::INT);
        break;
      }

      case TestLangParser::PLACEHOLDER: {
        setState(8);
        match(TestLangParser::PLACEHOLDER);
        break;
      }

      case TestLangParser::T__4: {
        setState(9);
        match(TestLangParser::T__4);
        setState(10);
        expr(0);
        setState(11);
        match(TestLangParser::T__5);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(23);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(21);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(15);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(16);
          _la = _input->LA(1);
          if (!(_la == TestLangParser::T__0

          || _la == TestLangParser::T__1)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(17);
          expr(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(18);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(19);
          _la = _input->LA(1);
          if (!(_la == TestLangParser::T__2

          || _la == TestLangParser::T__3)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(20);
          expr(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(25);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool TestLangParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool TestLangParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void TestLangParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  testlangParserInitialize();
#else
  ::antlr4::internal::call_once(testlangParserOnceFlag, testlangParserInitialize);
#endif
}
