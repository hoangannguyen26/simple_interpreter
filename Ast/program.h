#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast.h"


class Program : public AST
{
public:
    Program();
};

CREATE_SHARED_PTR(Program);

#endif // PROGRAM_H
