#ifndef NUM_H
#define NUM_H
#include "ast.h"
#include "../token.h"


class Num : public AST
{
public:
    explicit Num(const TokenPtr& token);
    Num(const Num&);
public:
    const TokenPtr            m_token;
    const BasicType           m_value;
};

using NumPtr = std::shared_ptr<Num>;

#endif // NUM_H
