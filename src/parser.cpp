#include "parser.h"

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
#include "Ast/ifcondition.h"
#include "Ast/doloop.h"
#include "Ast/tostring.h"
#include "Ast/toint.h"
#include "Exception/parserexception.h"

#include <memory>
#include <cctype>
#include <cstdlib>

Parser::Parser(const LexerPtr& lexer):
    m_exitFromBlock(false),
    m_lexer (lexer),
    m_currentToken(m_lexer->getNextToken()),
    m_currentTabLevel(0)
{

}

void Parser::eat(TokenType tokenType) {
    if(m_currentToken->m_type == tokenType)
    {
        m_LastToken = m_currentToken;
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
    } else if (token->m_type == TokenType::TO_STRING) {
        return to_string();
    } else if (token->m_type == TokenType::TO_INT) {
        return to_int();
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
    while (m_currentToken->m_type == TokenType::PLUS
           || m_currentToken->m_type == TokenType::MINUS
           || m_currentToken->m_type == TokenType::GREAT
           || m_currentToken->m_type == TokenType::LESS) {
        TokenPtr token = m_currentToken;
        if(token->m_type == TokenType::PLUS)
        {
            eat(TokenType::PLUS);
        }
        else if(token->m_type == TokenType::MINUS)
        {
            eat(TokenType::MINUS);
        }
        else if(token->m_type == TokenType::GREAT)
        {
            eat(TokenType::GREAT);
        }
        else if(token->m_type == TokenType::LESS)
        {
            eat(TokenType::LESS);
        }
        result = std::make_shared<BinOp>(result, token, term());
    }
    return result;
}

ASTPtr Parser::error() {
    throw ParserException("Error at line " + std::to_string(m_LastToken->m_line) + " character " + m_LastToken->m_value.getString());
    return nullptr;
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
    return std::make_shared<NoOp>(m_LastToken);
}

ASTPtr Parser::variable()
{
    /*
        variable : ID
    */
    if(m_currentToken->m_type == TokenType::ID) {
        VarPtr node = std::make_shared<Var>(m_currentToken);
        eat(TokenType::ID);
        return node;
    }
    return error();
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
    ASTPtr left = variable();
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
    else if(m_currentToken->m_type == TokenType::DO){
        return do_statement();
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
        ASTPtr condition = expr();
        eat(TokenType::END_OF_LINE);
        ASTPtr ifBlock = block();
        return std::make_shared<IfCondition>(condition, ifBlock, m_LastToken);
    }
    return error();
}

ASTPtr Parser::do_statement()
{
    if(m_currentToken->m_type == TokenType::DO){
        eat(TokenType::DO);
        m_currentTabLevel++;
        ASTPtr condition = expr();
        eat(TokenType::END_OF_LINE);
        ASTPtr doBlock = block();
        return std::make_shared<DoLoop>(condition, doBlock, m_LastToken);
    }
    return error();
}

//static bool existFromBlock = false;

ASTPtr Parser::block()
{
    std::vector<ASTPtr> nodes;
    BlockPtr root = std::make_shared<Block>(m_currentToken);
    int tabLevel = getTabLevel();
    nodes.push_back(statement());
    while (m_currentToken->m_type == TokenType::END_OF_LINE || m_exitFromBlock) {
        if(!m_exitFromBlock) {
            eat(TokenType::END_OF_LINE);
        }
        tabLevel = getTabLevel();
        if(tabLevel > m_currentTabLevel)
        {
            return error();
        } else if (tabLevel < m_currentTabLevel) {
            m_exitFromBlock = true;
            m_currentTabLevel --;
            break;
        }
        m_exitFromBlock = false;
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
        ASTPtr var_node = variable();
        ASTPtr initialization = nullptr;
        if(m_currentToken->m_type == TokenType::ASSIGN) {
            eat(TokenType::ASSIGN);
            initialization = expr();
        }
        return std::make_shared<VarDecl>(var_node, type_node, initialization, m_LastToken);
    }
    return nullptr;
}

ASTPtr Parser::print_statement() {
    if(m_currentToken->m_type == TokenType::PRINT) {
        eat(TokenType::PRINT);
        return std::make_shared<Print>(expr(), m_LastToken);
    }
    return error();
}

ASTPtr Parser::to_int()
{
    if(m_currentToken->m_type == TokenType::TO_INT) {
        eat(TokenType::TO_INT);
        auto token = m_currentToken;
        if(token->m_type == TokenType::ID)
        {
            eat(TokenType::ID);
            return std::make_shared<ToInt>(token);
        }
        if(token->m_type == TokenType::STRING)
        {
            eat(TokenType::STRING);
            return std::make_shared<ToInt>(token);
        }
        if(token->m_type == TokenType::INTEGER)
        {
            eat(TokenType::INTEGER);
            return std::make_shared<ToInt>(token);
        }
    }
    return error();
}
ASTPtr Parser::to_string()
{
    if(m_currentToken->m_type == TokenType::TO_STRING) {
        eat(TokenType::TO_STRING);
        auto token = m_currentToken;
        if(token->m_type == TokenType::ID)
        {
            eat(TokenType::ID);
            return std::make_shared<ToString>(token);
        }
        if(token->m_type == TokenType::STRING)
        {
            eat(TokenType::STRING);
            return std::make_shared<ToString>(token);
        }
        if(token->m_type == TokenType::INTEGER)
        {
            eat(TokenType::INTEGER);
            return std::make_shared<ToString>(token);
        }
    }
    return error();
}

int Parser::getTabLevel(){
    int count = 0;
    while (m_currentToken->m_type == TokenType::TAB) {
        count++;
        eat(TokenType::TAB);
    }
    return count;
}
