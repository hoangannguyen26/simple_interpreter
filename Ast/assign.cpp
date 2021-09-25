#include "assign.h"

Assign::Assign(const VarPtr& left, const TokenPtr& op, const ASTPtr& right) :
    AST(NodeType::Assign),
    m_left(left),
    m_op(op),
    m_right(right)
{

}
