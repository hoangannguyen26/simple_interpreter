#include "literal.h"
#include <cctype>

Literal::Literal(const TokenPtr& token):
    AST(NodeType::Literal),
    m_token(token),
    m_value(token->m_value)
{
}

Literal::Literal(const Literal& other):
    AST(other.m_type),
    m_token(other.m_token),
    m_value(other.m_value)
{
}
