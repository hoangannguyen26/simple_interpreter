#include "Ast/type.h"

Type::Type(const TokenPtr& token):
    AST(NodeType::Type, token),
    m_token(token),
    m_value(token->m_value.toString())
{
}
