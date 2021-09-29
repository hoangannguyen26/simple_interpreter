#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "nodevisitor.h"
#include "Ast/ast.h"
#include "Ast/literal.h"

#include <string>
#include <vector>


class Parser
{
public:
    explicit            Parser(const LexerPtr& lexer);
    ASTPtr              parse();
private:
    bool                m_exitFromBlock;
    const               LexerPtr m_lexer;
    TokenPtr            m_currentToken;
    TokenPtr            m_LastToken;
    int                 m_currentTabLevel;
    ASTPtr              error();
    void                eat(TokenType tokenType);
    ASTPtr              factor();
    ASTPtr              term();
    ASTPtr              expr();

    ASTPtr              empty();
    ASTPtr              variable();
    LiteralPtr          literal();
    ASTPtr              assignment_statement();
    ASTPtr              statement();
    ASTPtr              block();
    ASTPtr              program();
    ASTPtr              type_spec();
    ASTPtr              variable_declaration();
    ASTPtr              print_statement();
    int                 getTabLevel();
    ASTPtr              if_statement();
    ASTPtr              do_statement();
    ASTPtr              to_int();
    ASTPtr              to_string();
};

using ParserPtr = std::shared_ptr<Parser>;

#endif // PARSER_H
