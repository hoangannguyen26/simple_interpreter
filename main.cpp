#include <iostream>
#include "parser.h"
#include "lexer.h"
#include "interpreter.h"

using namespace std;

int main()
{
    std::string source;
    source += "var string strVal\n";
    source += "var int c\n" ;
    source +=  "c = 2 * 5\n";
    source +=  "strVal=\"This is a string\"  + \"add\"";

    const LexerPtr lexer = std::make_shared<Lexer>(source);
    const ParserPtr parser = std::make_shared<Parser>(lexer);
    const InterpreterPtr interpreter = std::make_shared<Interpreter>(parser);
    BasicType result = interpreter->interpret();
}
