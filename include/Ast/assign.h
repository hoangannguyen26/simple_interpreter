#ifndef ASSIGN_H
#define ASSIGN_H

#include "ast.h"

class Assign : public AST
{
public:
    Assign(const ASTPtr& left, const TokenPtr& op, const ASTPtr& right);
    ASTPtr          m_left;
    TokenPtr        m_op;
    ASTPtr          m_right;
};

CREATE_SHARED_PTR(Assign);

#endif // ASSIGN_H
