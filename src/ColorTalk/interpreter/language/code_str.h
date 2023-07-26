
#ifndef CODE_STR_H
#define CODE_STR_H

#include <string>

using std::string;

template<typename C>
concept CodeStrT  = requires(C c) {
  // Interface that gurantee that all escape in CodeString
  // are trim to it's original form. If there are no escaped
  // defined in your language then just return without any addition
  // processing.
  { c.withoutEscape() } -> std::convertible_to<string>;

  // Mapping to std::string which escape cahracter remain exists
  { c.toStr() } -> std::convertible_to<string>;
};

// A structure to contain Codes that
template<CodeStrT T>
class Code {
public:
  Code(T code): codebytes_{code} {}
  string codebytes() const
    { return codebytes_.withoutEscape(); }
private:
  const T codebytes_;
};

class CodeStr {
public:
  CodeStr(std::string codestr): code_string_{codestr} {}
  virtual string toStr() const;
  virtual string withoutEscape() const;
private:
  string code_string_;
};

using OriginCode = Code<CodeStr>;
using TargetCode = Code<CodeStr>;


#endif /* CODE_STR_H */
