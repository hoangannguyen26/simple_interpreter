#ifndef BLOCK_H
#define BLOCK_H

#include "ast.h"


class Block : public AST
{
public:
    Block();
};

CREATE_SHARED_PTR(Block);

#endif // BLOCK_H
