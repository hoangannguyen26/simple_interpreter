#ifndef UNARYOP_H
#define UNARYOP_H

#include "ast.h"


class UnaryOp : public AST
{
public:
    explicit UnaryOp(const TokenPtr& op, ASTPtr expr);
    const TokenPtr        m_op;
    const ASTPtr          m_expr;
};

CREATE_SHARED_PTR(UnaryOp);

#endif // UNARYOP_H
