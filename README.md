### That is a very simple interpreter written in C++ (C++ 11) language.

### Refer idea from: https://ruslanspivak.com/lsbasi-part1/

### How to build
- `mkdir build`
- `cd build && cmake .. && make`

### How to run
`./SimpleInterpreter path_to_source_file`

### 1. Variable declaration:
    
- `var int test01`
- `var string test02`

Variable name must start with a letter

### 2. Variable initialization:
- `test01 = 10` or `test01 = 10 + 2 * 2 - (4 -2)`
- `test02 = "string"` or `test02 = "string" + "string1"`

### 3. Common math operations:
- interger: [+, -, *, /]
- string: [+]

### 4. Special operators:
- to print a sting to output: 

        print variable
- to convert string into an integer value

        var string test1 = “100”
        var int test2 = to_int test1
- to convert a number into a string

        var int test1 = 100
        var string test2 = to_string test1
        
### 4. Conditions:
- support only `<` and `>`

        If test > 10
                print test
        or
        if test2 > test1
                print “It’s bigger!”

### 5. Cycles:

        do 10
                print “It will be printed 10 times!”

----

### How to implement a new `statement`
- Refer to commit: https://github.com/hoangannguyen26/simple_interpreter/commit/98d245870128a9e6bc1d8637f21c2a4f8064d619. This commit holds the implementation of the DO statement.

+ Add a new token type that corresponding to the new `statement`: edit `token_type.h`

        enum class TokenType {
                INTEGER,
                INTEGER_TYPE,
                STRING,
                STRING_TYPE,
                ...
                NEW_TOKEN_TYPE
        };

+ Add new keyword if has: edit lexer.h

        std::map<std::string, TokenPtr> RESERVED_KEYWORDS = {
                {"var", std::make_shared<Token> (TokenType::VAR, "var")},
                {"int", std::make_shared<Token> (TokenType::INTEGER_TYPE, "int")},
                ...
                {"new_keyword", std::make_shared<Token> (TokenType::NEW_TOKEN_TYPE, "new_keyword")},
        };
+ then update `Lexer::getNextToken()` to handle for new token type.

+ Update the parser.cpp to parser for the new `statement`
        ASTPtr              do_statement();
        ASTPtr              to_int();
        ASTPtr              to_string();
        ...
        ASTPtr              new_statement();

+ Add a new AST (Abstract Syntax Tree) node for new `statement` in /Ast directory.
+ Update the the interpreter to handle the logic for new `statement`:
  + add a new visitor function for the new statement.
  + implement the logic of this statement in its visiter funtion.

