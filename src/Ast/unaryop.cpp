#include "Ast/unaryop.h"

UnaryOp::UnaryOp(const TokenPtr &op, ASTPtr expr) : AST(NodeType::UnaryOp, op),
                                                    m_op(op),
                                                    m_expr(expr)
{
}
