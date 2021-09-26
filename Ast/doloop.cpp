#include "doloop.h"

DoLoop::DoLoop(const ASTPtr& condition, const ASTPtr& block):
    AST(NodeType::Do),
    m_condition(condition),
    m_block(block)
{

}
