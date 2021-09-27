#include "lexer.h"

Lexer::Lexer(const std::string& text):
    m_text(text),
    m_pos(0),
    m_currentChar(m_text[m_pos])
{

}

TokenPtr Lexer::getNextToken() {
    while (m_currentChar != EOF)
    {
        if(std::isblank(m_currentChar) && m_currentChar != '\t')
        {
            skipWhiteSpace();
            continue;
        }

        if(std::isalpha(m_currentChar) || m_currentChar == '_') {
            return id();
        }

        if(std::isdigit(m_currentChar))
        {
            return std::make_shared<Token>(TokenType::INTEGER, integer());
        }
        if(m_currentChar == '+')
        {
            advance();
            return std::make_shared<Token>(TokenType::PLUS, "+");
        }
        if(m_currentChar == '-')
        {
            advance();
            return std::make_shared<Token>(TokenType::MINUS, "-");
        }
        if(m_currentChar == '*')
        {
            advance();
            return std::make_shared<Token>(TokenType::MUL, "*");
        }
        if(m_currentChar == '/')
        {
            advance();
            return std::make_shared<Token>(TokenType::DIV, "/");
        }
        if(m_currentChar == '(')
        {
            advance();
            return std::make_shared<Token>(TokenType::LPAREN, "(");
        }
        if(m_currentChar == ')')
        {
            advance();
            return std::make_shared<Token>(TokenType::RPAREN, ")");
        }
        if(m_currentChar == '\n')
        {
            advance();
            return std::make_shared<Token>(TokenType::END_OF_LINE, "\n");
        }
        if(m_currentChar == '=') {
            advance();
            return std::make_shared<Token>(TokenType::ASSIGN, "=");
        }
        if(m_currentChar == '"' )
        {
           return std::make_shared<Token>(TokenType::STRING, string());
        }
        if(m_currentChar == '\t')
        {
            advance();
            return std::make_shared<Token>(TokenType::TAB, "\t");
        }
        if(m_currentChar == '>') {
            advance();
            return std::make_shared<Token>(TokenType::GREAT, ">");
        }
        if(m_currentChar == '<') {
            advance();
            return std::make_shared<Token>(TokenType::LESS, "<");
        }
        error();
    }
    return std::make_shared<Token>(TokenType::END_OF_FILE, "");
}


void Lexer::error() {
    throw "Error";
}


void Lexer::advance()
{
    m_pos ++;
    if (m_pos > m_text.length() - 1)
    {
        m_currentChar = EOF;
    }
    else
    {
        m_currentChar = m_text[m_pos];
    }
}

void Lexer::skipWhiteSpace()
{
    while (m_currentChar != EOF && std::isblank(m_currentChar)) {
        advance();
    }
}

int Lexer::integer()
{
    std::string result = "";
    while (m_currentChar != EOF && std::isdigit(m_currentChar)) {
        result += m_currentChar;
        advance();
    }
    return std::atoi(result.c_str());
}

std::string Lexer::string() {
    std::string result = "";
    advance();
    while (m_currentChar != EOF && m_currentChar != '"') {
        result += m_currentChar;
        advance();
    }
    advance();
    return result;
}

TokenPtr Lexer::id(){
    std::string result = "";
    while (m_currentChar != EOF && (std::isalpha(m_currentChar) || m_currentChar == '_')) {
        result += m_currentChar;
        advance();
    }
    const auto found = RESERVED_KEYWORDS.find(result);
    if(found != RESERVED_KEYWORDS.end()) {
        return found->second;
    } else {
        return std::make_shared<Token>(TokenType::ID, result);
    }
}
