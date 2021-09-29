#ifndef IFCONDITION_H
#define IFCONDITION_H

#include "ast.h"


class IfCondition : public AST
{
public:
    IfCondition(const ASTPtr& condition, const ASTPtr& block, const TokenPtr& token);
    const ASTPtr            m_condition;
    const ASTPtr            m_block;
};

CREATE_SHARED_PTR(IfCondition);

#endif // IFCONDITION_H
