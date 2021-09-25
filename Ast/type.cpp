#include "type.h"

Type::Type(const TokenPtr& token):
    AST(NodeType::Type),
    m_token(token),
    m_value(token->m_value.getString())
{
}
