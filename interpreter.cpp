#include "interpreter.h"
#include "Ast/ast.h"
#include "Ast/literal.h"
#include "Ast/binop.h"
#include "Ast/unaryop.h"
#include "Ast/compound.h"
#include "Ast/unaryop.h"
#include "Ast/var.h"
#include "Ast/noop.h"
#include "Ast/assign.h"
#include "Ast/vardecl.h"
#include "Ast/type.h"
#include "Ast/print.h"


#define GET_NODE(nodeType, astNode)                                     \
    nodeType##Ptr node = std::dynamic_pointer_cast<nodeType>(astNode);  \
    if(node == nullptr) {                                               \
        std::cout << "!!! ERROR !!! could not get node" <<#nodeType;  \
        return BasicType();                                             \
    }                                                                   \

Interpreter::Interpreter(const ParserPtr& parser):
    m_parser(parser)
{
}

BasicType Interpreter::visit_Num(const ASTPtr &astNode)
{
    GET_NODE(Literal, astNode);
    return BasicType(node->m_value);
}

BasicType Interpreter::visit_BinOp(const ASTPtr &astNode) {
    GET_NODE(BinOp, astNode);
    if(node->m_op->m_type == TokenType::PLUS) {
        return visit(node->m_left) + visit(node->m_right);
    }
    if(node->m_op->m_type == TokenType::MINUS) {
        return visit(node->m_left) - visit(node->m_right);
    }
    if(node->m_op->m_type == TokenType::MUL) {
        return visit(node->m_left) * visit(node->m_right);
    }
    if(node->m_op->m_type == TokenType::DIV) {
        return visit(node->m_left) / visit(node->m_right);
    }
    return BasicType();
}

BasicType Interpreter::visit_UnaryOp(const ASTPtr &astNode){
    GET_NODE(UnaryOp, astNode);
    if(node->m_op->m_type == TokenType::PLUS)
    {
        return visit(node->m_expr);
    }
    if(node->m_op->m_type == TokenType::MINUS)
    {
        return - visit(node->m_expr);
    }
    return BasicType();
}

BasicType Interpreter::visit_Assign(const ASTPtr &astNode) {
    GET_NODE(Assign, astNode);
    const std::string varName = node->m_left->m_value;
    if(GLOBAL_SCOPE.find(varName) == GLOBAL_SCOPE.end()) {
        throw "Variable is not defined";
        return BasicType();
    }
    GLOBAL_SCOPE[varName] = visit(node->m_right);
    return BasicType();
}

BasicType Interpreter::visit_Compound(const ASTPtr &astNode) {
    GET_NODE(Compound, astNode);
    for(const auto child : node->children) {
        visit(child);
    }
    return BasicType();
}

BasicType Interpreter::visit_Variable(const ASTPtr &astNode) {
    GET_NODE(Var, astNode);
    auto varName = node->m_value;
    if(GLOBAL_SCOPE.find(varName) == GLOBAL_SCOPE.end()){
        throw "Error name";
    }
    return node->m_value;
    return BasicType();
}

BasicType Interpreter::visit_VarDecl(const ASTPtr &astNode) {
    GET_NODE(VarDecl, astNode);

    VarPtr varNode = std::dynamic_pointer_cast<Var>(node->m_var_node);
    TypePtr typeNode = std::dynamic_pointer_cast<Type>(node->m_type_node);
    if(!varNode || !typeNode) {
        throw "Invaild variable declation";
        return BasicType();
    }
    // check if the variable exists
    auto variableName = varNode->m_value;
    if(GLOBAL_SCOPE.find(variableName) != GLOBAL_SCOPE.end()) {
        throw "";
        return BasicType();
    }
    GLOBAL_SCOPE[variableName] = BasicType();

    return BasicType();
}

BasicType Interpreter::visit_Type(const ASTPtr &astNode) {
    GET_NODE(Type, astNode);
    // Do nothing
    return BasicType();
};

BasicType Interpreter::visit_Print(const ASTPtr &astNode) {
    GET_NODE(Print, astNode);
    if(node->m_token->m_type == TokenType::ID) {
        const std::string variableName = node->m_token->m_value.getString();
        // Check if the variable exist
        const auto it = GLOBAL_SCOPE.find(variableName);
        if(it != GLOBAL_SCOPE.end()) {
            std::cout << it->second;
        }

    } else if(node->m_token->m_type == TokenType::INTEGER || node->m_token->m_type == TokenType::STRING) {
        std::cout << node->m_token->m_value;
    }
    // Do nothing
    return BasicType();
};



BasicType Interpreter::interpret() {
    ASTPtr tree = m_parser->parse();
    BasicType result = visit(tree);
    for(auto it = GLOBAL_SCOPE.begin(); it != GLOBAL_SCOPE.end(); it ++) {
        std::cout << it->first << " -- " << it->second << std::endl;
    }
    return result;
}
