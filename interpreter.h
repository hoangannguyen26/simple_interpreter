#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "parser.h"
#include <map>
#include "nodevisitor.h"


class Interpreter : public NodeVisitor
{
public:
    explicit                Interpreter(const ParserPtr& parser);
    BasicType                     interpret();
private:
    ParserPtr           m_parser;
    std::map<std::string, BasicType>    GLOBAL_SCOPE;

    BasicType       visit_BinOp(const ASTPtr& node) override;
    BasicType       visit_Num(const ASTPtr& node) override;
    BasicType       visit_UnaryOp(const ASTPtr &node) override;
    BasicType       visit_Assign(const ASTPtr &node) override;
    BasicType       visit_Compound(const ASTPtr &node) override;
    BasicType       visit_Variable(const ASTPtr &node) override;
    BasicType       visit_VarDecl(const ASTPtr &node) override;
    BasicType       visit_Type(const ASTPtr &node) override;
};

using InterpreterPtr = std::shared_ptr<Interpreter>;

#endif // INTERPRETER_H
