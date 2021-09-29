#include "Exception/myexception.h"

MyException::MyException(const std::string& message):
    m_message(message)
{
}
