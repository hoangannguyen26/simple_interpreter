#ifndef INTERPRETEREXCEPTION_H
#define INTERPRETEREXCEPTION_H

#include "myexception.h"


class InterpreterException : public MyException
{
public:
    InterpreterException(const std::string& message);
};

#endif // INTERPRETEREXCEPTION_H
