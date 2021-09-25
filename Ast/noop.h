#ifndef NOOP_H
#define NOOP_H
#include "ast.h"


class NoOp : public AST
{
public:
    NoOp();
};

using NoOpPtr = std::shared_ptr<NoOp>;

#endif // NOOP_H
