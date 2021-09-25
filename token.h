#ifndef TOKEN_H
#define TOKEN_H

#include "token-type.h"
#include <string>
#include <memory>
#include "basictype.h"

class Token
{
public:
    explicit Token(const TokenType type, const BasicType& m_value);
    const TokenType m_type;
    const BasicType m_value;
};

using TokenPtr = std::shared_ptr<Token>;

#endif // TOKEN_H
