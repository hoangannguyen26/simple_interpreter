#ifndef BLOCK_H
#define BLOCK_H
#include "ast.h"
#include <vector>


class Block : public AST
{
public:
    Block(const TokenPtr& token);
    std::vector<ASTPtr>         children;
    const TokenPtr  m_token;
};

CREATE_SHARED_PTR(Block);

#endif // BLOCK_H
