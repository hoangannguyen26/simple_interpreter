#ifndef VAR_H
#define VAR_H

#include "ast.h"

class Var : public AST
{
public:
    Var();
    explicit Var(const TokenPtr& token);
    const std::string         m_value;  // variable name
};

CREATE_SHARED_PTR(Var);

#endif // VAR_H
