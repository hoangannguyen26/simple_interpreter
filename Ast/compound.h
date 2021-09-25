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

using CompoundPtr = std::shared_ptr<Compound>;

#endif // COMPOUND_H
