#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#endif // TOKENTYPE_H


enum class TokenType {
    INTEGER,
    INTEGER_TYPE,
    STRING,
    STRING_TYPE,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    ID,
    VAR, // var
    ASSIGN, // =
    PRINT, // print
    IF,
    DO,
    TAB,
    LESS,
    GREAT,
    END_OF_LINE, // \n
    END_OF_FILE
};
