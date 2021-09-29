#include "Ast/ifcondition.h"

IfCondition::IfCondition(const ASTPtr &condition, const ASTPtr &block, const TokenPtr &token) : AST(AST::NodeType::If, token),
                                                                                                m_condition(condition),
                                                                                                m_block(block)
{
}
