#include "Exception/lexerexception.h"

LexerException::LexerException(const std::string& message):
MyException("LexerException: " + message + '\n')
{

}
