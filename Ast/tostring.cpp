#include "tostring.h"

ToString::ToString(const TokenPtr& data):
    AST(AST::NodeType::ToString),
    m_data(data)
{

}
