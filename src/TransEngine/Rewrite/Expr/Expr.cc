#include "Expr.h"

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


} // Expression
} // TransEngine
