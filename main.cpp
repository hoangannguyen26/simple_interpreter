#include <iostream>
#include "parser.h"
#include "lexer.h"
#include "interpreter.h"

using namespace std;

int main()
{
    std::string source;
    source += "var string strVal                            \n";
    source += "var int c                                    \n" ;
    source += "c = 2 * 5                                    \n";
    source += "strVal=\"This is a string\"  + \"add\"       \n";
    source += "print strVal                                 \n";
    source += "print c                                      \n";
    source += "print \"Hello world\"                        \n";
    source += "print 10 + 23\n";
    source += "if\n";
    source += "\tprint \"Print in side IF\"\n";
    source += "print 10 + 23";

    const LexerPtr lexer = std::make_shared<Lexer>(source);
    const ParserPtr parser = std::make_shared<Parser>(lexer);
    const InterpreterPtr interpreter = std::make_shared<Interpreter>(parser);
    BasicType result = interpreter->interpret();
}
