#include "binop.h"

BinOp::BinOp(const ASTPtr& left, const TokenPtr& op, const ASTPtr& right):
    AST(NodeType::BinOp),
    m_left(left),
    m_op(op),
    m_right(right)
{

}

BinOp::BinOp(const BinOp& other) :
    AST(other.m_type),
    m_left(other.m_left),
    m_op(other.m_op),
    m_right(other.m_right)
{
}
