#ifndef VARIANT_H
#define VARIANT_H

#include <string>
#include <typeinfo>
#include <iostream>

class Variant
{
public:
    Variant() = default;
    Variant(int val) : m_type(Type::Int), intVal(val), strVal(""){};
    Variant(const std::string &val) : m_type(Type::String), intVal(0), strVal(val){};
    Variant(const char val[100]) : m_type(Type::String), intVal(0), strVal(val){};

    int getInt() const
    {
        if (m_type == Type::Int)
        {
            return intVal;
        }
        throw std::bad_typeid();
        return 0;
    }

    std::string toString() const
    {
        if (m_type == Type::String)
        {
            return this->strVal;
        }
        else
        {
            return std::to_string(this->intVal);
        }
    }

    Variant toInt() const
    {
        if (m_type == Type::Int)
        {
            return *this;
        }
        else
        {
            return Variant(std::atoi(this->strVal.c_str()));
        }
    }

    Variant &operator=(int i)
    {
        if (m_type != Type::Int)
        {
            throw std::bad_typeid();
        }
        intVal = i;
        return *this;
    }

    Variant &operator=(const std::string &s)
    {
        if (m_type != Type::String)
        {
            throw std::bad_typeid();
        }
        intVal = 0;
        strVal = s;
        return *this;
    }

    Variant operator+(const Variant &other)
    {
        if (this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        Variant ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal + other.intVal;
        ret.strVal = this->strVal + other.strVal;
        return ret;
    }

    bool operator>(const Variant &other)
    {
        if (this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        if (this->m_type == Type::Int)
        {
            return this->intVal > other.intVal;
        }
        else
        {
            return this->strVal > other.strVal;
        }
    }

    bool operator<(const Variant &other)
    {
        if (this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        if (this->m_type == Type::Int)
        {
            return this->intVal < other.intVal;
        }
        else
        {
            return this->strVal < other.strVal;
        }
    }

    bool operator==(const Variant &other)
    {
        if (this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        if (this->m_type == Type::Int)
        {
            return this->intVal == other.intVal;
        }
        else
        {
            return this->strVal == other.strVal;
        }
    }

    bool operator!=(const Variant &other)
    {
        return !(*this == other);
    }

    Variant operator-(const Variant &other)
    {
        if (this->m_type != Type::Int || this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        Variant ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal - other.intVal;
        return ret;
    }

    Variant operator*(const Variant &other)
    {
        if (this->m_type != Type::Int || this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        Variant ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal * other.intVal;
        return ret;
    }

    Variant operator/(const Variant &other)
    {
        if (this->m_type != Type::Int || this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        Variant ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal / other.intVal;
        //        ret.strVal = this->strVal + other.strVal;
        return ret;
    }

    Variant operator-()
    {
        this->intVal = -this->intVal;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Variant &obj)
    {
        if (obj.m_type == Type::Int)
        {
            os << obj.intVal;
        }
        else if (obj.m_type == Type::String)
        {
            os << obj.strVal;
        }
        return os;
    }

    bool isString() const
    {
        return m_type == Type::String;
    }

    bool isInteger() const
    {
        return m_type == Type::Int;
    }

private:
    enum class Type
    {
        Void,
        Int,
        String
    };
    int intVal = 0;
    std::string strVal = "";
    Type m_type = Type::Void;
};

#endif // VARIANT_H
