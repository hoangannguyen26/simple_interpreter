#include "ifcondition.h"

IfCondition::IfCondition(const ASTPtr& condition, const ASTPtr& block):
    AST(AST::NodeType::If),
    m_condition(condition),
    m_block(block)
{

}
