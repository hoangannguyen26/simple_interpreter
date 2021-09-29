#include "Ast/noop.h"

NoOp::NoOp(const TokenPtr& token):
    AST(NodeType::NoOp, token)
{

}
