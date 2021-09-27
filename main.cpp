#include <iostream>
#include "parser.h"
#include "lexer.h"
#include "interpreter.h"
#include <fstream>

int main(const int argc, const char** argv)
{
    std::string sourceName = "source.test";
    if(argc == 2) {
        sourceName = argv[1];
    } else {
        std::cout << "Usage: " <<  argv[0] << "source file " << std::endl;
//         exit(1);
    }

    // read source file
    std::ifstream file(sourceName);
    std::string source;
    if(file.is_open())
    {
        std::string line;
        while (getline(file, line)) {
            source += line + '\n';
        }
        file.close();
    }
    // remove last \n
    int len = source.length();
    source[len - 1] = EOF;
    const LexerPtr lexer = std::make_shared<Lexer>(source);
    const ParserPtr parser = std::make_shared<Parser>(lexer);
    const InterpreterPtr interpreter = std::make_shared<Interpreter>(parser);
    BasicType result = interpreter->interpret();
    return 0;
}
