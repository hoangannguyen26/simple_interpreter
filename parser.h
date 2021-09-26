#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "lexer.h"
#include "nodevisitor.h"
#include "Ast/ast.h"
#include "Ast/var.h"
#include "Ast/literal.h"
#include <vector>


class Parser
{
public:
    explicit            Parser(const LexerPtr lexer);
    ASTPtr              parse();
private:
    const               LexerPtr m_lexer;
    TokenPtr            m_currentToken;
    int                 m_currentTabLevel;
    void                error();
    void                eat(TokenType tokenType);
    ASTPtr              factor();
    ASTPtr              term();
    ASTPtr              expr();

    ASTPtr              empty();
    VarPtr              variable();
    LiteralPtr          literal();
    ASTPtr              assignment_statement();
    ASTPtr              statement();
    std::vector<ASTPtr> statement_list();
    ASTPtr              block();
    ASTPtr              program();
    ASTPtr              type_spec();
    ASTPtr              variable_declaration();
    ASTPtr              print_statement();
    int                 getTabLevel();
    ASTPtr              if_statement();
    bool                m_exitFromBlock;
};

using ParserPtr = std::shared_ptr<Parser>;

#endif // PARSER_H
