#include "Expr.h"

namespace Chameleon {
namespace TransEngine {
namespace Expression {

bool Value::isBoolean(Value &v) {
  return IS_SAME_TYPE(Bool{}, v);
}

bool Value::isUnit(Value &v) {
  return IS_SAME_TYPE(Unit{}, v);
}

bool Value::isString(Value &v) {
  return IS_SAME_TYPE(String{}, v);
}

bool Value::isTerm(Value &v) {
  return IS_SAME_TYPE(Term, v);
}


} // Expression
} // TransEngine
} // Chameleon
