#include "utility.h"
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <type_traits>


namespace Utility {

std::string testLangRandomExpr(unsigned numOfOperands) {
  constexpr int NumOfOperators = 4;
  static std::string operators[] ={
    "+", "-", "*", "/"
  };

  if (numOfOperands == 0) return {};

  std::string sentence = std::to_string(*rc::gen::inRange(0, 100));
  --numOfOperands;
  if (numOfOperands == 0) {
    return sentence;
  } else {
    sentence += operators[*rc::gen::inRange(0, NumOfOperators)];
    sentence += testLangRandomExpr(numOfOperands);
    return sentence;
  }
}

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}


} // Utility
