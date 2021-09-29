#include "Ast/tostring.h"

ToString::ToString(const TokenPtr &data) : AST(AST::NodeType::ToString, data),
                                           m_data(data)
{
}
