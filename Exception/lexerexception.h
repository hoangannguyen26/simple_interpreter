#ifndef LEXEREXCEPTION_H
#define LEXEREXCEPTION_H

#include "myexception.h"


class LexerException : public MyException
{
public:
    LexerException(const std::string& message);
};

#endif // LEXEREXCEPTION_H
