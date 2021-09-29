#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>
#include <string>

class MyException : public std::exception
{
public:
    MyException(const std::string &message);
    virtual const char *what() const throw() override
    {
        return m_message.c_str();
    };

private:
    const std::string m_message;
};

#endif // MYEXCEPTION_H
