#ifndef DOLOOP_H
#define DOLOOP_H

#include "ast.h"


class DoLoop : public AST
{
public:
    DoLoop(const ASTPtr& condition, const ASTPtr& block, const TokenPtr& token);
    const ASTPtr            m_condition;
    const ASTPtr            m_block;
};

CREATE_SHARED_PTR(DoLoop);

#endif // DOLOOP_H
