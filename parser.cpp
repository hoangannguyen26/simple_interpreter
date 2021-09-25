#include "parser.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include "Ast/ast.h"
#include "Ast/num.h"
#include "Ast/binop.h"
#include "Ast/unaryop.h"
#include "Ast/noop.h"
#include "Ast/var.h"
#include "Ast/assign.h"
#include "Ast/compound.h"
#include "Ast/vardecl.h"
#include "Ast/type.h"
#include <memory>

Parser::Parser(const LexerPtr lexer):
    m_lexer (lexer),
    m_currentToken(m_lexer->getNextToken())
{

}

void Parser::eat(TokenType tokenType) {
    if(m_currentToken->m_type == tokenType)
    {
        m_currentToken = m_lexer->getNextToken();
    }
    else
    {
        error();
    }
}

ASTPtr Parser::factor()
{
    // factor: INTEGER | LPAREN expr RPAREN
    TokenPtr token = m_currentToken;
    if (token->m_type == TokenType::PLUS) {
        eat(TokenType::PLUS);
        return std::make_shared<UnaryOp>(token, factor());
    } else if (token->m_type == TokenType::MINUS) {
        eat(TokenType::MINUS);
        return std::make_shared<UnaryOp>(token, factor());
    } else if (token->m_type == TokenType::INTEGER) {
        eat(TokenType::INTEGER);
        return std::make_shared<Num>(token);
    } else if(token->m_type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        ASTPtr result = expr();
        eat(TokenType::RPAREN);
        return result;
    } else {
        return variable();
    }
}

ASTPtr Parser::term()
{
    // term: factor ((MUL | DIV) factor)*
    ASTPtr result = factor();
    while (m_currentToken->m_type == TokenType::MUL || m_currentToken->m_type == TokenType::DIV) {
        TokenPtr token = m_currentToken;
        if(token->m_type == TokenType::MUL)
        {
            eat(TokenType::MUL);
        }
        else if(token->m_type == TokenType::DIV)
        {
            eat(TokenType::DIV);
        }

        result = std::make_shared<BinOp>(result, token, factor());
    }
    return result;
}

ASTPtr Parser::expr()
{
    /*
     * expr: term ((PLUS | MIN) term) *
     * term: factor ((MUL | DIV) factor)*
     * factor: INTERGER | LPAREN expr RPAREN
    */
    ASTPtr result = term();
    while (m_currentToken->m_type == TokenType::PLUS || m_currentToken->m_type == TokenType::MINUS) {
        TokenPtr token = m_currentToken;
        if(token->m_type == TokenType::PLUS)
        {
            eat(TokenType::PLUS);
        }
        else if(token->m_type == TokenType::MINUS)
        {
            eat(TokenType::MINUS);
        }
        result = std::make_shared<BinOp>(result, token, term());
    }
    return result;
}

void Parser::error() {
    throw "Error";
}


ASTPtr Parser::parse() {
    ASTPtr node = program();
    if(m_currentToken->m_type != TokenType::END_OF_FILE)
    {
        error();
    }
    return node;
}

ASTPtr Parser::empty()
{
    return std::make_shared<NoOp>();
}

VarPtr Parser::variable()
{
    /*
        variable : ID
    */

    VarPtr node = std::make_shared<Var>(m_currentToken);
    eat(TokenType::ID);
    return node;
}

ASTPtr Parser::assignment_statement()
{
    /*
     * assignment_statement : variable ASSIGN expr
     *  ex: test = 1
     */
    VarPtr left = variable();
    TokenPtr token = m_currentToken;
    eat(TokenType::ASSIGN);
    ASTPtr right = expr();

    return std::make_shared<Assign>(left, token, right);
}

ASTPtr Parser::statement()
{
    //    compound_statement();
    if(m_currentToken->m_type == TokenType::VAR) {
        return  variable_declaration();
    } else if(m_currentToken->m_type == TokenType::ID)
    {
        return assignment_statement();
    }
    else
    {
        return empty();
    }
}

std::vector<ASTPtr> Parser::statement_list()
{
    std::vector<ASTPtr> result;
    result.push_back(statement());
    while (m_currentToken->m_type == TokenType::END_OF_LINE) {
        eat(TokenType::END_OF_LINE);
        result.push_back(statement());
    }
//    if(m_currentToken->m_type == TokenType::ID){
//        error();
//    }
    return result;
}

ASTPtr Parser::compound_statement()
{
    std::vector<ASTPtr> nodes = statement_list();
    CompoundPtr root = std::make_shared<Compound>();
    for(const auto node: nodes) {
        root->children.push_back(node);
    }
    return root;
}

ASTPtr Parser::program()
{
    return compound_statement();
}

ASTPtr Parser::type_spec()
{
    /*
     * type_spec : INTEGER
    */
    if(m_currentToken->m_type == TokenType::INTEGER_TYPE)
    {
        eat(TokenType::INTEGER_TYPE);
    } else if (m_currentToken->m_type == TokenType::STRING_TYPE){
        eat(TokenType::STRING_TYPE);
    }
    return std::make_shared<Type>(m_currentToken);
}

ASTPtr Parser::variable_declaration() {
    /*
     *  var type_spec ID
     */
    if(m_currentToken->m_type == TokenType::VAR){
        eat(TokenType::VAR);
        ASTPtr type_node = type_spec();
        eat(TokenType::ID);
        VarPtr var_node = variable();
        return std::make_shared<VarDecl>(var_node, type_node);
    }
    return nullptr;
}

ASTPtr Parser::print_statement() {
    if(m_currentToken->m_type == TokenType::PRINT) {
        eat(TokenType::PRINT);
        if(m_currentToken->m_type == TokenType::ID) {
            eat(TokenType::ID);
        } else if(m_currentToken->m_type == TokenType::INTEGER) {
            eat(TokenType::INTEGER);
        } else if(m_currentToken->m_type == TokenType::STRING) {
            eat(TokenType::STRING);
        }
    }
    return nullptr;
}
