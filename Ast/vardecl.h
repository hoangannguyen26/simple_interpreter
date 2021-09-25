#ifndef VARDECL_H
#define VARDECL_H

#include "ast.h"


class VarDecl : public AST
{
public:
    VarDecl(const ASTPtr& var, const ASTPtr& type);
    ASTPtr          m_var_node;
    ASTPtr          m_type_node;
};

using VarDeclPtr = std::shared_ptr<VarDecl>;

#endif // VARDECL_H
