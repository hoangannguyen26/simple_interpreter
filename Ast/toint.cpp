#include "toint.h"

ToInt::ToInt(const TokenPtr& data):
    AST(AST::NodeType::ToInt),
    m_data(data)
{
}
