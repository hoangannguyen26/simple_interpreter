#include "assign.h"

Assign::Assign(const ASTPtr& left, const TokenPtr& op, const ASTPtr& right) :
    AST(NodeType::Assign, op),
    m_left(left),
    m_op(op),
    m_right(right)
{

}
