#include "parser.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include "Ast/ast.h"
#include "Ast/literal.h"
#include "Ast/binop.h"
#include "Ast/unaryop.h"
#include "Ast/noop.h"
#include "Ast/var.h"
#include "Ast/assign.h"
#include "Ast/block.h"
#include "Ast/vardecl.h"
#include "Ast/type.h"
#include "Ast/print.h"
#include <memory>

Parser::Parser(const LexerPtr lexer):
    m_lexer (lexer),
    m_currentToken(m_lexer->getNextToken()),
    m_currentTabLevel(0)
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
    // factor: INTEGER | LPAREN expr RPAREN | STRING
    TokenPtr token = m_currentToken;
    if (token->m_type == TokenType::PLUS) {
        eat(TokenType::PLUS);
        return std::make_shared<UnaryOp>(token, factor());
    } else if (token->m_type == TokenType::MINUS) {
        eat(TokenType::MINUS);
        return std::make_shared<UnaryOp>(token, factor());
    } else if (token->m_type == TokenType::INTEGER || token->m_type == TokenType::STRING) {
        return literal();
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

LiteralPtr Parser::literal()
{
    LiteralPtr node = std::make_shared<Literal>(m_currentToken);
    if (m_currentToken->m_type == TokenType::INTEGER) {
        eat(TokenType::INTEGER);
    } else if (m_currentToken->m_type == TokenType::STRING) {
        eat(TokenType::STRING);
    }
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
    if(m_currentToken->m_type == TokenType::VAR) {
        return  variable_declaration();
    } else if(m_currentToken->m_type == TokenType::ID)
    {
        return assignment_statement();
    }
    else if(m_currentToken->m_type == TokenType::PRINT) {
        return print_statement();
    }
    else if(m_currentToken->m_type == TokenType::IF){
        return if_statement();
    }
    else
    {
        return empty();
    }
}

ASTPtr Parser::if_statement(){
    if(m_currentToken->m_type == TokenType::IF) {
        eat(TokenType::IF);
        m_currentTabLevel++;
        eat(TokenType::END_OF_LINE);
        ASTPtr ifBlock = block();
        return ifBlock;
    }
    return nullptr;
}


ASTPtr Parser::block()
{
    std::vector<ASTPtr> nodes;
    BlockPtr root = std::make_shared<Block>();
    int tabLevel = getTabLevel();
    nodes.push_back(statement());
    while (m_currentToken->m_type == TokenType::END_OF_LINE) {
        eat(TokenType::END_OF_LINE);
        if(tabLevel > m_currentTabLevel)
        {
            throw "Incorrect syntax";
            break;
        } else if (tabLevel < m_currentTabLevel) {
            m_currentTabLevel --;
            break;
        }
        nodes.push_back(statement());
    }

    for(const auto node: nodes) {
        root->children.push_back(node);
    }
    return root;
}

ASTPtr Parser::program()
{
    return block();
}

ASTPtr Parser::type_spec()
{
    /*
     * type_spec : INTEGER
    */
    auto token = m_currentToken;
    if(m_currentToken->m_type == TokenType::INTEGER_TYPE)
    {
        eat(TokenType::INTEGER_TYPE);
    } else if (m_currentToken->m_type == TokenType::STRING_TYPE){
        eat(TokenType::STRING_TYPE);
    }
    return std::make_shared<Type>(token);
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
        auto token = m_currentToken;
        if(m_currentToken->m_type == TokenType::ID) {
            return std::make_shared<Print>(variable());
        } else {
            return std::make_shared<Print>(expr());
        }
    }
    return nullptr;
}

int Parser::getTabLevel(){
    int count = 0;
    while (m_currentToken->m_type == TokenType::TAB) {
        count++;
        eat(TokenType::TAB);
    }
    return count;
}
