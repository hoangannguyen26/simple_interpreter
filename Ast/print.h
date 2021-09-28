#ifndef PRINT_H
#define PRINT_H
#include "ast.h"

class Print : public AST
{
public:
    Print(const ASTPtr& value, const TokenPtr& token);
    const ASTPtr        m_value;
};

CREATE_SHARED_PTR(Print);

#endif // PRINT_H
