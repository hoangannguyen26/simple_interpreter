#include "num.h"
#include <cctype>

Num::Num(const TokenPtr& token):
    AST(NodeType::Num),
    m_token(token),
    m_value(token->m_value)
{
}

Num::Num(const Num& other):
    AST(other.m_type),
    m_token(other.m_token),
    m_value(other.m_value)
{
}
