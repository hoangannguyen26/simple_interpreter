#ifndef NOOP_H
#define NOOP_H

#include "ast.h"

class NoOp : public AST
{
public:
    NoOp(const TokenPtr &token);
};

CREATE_SHARED_PTR(NoOp);

#endif // NOOP_H
