#ifndef NODEVISITOR_H
#define NODEVISITOR_H

#include "Ast/ast.h"
#include "variant.h"

class NodeVisitor
{
#define CREATE_VISITOR(visitor) virtual Variant visit_##visitor(const ASTPtr &node) = 0
#define OVERRIDE_VISITOR(visitor) Variant visit_##visitor(const ASTPtr &node) override
public:
    NodeVisitor() = default;
    Variant visit(const ASTPtr &node);

protected:
    CREATE_VISITOR(BinOp);
    CREATE_VISITOR(Literal);
    CREATE_VISITOR(UnaryOp);
    CREATE_VISITOR(Block);
    CREATE_VISITOR(Assign);
    CREATE_VISITOR(Variable);
    CREATE_VISITOR(VarDecl);
    CREATE_VISITOR(Type);
    CREATE_VISITOR(Print);
    CREATE_VISITOR(IfCondition);
    CREATE_VISITOR(DoLoop);
    CREATE_VISITOR(ToString);
    CREATE_VISITOR(ToInt);
};

#endif // NODEVISITOR_H
