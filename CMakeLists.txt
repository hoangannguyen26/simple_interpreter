cmake_minimum_required(VERSION 3.5)

project(SimpleInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SimpleInterpreter
    ${CMAKE_SOURCE_DIR}/Ast/ast.cpp
    ${CMAKE_SOURCE_DIR}/Ast/binop.cpp
    ${CMAKE_SOURCE_DIR}/Ast/literal.cpp
    ${CMAKE_SOURCE_DIR}/Ast/unaryop.cpp
    ${CMAKE_SOURCE_DIR}/Ast/noop.cpp
    ${CMAKE_SOURCE_DIR}/Ast/var.cpp
    ${CMAKE_SOURCE_DIR}/Ast/assign.cpp
    ${CMAKE_SOURCE_DIR}/Ast/block.cpp
    ${CMAKE_SOURCE_DIR}/Ast/vardecl.cpp
    ${CMAKE_SOURCE_DIR}/Ast/type.cpp
    ${CMAKE_SOURCE_DIR}/Ast/print.cpp
    ${CMAKE_SOURCE_DIR}/Ast/ifcondition.cpp
    ${CMAKE_SOURCE_DIR}/Ast/doloop.cpp
    ${CMAKE_SOURCE_DIR}/basictype.cpp
    ${CMAKE_SOURCE_DIR}/nodevisitor.cpp
    ${CMAKE_SOURCE_DIR}/interpreter.cpp
    ${CMAKE_SOURCE_DIR}/parser.cpp
    ${CMAKE_SOURCE_DIR}/lexer.cpp
    ${CMAKE_SOURCE_DIR}/token.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp
    )
message(STATUS "Working dir${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Working dir${CMAKE_SOURCE_DIR}")
ADD_CUSTOM_COMMAND(TARGET SimpleInterpreter
          POST_BUILD
          COMMENT "copying test data ${CMAKE_SOURCE_DIR}/testData/source.test"
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/testData/source.test ${CMAKE_CURRENT_BINARY_DIR}
)
