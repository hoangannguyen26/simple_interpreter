#include "block.h"

Block::Block(const TokenPtr& token):
    AST(NodeType::Block, token),
    children({})
{

}
