#ifndef TYPE_H
#define TYPE_H

#include "ast.h"
#include "../token.h"

class Type : public AST
{
public:
    explicit Type(const TokenPtr& token);
    TokenPtr        m_token;
    std::string     m_value;
};

using TypePtr = std::shared_ptr<Type>;

#endif // TYPE_H
