#ifndef TOKEN_H
#define TOKEN_H

#include "token-type.h"
#include <string>
#include <memory>
#include "basictype.h"

class Token
{
public:
    explicit Token(const TokenType& type, const BasicType& m_value, const unsigned line = 0);
    const TokenType m_type;
    const BasicType m_value;
    unsigned  m_line;
    void setLine(const unsigned line);
};

using TokenPtr = std::shared_ptr<Token>;

#endif // TOKEN_H
