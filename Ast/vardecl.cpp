#include "vardecl.h"

VarDecl::VarDecl(const ASTPtr& var, const ASTPtr& type, const ASTPtr& value, const TokenPtr& token):
    AST(NodeType::VarDecl, token),
    m_var_node(var),
    m_type_node(type),
    m_initialization_value(value)
{
}
