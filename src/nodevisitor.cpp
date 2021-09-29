#include "nodevisitor.h"

Variant NodeVisitor::visit(const ASTPtr &node)
{
    switch (node->m_type)
    {
    case AST::NodeType::Literal:
        return visit_Literal(node);
    case AST::NodeType::BinOp:
        return visit_BinOp(node);
    case AST::NodeType::UnaryOp:
        return visit_UnaryOp(node);
    case AST::NodeType::Assign:
        return visit_Assign(node);
    case AST::NodeType::Var:
        return visit_Variable(node);
    case AST::NodeType::Block:
        return visit_Block(node);
    case AST::NodeType::VarDecl:
        return visit_VarDecl(node);
    case AST::NodeType::Type:
        return visit_Type(node);
    case AST::NodeType::Print:
        return visit_Print(node);
    case AST::NodeType::If:
        return visit_IfCondition(node);
    case AST::NodeType::Do:
        return visit_DoLoop(node);
    case AST::NodeType::ToString:
        return visit_ToString(node);
    case AST::NodeType::ToInt:
        return visit_ToInt(node);
    default:
        return Variant(0);
    }
}
