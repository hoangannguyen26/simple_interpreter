#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <map>
#include "token.h"

class Lexer
{
public:
    explicit            Lexer(const std::string& text);
    TokenPtr            getNextToken();
private:
    void                error();
    void                advance();
    int                 integer();
    std::string         string();
    void                skipWhiteSpace();
    TokenPtr            id();

    const               std::string m_text;
    unsigned            m_pos;
    char                m_currentChar;
    std::map<std::string, TokenPtr> RESERVED_KEYWORDS = {
        {"var", std::make_shared<Token> (TokenType::VAR, "var")},
        {"print", std::make_shared<Token> (TokenType::PRINT, "print")},
        {"if", std::make_shared<Token> (TokenType::IF, "if")},
        {"do", std::make_shared<Token> (TokenType::DO, "do")}
    };
};

using LexerPtr = std::shared_ptr<Lexer>;

#endif // LEXER_H


