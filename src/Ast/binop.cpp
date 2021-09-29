#include "Ast/binop.h"

BinOp::BinOp(const ASTPtr& left, const TokenPtr& op, const ASTPtr& right):
    AST(NodeType::BinOp, op),
    m_left(left),
    m_op(op),
    m_right(right)
{

}
