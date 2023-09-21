#include "Parser.h"

namespace Parser {

template<typename ExtNode,
         ExtParser<ExtNode> P,
         NodeAdapter<ExtNode> A,
         int lang>
std::vector<A> Parser<ExtNode, P, A, lang>::adapters_ {};

} // Parser
