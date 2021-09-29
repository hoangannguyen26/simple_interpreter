#ifndef BASICTYPE_H
#define BASICTYPE_H

#include <string>
#include <typeinfo>
#include <iostream>


class BasicType
{
    enum class SupportType {
        Void,
        Int,
        String
    };

public:
    BasicType() = default;
    BasicType(int val): m_type(SupportType::Int), intVal(val), strVal("") {};
    BasicType(const std::string& val):m_type(SupportType::String), intVal(0), strVal(val) {};
    BasicType(const char val[100]):m_type(SupportType::String), intVal(0), strVal(val) {};

    int getInt() const {
        if(m_type == SupportType::Int) {
            return intVal;
        }
        throw std::bad_typeid();
        return 0;
    }

    std::string toString() const {
        if(m_type == SupportType::String)
        {
            return this->strVal;
        }
        else
        {
            return std::to_string(this->intVal);
        }
    }

    BasicType toInt() const {
        if(m_type == SupportType::Int)
        {
            return *this;
        }
        else
        {
            return BasicType(std::atoi(this->strVal.c_str()));
        }
    }

    BasicType& operator=(int i) {
        if(m_type != SupportType::Int) {
            throw std::bad_typeid();
        }
        intVal = i;
        return *this;
    }

    BasicType& operator=(const std::string& s) {
        if(m_type != SupportType::String) {
            throw std::bad_typeid();
        }
        intVal = 0;
        strVal = s;
        return *this;
    }

    BasicType operator+(const BasicType& other) {
        if(this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        BasicType ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal + other.intVal;
        ret.strVal = this->strVal + other.strVal;
        return ret;
    }

    bool operator>(const BasicType& other) {
        if(this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        if(this->m_type == SupportType::Int)
        {
            return this->intVal > other.intVal;
        }
        else
        {
            return this->strVal > other.strVal;
        }
    }

    bool operator<(const BasicType& other) {
        if(this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        if(this->m_type == SupportType::Int)
        {
            return this->intVal < other.intVal;
        }
        else
        {
            return this->strVal < other.strVal;
        }
    }

    bool operator==(const BasicType& other) {
        if(this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        if(this->m_type == SupportType::Int)
        {
            return this->intVal == other.intVal;
        }
        else
        {
            return this->strVal == other.strVal;
        }
    }

    bool operator!=(const BasicType& other) {
        return !(*this == other);
    }

    BasicType operator-(const BasicType& other) {
        if(this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        BasicType ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal - other.intVal;
        //        ret.strVal = this->strVal + other.strVal;
        return ret;
    }

    BasicType operator*(const BasicType& other) {
        if(this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        BasicType ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal * other.intVal;
        //        ret.strVal = this->strVal + other.strVal;
        return ret;
    }


    BasicType operator/(const BasicType& other) {
        if(this->m_type != other.m_type)
        {
            throw std::bad_typeid();
        }
        BasicType ret;
        ret.m_type = this->m_type;
        ret.intVal = this->intVal / other.intVal;
        //        ret.strVal = this->strVal + other.strVal;
        return ret;
    }

    BasicType operator-(){
        this->intVal = -this->intVal;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const BasicType& obj)
    {
        if(obj.m_type == SupportType::Int)
        {
            os << obj.intVal;
        } else if (obj.m_type == SupportType::String)
        {
            os << obj.strVal;
        }
        return os;
    }

private:
    int intVal = 0;
    std::string strVal = "";
    SupportType m_type = SupportType::Void;

};

#endif // BASICTYPE_H
