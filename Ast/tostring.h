#ifndef TOSTRING_H
#define TOSTRING_H

#include "ast.h"


class ToString : public AST
{
public:
    ToString(const TokenPtr& data);

    const TokenPtr        m_data;
};

CREATE_SHARED_PTR(ToString);

#endif // TOSTRING_H
