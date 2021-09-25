#ifndef PRINT_H
#define PRINT_H
#include "ast.h"

class Print : public AST
{
public:
    Print(const TokenPtr& token) :
        AST(NodeType::Print),
        m_token(token){

        };
    const TokenPtr        m_token;
};

CREATE_SHARED_PTR(Print);

#endif // PRINT_H
