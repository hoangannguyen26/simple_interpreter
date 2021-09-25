#include <iostream>
#include "parser.h"
#include "lexer.h"
#include "interpreter.h"

using namespace std;

int main()
{
    const std::string expr = "var int b\n var int c\n c = 2 * 5\n\"Cai noi\"";

    const LexerPtr lexer = std::make_shared<Lexer>(expr);
    const ParserPtr parser = std::make_shared<Parser>(lexer);
    const InterpreterPtr interpreter = std::make_shared<Interpreter>(parser);
    BasicType result = interpreter->interpret();
}
