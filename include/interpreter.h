#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"
#include "nodevisitor.h"

#include <map>


class Interpreter : public NodeVisitor
{
public:
    explicit                            Interpreter(const ParserPtr& parser);
    BasicType                           interpret();
private:
    ParserPtr                           m_parser;
    std::map<std::string, BasicType>    m_globalScope;
    BasicType                           getVariableValue(const std::string& variableName) const;
    BasicType                           error(const std::string& message = "") const;
    TokenPtr                            m_currentToken;

    OVERRIDE_VISITOR(BinOp);
    OVERRIDE_VISITOR(Literal);
    OVERRIDE_VISITOR(UnaryOp);
    OVERRIDE_VISITOR(Block);
    OVERRIDE_VISITOR(Assign);
    OVERRIDE_VISITOR(Variable);
    OVERRIDE_VISITOR(VarDecl);
    OVERRIDE_VISITOR(Type);
    OVERRIDE_VISITOR(Print);
    OVERRIDE_VISITOR(IfCondition);
    OVERRIDE_VISITOR(DoLoop);
    OVERRIDE_VISITOR(ToString);
    OVERRIDE_VISITOR(ToInt);
};

using InterpreterPtr = std::shared_ptr<Interpreter>;

#endif // INTERPRETER_H
