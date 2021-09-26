#ifndef AST_H
#define AST_H

#include <memory>
#include "../basictype.h"
#include "../token.h"

#define CREATE_SHARED_PTR(name) using name##Ptr = std::shared_ptr<name>

class AST
{
public:
    enum class NodeType {
        Literal,
        BinOp,
        UnaryOp,
        NoOp,
        Var,
        Assign,
        Type,
        VarDecl,
        Block,
        Program,
        Print,
    };
public:
    explicit AST(const NodeType type) :
        m_type(type)
    {
    }
    virtual ~AST() {}
    NodeType m_type;
};

CREATE_SHARED_PTR(AST);

#endif // AST_H
