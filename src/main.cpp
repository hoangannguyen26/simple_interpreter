#include "parser.h"
#include "lexer.h"
#include "interpreter.h"
#include "Exception/myexception.h"

#include <iostream>
#include <fstream>

int main(const int argc, const char** argv)
{
    std::string sourceName = "source.test";
    if(argc >= 2) {
        sourceName = argv[1];
    } else {
        std::cout << "Source is not specified." << std::endl;
        std::cout << "Usage: " <<  argv[0] << " path_to_source_file" << std::endl;
        exit(1);
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
    } else {
        std::cout<<"Error: could not open file `" + sourceName +"`" << std::endl;
        exit(1);
    }
    // remove last \n
    int len = source.length();
    source[len - 1] = EOF;
    const LexerPtr lexer = std::make_shared<Lexer>(source);
    const ParserPtr parser = std::make_shared<Parser>(lexer);
    const InterpreterPtr interpreter = std::make_shared<Interpreter>(parser);

    try {
        interpreter->interpret();
    } catch (const MyException& e) {
        std::cout << std::endl << e.what() << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
