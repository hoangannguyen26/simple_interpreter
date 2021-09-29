#ifndef VARDECL_H
#define VARDECL_H

#include "ast.h"

class VarDecl : public AST
{
public:
    VarDecl(const ASTPtr &var, const ASTPtr &type, const ASTPtr &value, const TokenPtr &token);
    const ASTPtr m_var_node;
    const ASTPtr m_type_node;
    const ASTPtr m_initialization_value;
};

CREATE_SHARED_PTR(VarDecl);

#endif // VARDECL_H
