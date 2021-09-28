#include "print.h"


Print::Print(const ASTPtr& value, const TokenPtr& token) :
    AST(NodeType::Print, token),
    m_value(value)
{
};
