#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <string>
#include <map>

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
    void                skipComment();
    TokenPtr            id();

    const               std::string m_text;
    unsigned            m_pos;
    char                m_currentChar;
    unsigned            m_currentLine;
    const std::map<std::string, TokenPtr> RESERVED_KEYWORDS = {
        {"var", std::make_shared<Token> (TokenType::VAR, "var")},
        {"int", std::make_shared<Token> (TokenType::INTEGER_TYPE, "int")},
        {"string", std::make_shared<Token> (TokenType::STRING_TYPE, "string")},
        {"print", std::make_shared<Token> (TokenType::PRINT, "print")},
        {"if", std::make_shared<Token> (TokenType::IF, "if")},
        {"do", std::make_shared<Token> (TokenType::DO, "do")},
        {"to_int", std::make_shared<Token> (TokenType::TO_INT, "to_int")},
        {"to_string", std::make_shared<Token> (TokenType::TO_STRING, "to_string")},
    };
};

using LexerPtr = std::shared_ptr<Lexer>;

#endif // LEXER_H


