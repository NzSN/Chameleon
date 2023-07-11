
#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <concepts>
#include <utility>

#include "antlr4-runtime.h"

using std::string;

namespace Rule {
namespace Interpreter {
namespace Language {

///////////////////////////////////////////////////////////////////////////////
//                                   Codes                                   //
///////////////////////////////////////////////////////////////////////////////
template<typename C>
concept CodeStrT  = requires(C c) {
    { c.withoutEscape() } -> std::convertible_to<string>;

    // Mapping to std::string which escape cahracter remain exists
    { c.toStr() } -> std::convertible_to<string>;
};

// A structure to contain Codes that
template<CodeStrT T>
class Code {
public:
    Code(T code): codeBytes_{code} {}
    string codeBytes() const
        { return codeBytes_.withoutEscape(); }
private:
    const T codeBytes_;
};

class CodeStr {
public:
    string toStr() const;
    string withoutEscape() const;
private:
    string codeString_;
};

using OriginCode = Code<CodeStr>;
using TargetCode = Code<CodeStr>;

///////////////////////////////////////////////////////////////////////////////
//                                MigrateRule                                //
///////////////////////////////////////////////////////////////////////////////
struct MigrateRule {
    MigrateRule(std::string ident, OriginCode ocode, TargetCode tcode):
        identifier(ident), originCode(ocode), targetCode(tcode) {}

    const std::string identifier;
    OriginCode originCode;
    TargetCode targetCode;
};

struct MigrateRules {
    std::vector<MigrateRule> rules;

    std::vector<MigrateRule>::const_iterator begin() const { return std::begin(rules); }
    std::vector<MigrateRule>::const_iterator end() const { return std::end(rules); }
};

///////////////////////////////////////////////////////////////////////////////
//                                  Migrate                                  //
///////////////////////////////////////////////////////////////////////////////
template<typename T>
concept Language = requires(T t, std::istream& is, std::string str) {
    { t.parseTreeFromStream(is) } -> std::same_as<antlr4::tree::ParseTree*>;
    { t.parseTreeFromString(str) } -> std::same_as<antlr4::tree::ParseTree*>;
};

template<Language T>
using MigrateInput = std::pair<const std::istream&, T>;

template<typename T>
struct Migrate {
    MigrateRules migrateRules;

    // Evaluation of a 'Migrate' Entity is to perform actions to
    // migrating codes from 'istream' to 'ostream' with Rules within
    // the 'Migrate' Entity.
    void operator()(MigrateInput<T>, std::ostream&) const {
        for (auto& rule: migrateRules) {
            rule();
        }
    }
};

} // Rule
} // Interpreter
} // Language

#endif /* LANGUAGE_H */
