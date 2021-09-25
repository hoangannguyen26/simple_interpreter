#ifndef AST_H
#define AST_H

#include <memory>
#include "../basictype.h"


class AST
{
public:
    enum class NodeType {
        Num,
        BinOp,
        UnaryOp,
        NoOp,
        Var,
        Assign,
        Compound,
        Type,
        VarDecl,
        Block,
        Program
    };
public:
    explicit AST(const NodeType type) :
        m_type(type)
    {

    }
    virtual ~AST() {}
    NodeType m_type;
};

using ASTPtr = std::shared_ptr<AST>;

#endif // AST_H
