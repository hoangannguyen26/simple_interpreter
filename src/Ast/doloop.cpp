#include "Ast/doloop.h"

DoLoop::DoLoop(const ASTPtr &condition, const ASTPtr &block, const TokenPtr &token) : AST(NodeType::Do, token),
                                                                                      m_condition(condition),
                                                                                      m_block(block)
{
}
