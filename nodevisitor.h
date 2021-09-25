#ifndef NODEVISITOR_H
#define NODEVISITOR_H
#include "Ast/ast.h"
#include "basictype.h"


class NodeVisitor
{
public:
    NodeVisitor() = default;
    BasicType visit(const ASTPtr& node);
protected:
    virtual BasicType visit_BinOp(const ASTPtr& node) = 0;
    virtual BasicType visit_Num(const ASTPtr& node) = 0;
    virtual BasicType visit_UnaryOp(const ASTPtr& node) = 0;
    virtual BasicType visit_Compound(const ASTPtr& node) = 0;
    virtual BasicType visit_Assign(const ASTPtr& node) = 0;
    virtual BasicType visit_Variable(const ASTPtr& node) = 0;
    virtual BasicType visit_VarDecl(const ASTPtr &node) = 0;
    virtual BasicType visit_Type(const ASTPtr &node) = 0;
};


#endif // NODEVISITOR_H
