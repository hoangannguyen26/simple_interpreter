#include "unaryop.h"

UnaryOp::UnaryOp(const TokenPtr& op, ASTPtr expr):
    AST(NodeType::UnaryOp),
    m_op(op),
    m_expr(expr)
{

}
