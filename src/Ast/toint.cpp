#include "Ast/toint.h"

ToInt::ToInt(const TokenPtr &data) : AST(AST::NodeType::ToInt, data),
                                     m_data(data)
{
}
