#include "Ast/literal.h"
#include <cctype>

Literal::Literal(const TokenPtr &token) : AST(NodeType::Literal, token),
                                          m_value(token->m_value)
{
}
