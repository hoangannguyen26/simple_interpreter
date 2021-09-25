#ifndef NUM_H
#define NUM_H
#include "ast.h"
#include "../token.h"


class Literal : public AST
{
public:
    explicit Literal(const TokenPtr& token);
    Literal(const Literal&);
public:
    const TokenPtr            m_token;
    const BasicType           m_value;
};

CREATE_SHARED_PTR(Literal);

#endif // NUM_H
