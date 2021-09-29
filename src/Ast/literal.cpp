#include "Ast/literal.h"

Literal::Literal(const TokenPtr &token) : AST(NodeType::Literal, token),
                                          m_value(token->m_value)
{
}
