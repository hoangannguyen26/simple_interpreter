cmake_minimum_required(VERSION 3.5)

project(SimpleInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SimpleInterpreter
    Ast/ast.cpp
    Ast/binop.cpp
    Ast/num.cpp
    Ast/unaryop.cpp
    Ast/noop.cpp
    Ast/var.cpp
    Ast/assign.cpp
    Ast/compound.cpp
    Ast/vardecl.cpp
    Ast/type.cpp
    basictype.cpp
    nodevisitor.cpp
    interpreter.cpp
    parser.cpp
    lexer.cpp
    token.cpp
    main.cpp
    )
