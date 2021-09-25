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

    OVERRIDE_VISITOR(BinOp);
    OVERRIDE_VISITOR(Num);
    OVERRIDE_VISITOR(UnaryOp);
    OVERRIDE_VISITOR(Compound);
    OVERRIDE_VISITOR(Assign);
    OVERRIDE_VISITOR(Variable);
    OVERRIDE_VISITOR(VarDecl);
    OVERRIDE_VISITOR(Type);
    OVERRIDE_VISITOR(Print);
};

using InterpreterPtr = std::shared_ptr<Interpreter>;

#endif // INTERPRETER_H
