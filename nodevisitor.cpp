#include "nodevisitor.h"


BasicType NodeVisitor::visit(const ASTPtr& node){
    switch (node->m_type) {
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
    default:
        throw "Missing handle";
        return BasicType(0);
    }
}
