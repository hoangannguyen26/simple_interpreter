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
        Print,
        If,
        Do,
        ToString,
        ToInt
    };
public:
    explicit AST(const NodeType type, const TokenPtr& token) :
        m_type(type),
        m_token(token)
    {
    }
    virtual ~AST() {}
    NodeType m_type;
    const TokenPtr m_token;
};

CREATE_SHARED_PTR(AST);

#endif // AST_H
