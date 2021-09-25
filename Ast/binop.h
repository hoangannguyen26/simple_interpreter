#ifndef BINOP_H
#define BINOP_H
#include "ast.h"
#include "../token.h"
#include "num.h"


class BinOp : public AST
{
public:
    explicit BinOp(const ASTPtr& left, const TokenPtr& op, const ASTPtr& right);
    BinOp(const BinOp& other);
public:
    const ASTPtr            m_left;
    const TokenPtr          m_op;
    const ASTPtr            m_right;
};

using BinOpPtr = std::shared_ptr<BinOp>;

#endif // BINOP_H
