cmake_minimum_required(VERSION 3.5)

project(SimpleInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIRECTORIES})

message(STATUS "Working dir${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Working dir${CMAKE_SOURCE_DIR}")

add_executable(SimpleInterpreter
    ${SOURCE_DIR}/Ast/ast.cpp
    ${SOURCE_DIR}/Ast/binop.cpp
    ${SOURCE_DIR}/Ast/literal.cpp
    ${SOURCE_DIR}/Ast/unaryop.cpp
    ${SOURCE_DIR}/Ast/noop.cpp
    ${SOURCE_DIR}/Ast/var.cpp
    ${SOURCE_DIR}/Ast/assign.cpp
    ${SOURCE_DIR}/Ast/block.cpp
    ${SOURCE_DIR}/Ast/vardecl.cpp
    ${SOURCE_DIR}/Ast/type.cpp
    ${SOURCE_DIR}/Ast/print.cpp
    ${SOURCE_DIR}/Ast/ifcondition.cpp
    ${SOURCE_DIR}/Ast/doloop.cpp
    ${SOURCE_DIR}/Ast/tostring.cpp
    ${SOURCE_DIR}/Ast/toint.cpp
    ${SOURCE_DIR}/basictype.cpp
    ${SOURCE_DIR}/nodevisitor.cpp
    ${SOURCE_DIR}/interpreter.cpp
    ${SOURCE_DIR}/parser.cpp
    ${SOURCE_DIR}/lexer.cpp
    ${SOURCE_DIR}/token.cpp
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Exception/myexception.cpp
    ${SOURCE_DIR}/Exception/parserexception.cpp
    ${SOURCE_DIR}/Exception/lexerexception.cpp
    ${SOURCE_DIR}/Exception/interpreterexception.cpp
    )
ADD_CUSTOM_COMMAND(TARGET SimpleInterpreter
          POST_BUILD
          COMMENT "copying test data ${CMAKE_SOURCE_DIR}/testData/source.test"
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/testData/source.test ${CMAKE_CURRENT_BINARY_DIR}
)
