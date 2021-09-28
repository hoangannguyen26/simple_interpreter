#include "lexer.h"
#include "Exception/lexerexception.h"

Lexer::Lexer(const std::string& text):
    m_text(text),
    m_pos(0),
    m_currentChar(m_text[m_pos]),
    m_currentLine(1)
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
            return std::make_shared<Token>(TokenType::INTEGER, integer(), m_currentLine);
        }
        if(m_currentChar == '+')
        {
            advance();
            return std::make_shared<Token>(TokenType::PLUS, "+", m_currentLine);
        }
        if(m_currentChar == '-')
        {
            advance();
            return std::make_shared<Token>(TokenType::MINUS, "-", m_currentLine);
        }
        if(m_currentChar == '*')
        {
            advance();
            return std::make_shared<Token>(TokenType::MUL, "*", m_currentLine);
        }
        if(m_currentChar == '/')
        {
            advance();
            return std::make_shared<Token>(TokenType::DIV, "/", m_currentLine);
        }
        if(m_currentChar == '(')
        {
            advance();
            return std::make_shared<Token>(TokenType::LPAREN, "(", m_currentLine);
        }
        if(m_currentChar == ')')
        {
            advance();
            return std::make_shared<Token>(TokenType::RPAREN, ")", m_currentLine);
        }
        if(m_currentChar == '\n')
        {
            m_currentLine++;
            advance();
            return std::make_shared<Token>(TokenType::END_OF_LINE, "\n", m_currentLine);
        }
        if(m_currentChar == '=') {
            advance();
            return std::make_shared<Token>(TokenType::ASSIGN, "=", m_currentLine);
        }
        if(m_currentChar == '"' )
        {
           return std::make_shared<Token>(TokenType::STRING, string(), m_currentLine);
        }
        if(m_currentChar == '\t')
        {
            advance();
            return std::make_shared<Token>(TokenType::TAB, "\t", m_currentLine);
        }
        if(m_currentChar == '>') {
            advance();
            return std::make_shared<Token>(TokenType::GREAT, ">", m_currentLine);
        }
        if(m_currentChar == '<') {
            advance();
            return std::make_shared<Token>(TokenType::LESS, "<", m_currentLine);
        }
        error();
    }
    return std::make_shared<Token>(TokenType::END_OF_FILE, "", m_currentLine);
}


void Lexer::error() {
    throw LexerException("Error at line: " + std::to_string(m_currentLine) + " character " + m_currentChar);
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
        found->second->setLine(m_currentLine);
        return found->second;
    } else {
        return std::make_shared<Token>(TokenType::ID, result, m_currentLine);
    }
}
