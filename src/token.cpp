#include "token.h"

Token::Token(const TokenType& type, const BasicType& value, const unsigned line):
    m_type(type),
    m_value(value),
    m_line(line)
{
}

void Token::setLine(const unsigned line){
    m_line = line;
}
