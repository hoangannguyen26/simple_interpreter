#ifndef VAR_H
#define VAR_H

#include "ast.h"
#include "../token.h"

// The Var node is constructed out of ID token.
class Var : public AST
{
public:
    Var();
    explicit Var(const TokenPtr& token);
    const TokenPtr            m_token;
    const std::string         m_value;  // variable name
};

using VarPtr = std::shared_ptr<Var>;

#endif // VAR_H
