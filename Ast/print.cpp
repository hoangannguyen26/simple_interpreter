#include "print.h"


Print::Print(const ASTPtr& value) :
    AST(NodeType::Print),
    m_value(value)
{
};
