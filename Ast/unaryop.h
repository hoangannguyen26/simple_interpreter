#ifndef UNARYOP_H
#define UNARYOP_H
#include "ast.h"
#include "../token.h"


class UnaryOp : public AST
{
public:
    explicit UnaryOp(const TokenPtr& op, ASTPtr expr);
    const TokenPtr        m_op;
    const ASTPtr          m_expr;
};

using UnaryOpPtr = std::shared_ptr<UnaryOp>;

#endif // UNARYOP_H
