# WordLang

**WordLang** is a programming language designed for natural language-style programming. It compiles to C language and supports operations on characters, words, and sentences, along with standard programming features like expressions, variable declarations, control structures, and I/O.

---

## Table of Contents

- [Features](#features)
- [Language Overview](#language-overview)
  - [Data Types](#data-types)
  - [Literals](#literals)
  - [Variable Declarations](#variable-declarations)
  - [Operators](#operators)
  - [Expressions](#expressions)
  - [Conditions](#conditions)
  - [Control Structures](#control-structures)
  - [Input/Output](#inputoutput)
- [Project Architecture](#project-architecture)
  - [Statement](#statement)
  - [Conditional Statement](#conditional-statement)
  - [Expression](#expression)
- [Compiler Architecture](#compiler-architecture)
- [Building the Compiler](#building-the-compiler)
- [Running a WordLang Program](#running-a-wordlang-program)
- [Tests](#tests)
- [Example](#example)
  - [Example Video](#example-video)
  - [Example Program](#example-program)

---

## Features

- Custom data types for handling language constructs (`int`, `char`, `word`, `sentence`)
- Expression support including concatenation, indexing, and subtraction
- Standard control flow: `if`, `else if`, `else`, `while`, `loop`
- Support for nested and general-purpose scoped blocks, including `if`, `else if`, `else`, `while`, and `loop`
- Symbol table stack and scoped environments with locally scoped variables automatically deleted after the scope ends
- Typed declarations and safe assignments
- Input/output commands with natural prompt formatting
- Lex and Yacc-based parsing
- Generates readable and runnable C code

---

## Language Overview

### Data Types

| Type       | Description                            |
| ---------- | -------------------------------------- |
| `int`      | Integer values as in C                 |
| `char`     | A single ASCII character (or empty)    |
| `word`     | A string without spaces                |
| `sentence` | Space-separated words ending with `\n` |

### Literals

| Type       | Format         | Example         |
| ---------- | -------------- | --------------- |
| `int`      | number         | `42`, `0`, `-1` |
| `char`     | `'x'`          | `'a'`, `''`     |
| `word`     | string literal | `"word"`        |
| `sentence` | ^sentence^     | `^hello world^` |

### Variable Declarations

#### Variable Naming

Variable names must start with a letter or `_`, followed by up to 31 letters or digits (maximum 32 characters total).

#### Examples
```
int _i1, a2345678923456789234567891234567, i3_3;
char _c1;
word w1, w2, w3;
sentence s1, s2;
```


### Operators

| Operator    | Meaning                                                                |
| ----------- | ---------------------------------------------------------------------- |
| `=`         | Assignment                                                             |
| `+`         | Integer addition                                                       |
| `-`         | Subtraction (or remove char/word)                                      |
| `#`         | Concatenation                                                          |
| `:`         | Text indexing                                                          |
| `== !=`     | Equality / Inequality                                                  |
| `< > <= >=` | Numeric (`int`), Lexicographic (`char`, `word`, `sentence`) comparison |
| `!`         | Logical negation                                                       |
| `()`        | Parentheses for precedence                                             |

### Expressions

| Example             | Result         | Result Type |
| ------------------- | -------------- | ----------- |
| `-3`                | `-3`           | `int`       |
| `10 - 3`            | `7`            | `int`       |
| `-10 + 3`           | `-7`           | `int`       |
| `"Word" : 1`        | `'o'`          | `char`      |
| `'H' # 'i'`         | `"Hi"`         | `word`      |
| `"Hello" # "World"` | `"HelloWorld"` | `word`      |
| `^Hello World^ : 1` | `"World"`      | `word`      |
| `"Hi" # ^there^`    | `^Hi there^`   | `sentence`  |

### Conditions

Conditions are expressions that evaluate to `true` or `false`. They support all data types (`char`, `word`, `sentence`, `int`) and include:

- `==`, `!=` for equality/inequality
- `<`, `>`, `<=`, `>=` for comparisons (lexicographic for `char`, `word`, `sentence`; numeric for `int`)
- `!` for logical negation

### Control Structures

WordLang supports standard control flows:

- `if (condition) { ... }`
- `else if (condition) { ... }`
- `else { ... }`
- `while (condition) { ... }`
- `loop (positive number) { ... }` — fixed-count loop

All control structures use scoped blocks with `{}`. Variables declared inside a block are locally scoped and deleted when the block ends.

### Input/Output

Use the `input` and `output` statements:

```
input "Prompt" variable;
output variable;
```

You can prompt using literal types (`'c'`, `"word"`, `^sentence^`, number) or string messages.

---

## Project Architecture

WordLang's compiler architecture follows an object-oriented-like approach using C structures and function dispatching. Each major component — statements, expressions, and conditionals — is modular, extensible, and handled via function sets.

### Statement

```c
typedef enum {
    LOOP_STATEMENT,
    WHILE_STATEMENT,
    CONDITIONAL_STATEMENT,
    SCOPE_STATEMENT,
    DECLARATION_STATEMENT,
    ASSIGNMENT_STATEMENT,
    OUTPUT_STATEMENT,
    INPUT_STATEMENT
} StatementType;

typedef struct Statement {
    StatementType type;
    void *data;
    struct Statement *next;
} Statement;
```

### Conditional Statement

```c
typedef enum {
    IF_CONDITIONAL,
    ELSE_CONDITIONAL
} ConditionalType;

typedef struct ConditionalStatement {
    ConditionalType type;
    void *data;
    struct ConditionalStatement *next;
} ConditionalStatement;
```

### Expression

```c
typedef enum {
    LITERAL_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    UNARY_EXPRESSION,
    BINARY_EXPRESSION
} ExpressionType;

typedef struct Expression {
    ExpressionType type;
    void *data;
} Expression;
```


### Unified Lifecycle per Module

Each module type has the following lifecycle support:

- **Create** — dynamic memory allocation and setup
- **Execute / Evaluate** — runtime logic per type
- **Print** — C code generation output
- **Destroy** — safe deallocation and cleanup

This design enables clean separation of logic, easy extensibility, and reusable code.

---

## Compiler Architecture

The compiler is built using **Flex** and **Bison** to tokenize and parse WordLang code. The pipeline:

1. **Lexer:** Tokenizes `.wl` source
2. **Parser:** Validates syntax and builds an AST
3. **CodeGen:** Converts AST to readable C code
4. **Runtime:** Prints generated `.c` to stdout or a file

---

## Building the Compiler

Use the provided `Makefile`:

```bash
make
```

This generates the `wordlang` compiler.

---

## Running a WordLang Program

To compile and run a `.wl` file:

```bash
make run FILE=example.wl
```

---

## Tests

Test programs cover:

- Literal expressions
- Input/output
- Indexing
- Concatenation
- Arithmetic and subtraction
- Booleans and conditions
- Control flows and scopes

Run all:

```bash
make run
```

---

## Example

### Example Video
[![Watch the video](https://img.youtube.com/vi/v3rO4DIA14k/0.jpg)](https://www.youtube.com/watch?v=v3rO4DIA14k)

### Example Program
```
word w1;
sentence s1, adverb;
loop (3)
    adverb = adverb # "very";
w1 = "interesting";
s1 = ^Compilers are a^ # adverb # w1;
output s1 # "topic"; //Outputs: Compilers are a very very very interesting topic
word object, article;
char notVowel;
input ^What are you holding?^ object;
notVowel = object:0;
notVowel = notVowel - 'a' - 'e' - 'i' - 'o' - 'u';
s1 = ^You are holding^;
if (notVowel) article="a";
else article="an";
output s1 # article # object; // Outputs: You are holding {a | an}
// for example: You are holding an apple
// for example: You are holding a hammer
word last; // Flip Sentence (works only if words are distinct)
last = s1:-1;
while (s1:0 != last) {
    w1 = s1:0;
    s1 = (s1 - w1) # w1;
}
output s1; // Outputs: <object> {a | an} holding are You

char b, e, palindrome; // Find Palindrome (works only if no more than 2 equal chars)
word savWord;
palindrome = 'Y';
input ^Enter a word:^ w1; // For example: racecar
savWord = w1;
while (w1) {
    b = w1:0;
    e = w1:-1;
    if (palindrome == 'Y')
        if (e != b)
            palindrome = 'N';
    w1 = w1 - b - e;
}
if (palindrome == 'Y')
    output savWord # ^is a palindrome word^; //In example: racecar is a palindrome word
else
    output savWord # ^is not a palindrome^;

// Sort words in s1. For example: ^apple an holding are you^
s1 = ^apple an holding are you^;
int i, j, count;
count=0;
while (s1:count)
    count = count + 1;
sentence s;
while (count>1) {
    i = 0;
    loop (count-1) {
        if (s1:i > s1:(i+1)) {
            s = ^^;
            j=0;
            loop(i) {
                s = s # s1:j;
                j = j + 1;
            }
            s = s # s1:(i+1);
            s = s # s1:i;
            j = j + 2;
            loop (count-j) {
                s = s # s1:j;
                j = j + 1;
            }
            s1 = s;
        }
        i = i +1;
    }
    count = count-1;
}
output s1; // In example: ^an apple are holding You^
```