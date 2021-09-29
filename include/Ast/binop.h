#ifndef BINOP_H
#define BINOP_H

#include "ast.h"


class BinOp : public AST
{
public:
    explicit BinOp(const ASTPtr& left, const TokenPtr& op, const ASTPtr& right);
public:
    const ASTPtr            m_left;
    const TokenPtr          m_op;
    const ASTPtr            m_right;
};

CREATE_SHARED_PTR(BinOp);

#endif // BINOP_H
