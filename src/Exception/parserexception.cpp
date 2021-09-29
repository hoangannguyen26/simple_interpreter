#include "Exception/parserexception.h"

ParserException::ParserException(const std::string& message):
    MyException("ParserException: " + message + "\n")
{
}
