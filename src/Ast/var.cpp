#include "Ast/var.h"

Var::Var(const TokenPtr &token) : AST(NodeType::Var, token),
                                  m_value(token->m_value.toString())
{
}
