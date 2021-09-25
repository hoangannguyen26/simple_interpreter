#include "token.h"

Token::Token(const TokenType type, const BasicType& value):
    m_type(type),
    m_value(value)
{
}
