#include "interpreter.h"
#include "Ast/ast.h"
#include "Ast/num.h"
#include "Ast/binop.h"
#include "Ast/unaryop.h"
#include "Ast/compound.h"
#include "Ast/unaryop.h"
#include "Ast/var.h"
#include "Ast/noop.h"
#include "Ast/assign.h"
#include "Ast/vardecl.h"
#include "Ast/type.h"

Interpreter::Interpreter(const ParserPtr& parser):
    m_parser(parser)
{

}

BasicType Interpreter::visit_Num(const ASTPtr &numNode)
{
    NumPtr node = std::dynamic_pointer_cast<Num>(numNode);
    if(node) {
        return BasicType(node->m_value);
    }
    return BasicType();
}

BasicType Interpreter::visit_BinOp(const ASTPtr &binopNode) {
    BinOpPtr node = std::dynamic_pointer_cast<BinOp>(binopNode);
    if(node) {
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
    }
    return BasicType();
}

BasicType Interpreter::visit_UnaryOp(const ASTPtr &unaryOpNode){
    UnaryOpPtr node = std::dynamic_pointer_cast<UnaryOp>(unaryOpNode);
    if(node) {
        if(node->m_op->m_type == TokenType::PLUS)
        {
            return visit(node->m_expr);
        }
        if(node->m_op->m_type == TokenType::MINUS)
        {
            return - visit(node->m_expr);
        }
    }
    return BasicType();
}

BasicType Interpreter::visit_Assign(const ASTPtr &assignNode) {
    AssignPtr node = std::dynamic_pointer_cast<Assign>(assignNode);
    if(node) {
        const std::string varName = node->m_left->m_value;
        if(GLOBAL_SCOPE.find(varName) == GLOBAL_SCOPE.end()) {
            throw "Variable is not defined";
            return BasicType();
        }
        GLOBAL_SCOPE[varName] = visit(node->m_right);
    }
    return BasicType();
}

BasicType Interpreter::visit_Compound(const ASTPtr &compoudNode) {
    CompoundPtr node = std::dynamic_pointer_cast<Compound>(compoudNode);
    if(node) {
        for(const auto child : node->children) {
            visit(child);
        }
    }
    return BasicType();
}

BasicType Interpreter::visit_Variable(const ASTPtr &varNode) {
    VarPtr node = std::dynamic_pointer_cast<Var>(varNode);
    if(node) {
        auto varName = node->m_value;
        if(GLOBAL_SCOPE.find(varName) == GLOBAL_SCOPE.end()){
            throw "Error name";
        }
        return node->m_value;
    }
    return BasicType();
}

BasicType Interpreter::visit_VarDecl(const ASTPtr &varDeclNode) {
    VarDeclPtr node = std::dynamic_pointer_cast<VarDecl>(varDeclNode);

    if(node) {
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
    }

    return BasicType();
}
BasicType Interpreter::visit_Type(const ASTPtr &typeNode) {
    TypePtr node = std::dynamic_pointer_cast<Type>(typeNode);
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
