#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H
#include "myexception.h"

class ParserException : public MyException
{
public:
    ParserException(const std::string& message);
};

#endif // PARSEREXCEPTION_H
