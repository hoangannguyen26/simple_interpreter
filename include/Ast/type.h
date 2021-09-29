#ifndef TYPE_H
#define TYPE_H

#include "ast.h"

class Type : public AST
{
public:
    explicit Type(const TokenPtr& token);
    TokenPtr              m_token;
    const std::string     m_value;
};

CREATE_SHARED_PTR(Type);

#endif // TYPE_H
