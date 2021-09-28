### That is a very simple interpreter written in C++ (C++ 11) language.

### Refer idea from: https://ruslanspivak.com/lsbasi-part1/

### How to build
- `mkdir buidl`
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