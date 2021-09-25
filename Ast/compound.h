#ifndef COMPOUND_H
#define COMPOUND_H
#include "ast.h"
#include <vector>


class Compound : public AST
{
public:
    Compound();
    std::vector<ASTPtr>         children;
};

CREATE_SHARED_PTR(Compound);

#endif // COMPOUND_H
