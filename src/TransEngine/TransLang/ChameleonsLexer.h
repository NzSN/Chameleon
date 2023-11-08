
// Generated from ./ChameleonsLexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  ChameleonsLexer : public antlr4::Lexer {
public:
  enum {
    TARGET_TAG = 1, RULE_TAG = 2, STRATEGY_TAG = 3, WHERE = 4, LOGICOP = 5, 
    ORDEROP = 6, NUMBER = 7, IDENTIFIER = 8, COLON = 9, OPENBRACE = 10, 
    TERM_VAR = 11, TRANSFORM = 12, WS = 13, CODEBYTES = 14, CLOSEBRACE = 15
  };

  enum {
    PROGRAM = 1
  };

  explicit ChameleonsLexer(antlr4::CharStream *input);

  ~ChameleonsLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

