#include "vardecl.h"

VarDecl::VarDecl(const ASTPtr& var, const ASTPtr& type):
    AST(NodeType::VarDecl),
    m_var_node(var),
    m_type_node(type)
{
}
