#ifndef TOINT_H
#define TOINT_H

#include "ast.h"

class ToInt : public AST
{
public:
    ToInt(const TokenPtr &data);

    const TokenPtr m_data;
};

CREATE_SHARED_PTR(ToInt);

#endif // TOINT_H
