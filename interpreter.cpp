#include "interpreter.h"
#include "Ast/ast.h"
#include "Ast/literal.h"
#include "Ast/binop.h"
#include "Ast/unaryop.h"
#include "Ast/block.h"
#include "Ast/unaryop.h"
#include "Ast/var.h"
#include "Ast/noop.h"
#include "Ast/assign.h"
#include "Ast/vardecl.h"
#include "Ast/type.h"
#include "Ast/print.h"
#include "Ast/ifcondition.h"
#include "Ast/doloop.h"
#include"Ast/tostring.h"
#include"Ast/toint.h"


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

BasicType Interpreter::visit_Literal(const ASTPtr &astNode)
{
    GET_NODE(Literal, astNode);
    return BasicType(node->m_value);
}

BasicType Interpreter::visit_BinOp(const ASTPtr &astNode) {
    GET_NODE(BinOp, astNode);
    auto left = visit(node->m_left);
    auto right = visit(node->m_right);
    if(node->m_left->m_type == AST::NodeType::Var) {
        const VarPtr var = std::dynamic_pointer_cast<Var>(node->m_left);
        if(var) {
            left = getVariableValue(var->m_value);
        }
    }
    if(node->m_right->m_type == AST::NodeType::Var) {
        const VarPtr var = std::dynamic_pointer_cast<Var>(node->m_right);
        if(var) {
            right = getVariableValue(var->m_value);
        }
    }

    if(node->m_op->m_type == TokenType::PLUS) {
        return left + right;
    }
    if(node->m_op->m_type == TokenType::MINUS) {
        return left - right;
    }
    if(node->m_op->m_type == TokenType::MUL) {
        return left * right;
    }
    if(node->m_op->m_type == TokenType::DIV) {
        return left / right;
    }
    if(node->m_op->m_type == TokenType::GREAT) {
        return left > right;
    }
    if(node->m_op->m_type == TokenType::LESS) {
        return left < right;
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
    GLOBAL_SCOPE[varName] = visit(node->m_right);;
    return BasicType();
}

BasicType Interpreter::visit_Block(const ASTPtr &astNode) {
    GET_NODE(Block, astNode);
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
    VarPtr variable = std::dynamic_pointer_cast<Var>(node->m_value);
    if(variable) {
        const std::string variableName = variable->m_value;
        // Check if the variable exist
        const auto it = GLOBAL_SCOPE.find(variableName);
        if(it != GLOBAL_SCOPE.end()) {
            std::cout << it->second;
        } else {
            throw "could not found variable";
        }
    } else {
        std::cout << visit(node->m_value);
    }
    return BasicType();
}

BasicType Interpreter::visit_IfCondition(const ASTPtr &astNode) {
    GET_NODE(IfCondition, astNode);
    auto condition = visit(node->m_condition);
    if(condition != 0) {
        return visit(node->m_block);
    }
    return BasicType();
}

BasicType Interpreter::visit_DoLoop(const ASTPtr &astNode) {
    GET_NODE(DoLoop, astNode);
    int loop = 0;
    if(node->m_condition->m_type == AST::NodeType::Var) {
        const VarPtr var = std::dynamic_pointer_cast<Var>(node->m_condition);
        if(var) {
            loop = getVariableValue(var->m_value).getInt();
        }
    } else if(node->m_condition->m_type == AST::NodeType::BinOp) {
        loop = visit(node->m_condition).getInt();
    } else if (node->m_condition->m_type == AST::NodeType::Literal) {
        const LiteralPtr num = std::dynamic_pointer_cast<Literal>(node->m_condition);
        if(num) {
            loop = num->m_value.getInt();
        }
    }
    for(int i = 0; i < loop; i ++) {
        visit(node->m_block);
    }
    return BasicType();
}

BasicType Interpreter::visit_ToString(const ASTPtr &astNode){
    GET_NODE(ToString, astNode);
    if(node->m_data->m_type == TokenType::ID) {
        auto variable = getVariableValue(node->m_data->m_value.getString());
        return variable.toString();
    }
    return node->m_data->m_value.toString();
}

BasicType Interpreter::visit_ToInt(const ASTPtr &astNode){
    GET_NODE(ToInt, astNode);
    if(node->m_data->m_type == TokenType::ID) {
        auto variable = getVariableValue(node->m_data->m_value.getString());
        return variable.toInt();
    }
    return node->m_data->m_value.toInt();
}


BasicType Interpreter::getVariableValue(const std::string& varName) const {
    const auto it = GLOBAL_SCOPE.find(varName);
    if(it != GLOBAL_SCOPE.end()) {
        return it->second;
    }
    throw "Variable does not exist ";
}

BasicType Interpreter::interpret() {
    ASTPtr tree = m_parser->parse();
    BasicType result = visit(tree);
    return result;
}
