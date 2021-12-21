# Compiler design note

The readme file combines all TA's instruction and all definitions to the P language's lexical, syntax and semantics. The source code for lexical definition and syntax analysis are in the `src` directory. Abstract syntax tree was built using Visitor design pattern and the source files are in `src/lib`. The code for semantics analysis can be found in `lib/sema`.

A sample code of P program can be seen as below: 

```pascal
//&T-
ReadStatement;
begin
    var arr: array 10 of array 90 of integer;
    var constant: 010;

    read i;
    read arr[1][3][2];

    read arr[1];

    read constant;
    for i := 10 to 40 do
    begin
        read i;
    end
    end do
end
end

```



# Part 1 Lexical Definition- Scanner implementation

## Character Set

**`P`** programs are formed from ASCII characters. Control characters are not used in the language's definition except **`\n`** (line feed) and **`\t`** (horizontal tab).

## Lexical Definition

Tokens are divided into two classes: tokens that will be passed to the parser and tokens that will be discarded by the scanner (i.e. recognized but not passed to the parser).

### Tokens That Will Be Passed to the Parser

The following tokens will be recognized by the scanner and will be eventually passed to the parser:

#### Delimiters

  Each of these delimiters should be passed back to the parser as a token.

||Delimiter|
|:-:|:-:|
|comma|**`,`**|
|semicolon|**`;`**|
|colon|**`:`**|
|parentheses| **`(`**, **`)`**|
|square brackets| **`[`**, **`]`**|

#### Arithmetic, Relational, and Logical Operators

  Each of these operators should be passed back to the parser as a token.

||Operator|
|:-:|:-:|
|addition|**`+`**|
|subtraction|**`-`**|
|multiplication|**`*`**|
|division| **`/`**, **`mod`**|
|assignment|**`:=`**|
|relational| **`<`**, **`<=`**, **`<>`**, **`>=`**, **`>`**, **`=`** |
|logical|**`and`**, **`or`**, **`not`**|

#### Keywords

  The following keywords are reserved words of **`P`** (Note that the case is significant):

  + **`array`**, **`begin`**, **`boolean`**, **`def`**, **`do`**, **`else`**, **`end`**, **`false`**, **`for`**, **`integer`**, **`if`**, **`of`**, **`print`**, **`read`**, **`real`**, **`string`**, **`then`**, **`to`**, **`true`**, **`return`**, **`var`**, **`while`**

  Each of these keywords should be passed back to the parser as a token.

#### Identifiers

  An identifier is a string of letters and digits beginning with a letter. Case of letters is relevant, i.e. **ident**, **Ident**, and **IDENT** are different identifiers. Note that keywords are not identifiers.

#### Integer Constants

  A sequence of one or more digits. An integer that begins with 0 and followed by other digits is assumed to be **octal**; otherwise, it is assumed to be **decimal**.

#### Floating-Point Constants

  A dot **`.`** symbol separating the integral part from the fractional part. While integral part is a decimal number and fractional part is a sequence of one or more digits without any redundant **`0`**.

  > Note that `009.1` is a valid input in **`P`** (whether `009.1` is a valid syntax should not be the lexer's concern) because the input would be recognized as two seperate tokens: `00` (an octal integer constant) and `9.1` (a floating-point constant).

  > Moreover, `0.0` is a valid floating-point constant because there are no redundant `0`s in both side of the dot symbol.

#### Scientific Notations

  A way of writing numbers that accommodates values too large or small to be conveniently written in standard decimal notation. All numbers are written like **`aEb`** or **`aeb`** (**`a`** times ten to the power of **`b`**), where the exponent **`b`** is a **decimal integer** (see [Integer Constants](#integer-constants)) with the optional sign and the coefficient **`a`** is any real number, called the significand, a decimal integer or floating-point number.

  For example: `1.23E4`, `1.23E+4`, `1.23E-4`, `123E4`, etc.

#### String Constants

  A string constant is a sequence of zero or more ASCII characters appearing between double-quote (`"`) delimiters. String constants should not contain embedded newlines. A double-quote appearing with a string must be written twice. For example, `"aa""bb"` denotes
  the string constant `aa"bb`.

### Tokens That Will Be Discarded

The following tokens will be recognized by the scanner, but should be discarded rather than passing back to the parser.

#### Whitespace

  A sequence of blanks (spaces) tabs, and newlines.

#### Comments

  Comments can be denoted in two ways:

  + *C-style* is text surrounded by **`/*`** , and **`*/`** delimiters, which may span more than one line;

    Noted that C-style comments **don't "nest"**. Namely, **`/*`** always closes with the first **`*/`**.
  + *C++-style* is text following a **`//`** delimiter running up to the end of the line.

  Whichever comment style is encountered first remains in effect until the appropriate comment close is encountered. For example

      // this is a comment // line  */ /* with some /* delimiters */  before the end
    
      /* this is a comment // line with some /* and	\\
      // delimiters */

  are both valid comments.

#### Pseudocomments

  A special form of  *C++-style* comments, called  **`pseudocomments`**, are used to signal options to the scanner.
  Each **`pseudocomment`** consists of a *C++-style* comment delimiter, a character **`&`**, an upper-case letter, and either a  **`+`** or **`-`** (**`+`** turns the option "on" and **`-`** turns the option "off" ). In other words, each **`pseudocomment`** either has the form `//&C+` or the form `//&C-` where `C` denotes the option.

  There may be up to 26 different options (A-Z). Specific options will be defined in the project description. A comment that does not match the option pattern exactly has no effect on the option settings.  Undefined options have no special meaning, i.e. such **`pseudocomments`** are treated as regular comments.

  For this project, define two options, **`S`** and **`T`**. **`S`** turns **source program listing** on or off, and **`T`** turns **token listing** on or off. The effect of options starts from current line of code. By default, both options are on. For example, the following comments are **`pseudocomments`** :
  + `//&S+`
  + `//&S-`
  + `//&S+&S-`  _**This leaves the `S` option on because the rest of the comment is ignored**_



## What the Scanner is capable of 

Your goal is to have your scanner print tokens and lines, based on **`S`**(source program listing), **`T`**(token listing) options.

+ If **`S`** (listing option) is on, each line should be listed, along with a line number.
+ If **`T`** (token option) is on, each token should be printed on a separate line, surrounded by angle brackets.

For example, given the input:

```pascal
// print hello world
begin
var a : integer;
var b : real;
print "hello world";
a := 1+1;
b := 1.23;
if a > 01 then
b := b*1.23e-1;
//&S-
a := 1;
//&S+
//&T-
a := 2;
//&T+
end if
end
```

Your scanner should output:

```pascal
1: // print hello world
<KWbegin>
2: begin
<KWvar>
<id: a>
<:>
<KWinteger>
<;>
3: var a : integer;
<KWvar>
<id: b>
<:>
<KWreal>
<;>
4: var b : real;
<KWprint>
<string: hello world>
<;>
5: print "hello world";
<id: a>
<:=>
<integer: 1>
<+>
<integer: 1>
<;>
6: a := 1+1;
<id: b>
<:=>
<float: 1.23>
<;>
7: b := 1.23;
<KWif>
<id: a>
<>>
<oct_integer: 01>
<KWthen>
8: if a > 01 then
<id: b>
<:=>
<id: b>
<*>
<scientific: 1.23e-1>
<;>
9: b := b*1.23e-1;
<id: a>
<:=>
<integer: 1>
<;>
12: //&S+
13: //&T-
14: a := 2;
15: //&T+
<KWend>
<KWif>
16: end if
<KWend>
17: end
```

### Error Handling

  If no rule matches the input pattern, print the line number and the first character and then abort the program. The output should be the following format which will be covered in template.

> `Error at line 3: bad character "$"`


# Part2 Syntactic Definitions- Parser Implementation

A `p` language parser will be implemented using LALR(1) grammar. The parser source code is prodiced by using `yacc`.

Once the LALR(1) grammar `yacc` is to produce a C program called `"parser.c"`, which contains the parsing function `yyparse()`.  The parsing function `yyparse()` calls `yylex()`(which is contained in C program produced by `flex`).

## Syntactic Definitions

### Program Units

The two program units are the *program* and the *functions*.

 - #### Program

    A program has the form:

        identifier;
        <zero or more variable and constant declaration>
        <zero or more function declaration and definition>
        <one compound statement>
        end

    A program has no arguments, and hence no parentheses are present in the header. There are two types of variables in a program:

    - **global variables:**   declared after the identifier but before the compound statement
    - **local variables:**   declared inside the compound statement and functions 

 - #### Function

    A function declaration has the following form:

        identifier (<zero or more formal arguments>): scalar_type;

    A function definition has the following form:

        identifier (<zero or more formal arguments>): scalar_type
        <one compound statement>
        end

    Parentheses are required even if no arguments are declared. No functions may be declared inside a function.

    The formal arguments are declared in a formal argument section, which is a list of declaration separated by semicolons. Each declaration has the form

        identifier_list: type

    where identifier_list is a list of identifier separated by comma:

        identifier, identifier, ..., identifier

    At least one identifier must appear before each colon, which is followed by exactly one type(include array) specification. Note that if arrays are to be passed as arguments, they must be fully declared. All arguments are passed by values.

    Functions may return one value or no value at all. Consequently, the return value declaration is either a type name or is empty. If no return value is declared, there is no colon before the terminating semicolon. A function that returns no value can be called a `"procedure"`. For example, following are valid function declaration headers:

        func1(x, y: integer; z: string): boolean;
        func2(a: boolean): string;
        func3();        // procedure
        func4(b: real); // procedure
        func5(): integer;

### Data Types and Declarations

 - #### Variable

    The four predefined scalar data types are `integer`, `real`, `string`, and `boolean`. The only structured type is the `array`. A variable declaration has the form:

        var identifier_list: scalar_type;

    or

        var identifier_list: array integer_constant of type;

    where integer_constant should be a non-negative integer constant which represents the size of the array.

 - #### Constant

    A constant declaration has the form:

        var identifier_list: literal_constant;

    where literal_constant is a constant of the proper type (e.g. an integer or real literal w/ or w/o a negative sign, string literal, true, or false).

    > Note that assignments to constants are not allowed and constants can not be declared in terms of other named constants. Variables may not be initialized in declarations.

### Statements

There are seven distinct types of statements: compound, simple, conditional, while, for, return, and procedure call.

 - #### compound

    A compound statement consists of a block of statements delimited by the keywords `begin` and `end`, and an optional variable and constant declaration section:

        begin
        <zero or more variable and constant declaration>
        <zero or more statements>
        end

    Note that declarations inside a compound statement are local to the statements in the block and no longer exist after the block is exited.

 - #### simple

    The simple statement has the form:

        variable_reference := expression;

    or

        print variable_reference;

    or

        print expression;

    or

        read variable_reference;

    A *variable_reference* can be simply an *identifier* or an *array_reference* in the form of

        identifier [expression] [expression] [...]

 - #### conditional

    The conditional statement may appear in two forms:

        if expression then
        <one compound statement>
        else
        <one compound statement>
        end if

    or

        if exprression then
        <one compound statement>
        end if

 - #### while

    The while statement has the form:

        while expression do
        <one compound statement>
        end do

 - #### for

    The for statement has the form:

        for identifier := integer_constant to integer_constant do
        <one compound statement>
        end do

 - #### return

    The return statement has the form:

        return expression ;

 - #### procedure call

    A procedure is a function that has no return value. A procedure call is then an invocation of such a function. It has the following form:

        identifier (<expressions separated by zero or more comma>) ;

### Expressions

Arithmetic expressions are written in infix notation, using the following operators with the precedence:

||Operator|
|:-:|:-:|
|negative|**`-`**|
|multiplication|**`*`**|
|division| **`/`**, **`mod`**|
|addition|**`+`**|
|subtraction|**`-`**|
|relational| **`<`**, **`<=`**, **`<>`**, **`>=`**, **`>`**, **`=`** |
|logical|**`and`**, **`or`**, **`not`**|

Note that:

1. The token **"-"** can be either the **binary subtraction** operator, or the **unary negation** operator. Associativity is the left. Parentheses may be used to group subexpressions to dictate a different precedence. Valid components of an expression include **literal constants**, **variable reference**, **function invocations**

2. The part of semantic checking will be handled in the part of semantic analysis. In this part, you don't need to check semantic errors like **"a := 3 + true;"**. Just take care of syntactic errors!

3. Consecutive operators are **not** legal in an expression. (e.g. `--a` or `not not a`)

 - The **function invocation** has the form:

        identifier (<expression separated by zero or more comma>)

## The Parser is capable of:

The parser should list information according to **Opt_S** and **Opt_T** options (the same as Project 1).  If the input file is syntactically correct, print

    |--------------------------------|
    |  There is no syntactic error!  |
    |--------------------------------|

Once the parser encounters a syntactic error, print an error message in the form of

    |--------------------------------------------------------------------------
    | Error found in Line #[ line number where the error occurs ]: [ source code of that line ]
    |
    | Unmatched token: [ the token that is not recognized ]
    |--------------------------------------------------------------------------

# Part 3 Constructing Abstract Syntax Trees


## Overview

In this part, you will extend your parser to construct an abstract syntax tree (AST) for a given program written in **`P`** language using the information provided by previous assignments and to dump this AST in the designated format using visitor pattern.

### 0x00. Introduction to Abstract Syntax Tree

In the previous part, we have recognized the structure of the input program, and then we need to perform further tasks, such as semantic analysis, code generation, based on it in the latter assignments. However, writing YACC actions for all the tasks makes your codes gnarly and inflexible.
Therefore, we need some data structure to record the essential information along with the structure of the input program. After that, we can perform those tasks on that data structure individually.

An Abstract Syntax Tree (AST) is a way of representing the syntax of a programming language as a hierarchical tree-like structure. The tree represents all of the constructs in the language and their subsequent rules. Some language constructs, such as if-else conditional and function declaration in `P` language, are made up of simpler constructs, such as variables and statements.

Consequently, the root of an AST of a program represents the entire program, and each node within the AST either has one or more children that represent its constituent parts or represents a basic construct (e.g., a constant or a variable reference) per se.

Let's look at a simple example:

```pascal
sample;

begin
  var a: 100;
  var b: 101;
  if a < b then
  begin
    print 55146;
  end
  else
  begin
    print 22146;
  end
  end if
end
end
```

First, we have a `ProgramNode` as the root of our AST. The `ProgramNode` has an arbitrary number of child nodes, which can be a global (constant) variable declaration, a function declaration, or a program body, and each declaration forms a node. In this case, no declaration is made before the program body, so no declaration node is generated. The `ProgramNode` here has only one child node, which is a program body.

A program body is a `CompoundStatementNode` with an arbitrary number of child nodes:

- Local (constant) variable declarations
  - `var a: 100;`
  - `var b: 101;`
- Statement
  - `if ... else ... end if`

An `if` statement also has an arbitrary number of child nodes. In this case, it has the following child nodes:

- A conditional expression
  - `a < b`
- A compound statement as the if body
  - `begin ... end`
  - A statement in the if body
    - `print 55146;`
- A component statement as the else body
  - `begin ... end`
  - A statement in the else body
    - `print 22146;`

Each of these child nodes can be broken down further. For example, the conditional expression is a `BinaryOperatorNode` of `<` operation with two child nodes:

- A variable reference (left operand)
  - `a`
- A variable reference (right operand)
  - `b`

Here is the full AST for the aforementioned `P` program:

![ast example](./ast.jpeg)

And here's pseudocode for constructing an `IfNode` which is a subtree of the full AST:

```
// Construct if condition
conditional = BinaryOperatorNode(op=">", left_operand=VariableReferenceNode("a")
                                       , right_operand=VariableReferenceNode("b"))

// Construct if body
print = PrintNode(ConstantValueNode(55146))
compound = CompoundStatementNode([print])
if_body = compound

// Construct else body
print = PrintNode(ConstantValueNode(22146))
compound = CompoundStatementNode([print])
else_body = compound

// Construct if statement
if = IfNode(cond=conditional, body=if_body, else=else_body)
```

As you can see, AST can do exactly what we want, recording the essential information like the conditional expression of an `if` statement along with the structure (conditional expression as a child node of an `IfNode`). You're going to design and construct an AST for each given input program in this assignment.

---

### 0x01. Preparation for AST Construction

> Before starting this section, you're recommended to read the lecture note of `Yacc`, in particular, pages 10, 15 and 16.

Now we have a basic grasp of what AST is and what it's capable of. Let's get ready for AST construction with the help of the scanner and the parser we built in the previous assignments.

In the previous section, we may find that two key components of an AST are **the relationship between different nodes** and **the attributes of each node**. We will start with the relationship first.

In effect, the information of the relationship has been captured in the yacc rules written in the previous assignment. All we need is to preserve this relationship in our AST. Take the `print` statement for example:

```
print:
  PRINT Expression SEMICOLON
;

Expression:
    LiteralConstant
    |
    ...
;

LiteralConstant:
    INT_LITERAL
    |
    ...
;
```

Assume that both a `print` statement and a `literal constant` form a node in the AST, you can see that **a `PrintNode` "has" a ConstantValueNode.** We preserve this [**has-a** relationship](https://en.wikipedia.org/wiki/Has-a) through the appropriate design of class `PrintNode`. We'll talk about it in the next section.

---

Next, we also need to store related attribute information when preserving the relationship in the AST. For example:

```
print 55146;
```

Given the code above to our compiler, the scanner tokenizes the string into a series of tokens and then the parser recognizes them as a `print` statement.

After that, we need to extract more information from them for making our AST more expressive. In this case, we extract constant value - 55146 from the string "55146" and the `ConstantValueNode` captures that value as its member. This allows later phases of the compiler (e.g., semantic analysis) to know what the printed value is.

In order to provide the attribute information when performing AST construction, it is variable `yylval`'s turn to play. We may have a regular expression for the decimal integer in `scanner.l`:

```lex
0|[1-9][0-9]*
```

And we add the codes for storing the attribute information in the corresponding lex action:

```lex
0|[1-9][0-9]* {
    yylval = strtol(yytext, NULL, 10);
    return INT_LITERAL;
}
```

Then in the routines of `yyparse()`, when it calls `yylex()` to get a token from a lexical analyzer and it recognizes an integer, the value of that recognized integer is assigned to variable `yylval`. We can then obtain that value in a YACC action through the pseudo-variable $1, $2, and so on.
Furthermore, the semantic values of the non-terminal components of the rule are also referred to the pseudo-variables, but some declarations need to be done before using them. We'll talk about it in the next section.

```
print:
    PRINT Expression SEMICOLON {
        // $2 represents the node constructed in the action of rule LiteralConstant -> INT_LITERAL
        $$ = PrintNode($2);
    }

Expression:
    LiteralConstant {
        $$ = $1;
    }
    |
    ...
LiteralConstant:
    INT_LITERAL {
        // store the recognized value
        $$ = ConstantValueNode(/* type */, /* value */ $1);
    }
    |
    ...
;
;
```

> You may see [this](http://dinosaur.compilertools.net/yacc/index.html) for the internal mechanism of how YACC preserves multiple values set by different lex actions. (Search for "yylval")

However, not all attributes are type integer. Here we can use the `%union` declaration to specify the entire collections of possible data types for semantic values stored in variable `yylval`. (More details can be found in lecture note of Yacc p.16 or [here](https://www.gnu.org/software/bison/manual/bison.html#Union-Decl).)

---

### 0x02. AST Construction

Let's build the AST!

First, we need to define the data structure of each node in the AST. We have to take a look at the requirements of each node so that we can determine how to design each class.

Take `ProgramNode`, `PrintNode` and `ConstantValueNode` for example:

- `ProgramNode`
  - Location
  - Name
  - Return type
  - ...
- `PrintNode`
    - Location
    - Target (an expression node)
- `ConstantValueNode`
  - Location
  - Constant value

> Specific requirements for each kind of node can be found in [AST-guideline.md](./ast_guideline.md).

You may notice that each kind of node has one common attribute - location. As a result, we can extract this common attribute from each kind of node and use inheritance rather than define it in each of them. After that, extend the derived class according to respective requirements if needed.

> More details about location information can be found in Section [Location Information](#location-information)

Initially, define a base class/struct called `AstNode` that other classes/structs will inherit from:

```c++
struct Location {
    uint32_t line;
    uint32_t col;
};

// C++ version
class AstNode {
  public:
    AstNode(const uint32_t line, const uint32_t col);

  public:
    Location location;
};

// C version
struct AstNode {
    struct Location location;
};
```

Then define the derived classes/structs `ProgramNode`, `PrintNode` and `ConstantValueNode`:

```c++
// C++ version
class ProgramNode : public AstNode {
  public:
    ProgramNode(const uint32_t line, const uint32_t col, const char *name);

  public:
    std::string name;
    // TODO: return type, ...
};

class PrintNode : public AstNode {
  public:
    PrintNode(const uint32_t line, const uint32_t col, AstNode *target);

  public:
    AstNode *target;
};

class ConstantValueNode : public AstNode {
  public:
    ConstantValueNode(const uint32_t line, const uint32_t col, const ConstantValue value);

  public:
    ConstantValue value;
};

// C version
struct ProgramNode {
    struct AstNode base;

    const char *name;
    // TODO: return type, ...
};

ProgramNode *newProgramNode(const uint32_t line, const uint32_t col, const char *name);

struct PrintNode {
  struct AstNode base;

  struct AstNode *target;
};

PrintNode *newPrintNode(const uint32_t line, const uint32_t col, AstNode *target);

struct ConstantValueNode {
    struct AstNode base;

    ConstantValue value;
};

ConstantValueNode *newConstantValueNode(const uint32_t line, const uint32_t col,
                                        ConstantValue value);

```

> The C++ code above only shows the rough design of the class. There is a lot more need to be done when using inheritance in C++. You're encouraged to delve into them for having a better quality of code.
>
> If you want to learn more about OOP in C, you can see [你所不知道的 C 語言：物件導向程式設計篇](https://hackmd.io/@sysprog/c-oop?type=view).

Note that a `PrintNode` should have an expression node, which can be a node of type `ConstantValueNode`, `VariableReferenceNode`, etc. Since a member can only be one type, we take advantage of the "is-a" relationship based on inheritance. This relationship allows us to treat a pointer to `ConstantValueNode` as a pointer to `AstNode` in C++ (google "C++ upcasting"), while you can also achieve this in C, but you need to take care of memory layout on your own. In this way, we successfully preserve the has-a relationship mentioned in the previous section.

After defining the data structure of nodes, we can construct the AST through writing yacc actions. (You don't have to finish all the definitions first. You can construct the AST while defining the data structure.) Take the `ProgramNode` as an example:

```yacc
Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END
;

ProgramName:
    ID
;
```

In the rule of `Program`, there is a non-terminal `ProgramName`. We have to declare a type for it so that yacc/bison can replace the pseudo-variable with the correct member name of `union` (See [3.7.4 Nonterminal Symbols](https://www.gnu.org/software/bison/manual/bison.html#Symbol-Decls)). If you don't declare types for non-terminals, you may get the following error message:

```
parser.y:82.64-65: error: $1 of ‘Program’ has no declared type
```

Non-terminal `ProgramName` should have a semantic value that represents the program name. Therefore, we may have a member which is a pointer to `char` in the union declaration, and use the `%type` declaration to declare a type for `ProgramName`, like this:

```yacc
%union {
    char *identifier;
}

%type <identifier> ProgramName
```

Next, just like the previous section mentioned, we have to add the codes for storing the attribute information in the corresponding lex action. In this case, find the regular expression for the identifier and write some codes like below:

```lex
    /* Identifier */
[a-zA-Z][a-zA-Z0-9]* {
    TOKEN_STRING(id, yytext);
    yylval.identifier = strndup(yytext, /* MAX_ID_LENG */ 32u);
    return ID;
}
```

After that, you can write the yacc action to construct a `ProgramNode` which only has a location and a name as the member of `AstNode` and `ProgramNode` respectively:

```yacc
Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
        // C++ version
        root = new ProgramNode(@1.first_line, @1.first_column, $1 /* TODO: other members */);

        // C version
        root = newProgramNode(@1.first_line, @1.first_column, $1 /* TODO: other members */);
    }
;
```

As for the remaining members of the `ProgramNode` and other nodes, they are left for you to design and implement.

> :warning: **Warning again! Read Carefully.**
>
> - You may need to find a way to convey the type of `P` language. **DO NOT** use string for it. It might be a really simple and straightforward approach in this assignment, but it will be really annoying to deal with it when you need to extract some information from it.
> <br> Here is a suggestion: Use an `enum` and a list of integer for the scalar part and the structured part of type respectively.

---

### 0x03. AST Examination

Writing a big bunch of codes and then compile and test the result is often a non-stop ticket to late-night debugging hell, so it's important to **test your codes step by step when developing**.

For example, in the previous section, we have designed and implemented partial `AstNode` and `ProgramNode`. Thus we can test whether the construction is correct before moving on to the next one.

But how do we test it? Writing unit tests may be a good approach, but it's a bit out of scope (you can still do this if you want). Another approach may be using GDB to examine whether the data on the memory is as expected. However, it's still not practical. Here comes the most fundamental but familiar approach, the almighty `print`! Moreover, it happens to be one of the requirements for this assignment. Let's do this.

In order to dump the information of nodes, we have to consider two things:

1. Traversal
2. Output

In this assignment, we apply a **pre-order** traversal. When traversing nodes, we have to make different kinds of nodes dump their attributes in the corresponding format. Take `PrintNode` for example, it has a member which type is a pointer to `AstNode`. We need to let it output as it is a pointer to `ConstantValueNode` if that node represents statement `print 55146;`, and polymorphism is suitable for this scene.

The concept of polymorphism, in particular subtype polymorphism, is that "a call to a member function will cause a different function to be executed depending on the real type of object that invokes the function".
For example, let class/struct `AstNode` be a base class/struct, and there is a virtual member function `print` (you can use function pointer to achieve the same effect in C). Derived classes/structs (e.g., `ProgramNode`, `DeclarationNode`) then define their own implementation for member function `print`.

Consequently, the program can act like the C++ program below:

> Here only shows C++ codes, since it is simpler than C to illustrate the concept of polymorphism. As for C, you may see this [article](https://www.codeproject.com/Articles/108830/Inheritance-and-Polymorphism-in-C) and feel free to ask questions by opening issues in the Discussion repository.

```c++
// In ast.hpp
class AstNode {
  public:
    // other member functions

    virtual void print() = 0; // pure virtual function

  public:
    // data members
};

// In program.hpp
class ProgramNode : public AstNode {
  public:
    // other member functions

    void print() override;

  public:
    // data members
};

// In program.cpp
void ProgramNode::print() {
  std::printf("program <line: %u, col: %u> %s %s\n",
              location.line, location.col, name.c_str(), "void");
}

// In assignment.hpp
// basically same as program.hpp, omit it.

// In assignment.cpp
void AssignmentNode::print() {
  std::printf("assignment statement <line: %u, col: %u>\n");
}

// In main.cpp
ProgramNode *pn = new ProgramNode(/* ... */);
AssignmentNode *an = new AssignmentNode(/* ... */);

std::vector <AstNode *> nodes = {pn, an};

for (const AstNode *node : nodes) {
  node->print();
}

/*
Output:

program <line: 1, col: 1> test void
assignment statement <line: 15, col: 7>

*/
```

> If you're interested in the mechanism of the virtual function, you may want to know more about [vtable](https://www.learncpp.com/cpp-tutorial/125-the-virtual-table/).

With the help of polymorphism, we can make each node output in the right way when traversing.

As for when to dump the AST, since you will have a root node to represent the whole AST, you may dump it right after the execution of `yyparse()`:

```c++
int main(int argc, const char *argv[]) {
  // ...

  yyparse();

  root->print();

  // ...
}
```

So, here may be your workflow of developing:

1. Design and implement one kind of node partially or fully.
2. Write lex and yacc actions to construct the node.
3. Examine the construction by dumping that node.
4. Repeat 1 ~ 3. until all kinds of nodes have been done.

Now, you should have a basic idea of how to accomplish this assignment. However, we encourage you to read the [tutorial of visitor pattern](./tutorial/) and apply this pattern in your assignment rather than just using polymorphism.

## What the Parser is capable of :

Your parser should construct an AST, rooted at a Program node, after the execution of `yyparse()`. After that, you can dump the AST, perform semantic analyses or generate code directly upon the AST, rather than completing all the functionalities in the yacc actions.

Your parser should dump the AST when the flag `--dump-ast` is enabled. Use **pre-order traversal** while traversing your AST.

Let's look at a simple example:

```
$ ./parser test.p --dump-ast
1: //&T-
2: test;
3:
4: func( a: integer ; b: array 1 of array 2 of real ): boolean
5: begin
6:   var c: "hello world!";
7:   begin
8:     var d: real;
9:     return (b[1][4] >= 1.0);
10:   end
11: end
12: end
13:
14: begin
15:   var a: integer;
16:   begin
17:     var a: boolean;
18:   end
19: end
20: end
program <line: 2, col: 1> test void
  function declaration <line: 4, col: 1> func boolean (integer, real [1][2])
    declaration <line: 4, col: 7>
      variable <line: 4, col: 7> a integer
    declaration <line: 4, col: 20>
      variable <line: 4, col: 20> b real [1][2]
    compound statement <line: 5, col: 1>
      declaration <line: 6, col: 3>
        variable <line: 6, col: 7> c string
          constant <line: 6, col: 10> hello world!
      compound statement <line: 7, col: 3>
        declaration <line: 8, col: 5>
          variable <line: 8, col: 9> d real
        return statement <line: 9, col: 5>
          binary operator <line: 9, col: 21> >=
            variable reference <line: 9, col: 13> b
              constant <line: 9, col: 15> 1
              constant <line: 9, col: 18> 4
            constant <line: 9, col: 24> 1.000000
  compound statement <line: 14, col: 1>
    declaration <line: 15, col: 3>
      variable <line: 15, col: 7> a integer
    compound statement <line: 16, col: 3>
      declaration <line: 17, col: 5>
        variable <line: 17, col: 9> a boolean

|--------------------------------|
|  There is no syntactic error!  |
|--------------------------------|
```

# Part 4 Semantic Analyses implementation
## Overview

In this part, you will extend your parser to perform semantic analyses for a given program written in `P` language using the information recorded in the AST, which has been constructed in the previous part.

This part requires you to construct a symbol table for performing semantic analyses this time and code generation in the last part.
You should design it using feasible data structures.

### 0x00. Introduction to Symbol Table

In the previous part, we have constructed an AST for the given program. In a program, the most common behavior is that we declare some variables and use them later.
However, it's quite painful to walk back and forth between a declaration node and a variable reference node in the AST.

As a result, we need to maintain a data structure, symbol table, which stores some information when we encounter a declaration. After that, we can directly get information from the symbol table when a reference is analyzed instead of going back to find the declaration.

A symbol table is used for the following purposes:

- To pass information from declarations to uses
- To verify if a symbol has been declared before uses
- To help type checking when analyzing parts, operations, and return statement

**Components**

A symbol table is simply a table that contains entries for each name of program, functions, or variables. Each entry consists of the following components:

| Field | Description |
| ----- | ----------- |
| Name | The name of the symbol. Each symbol have the length between 1 to 32. The extra part of an identifier will be discarded. |
| Kind | The name type of the symbol. There are **six** kinds of symbols: program, function, parameter, variable, loop\_var, and constant. |
| Level | The scope level of the symbol. 0 represents the global scope. Local scope levels start from 1, and the scope level is incremented at the start of a scope and decremented at the end of the scope.  |
| Type | The type of the symbol. Each symbol is of types integer, real, boolean, string, or the signature of an array. (Note that this field can be used for the return type of a function ) |
| Attribute | Other attributes of the symbol, the value of a constant or list of the types of the formal parameters of a function. |

#### Implementation

A symbol table can be implemented in one of the following ways to represent entries in it:

- Linear list
- Binary search tree
- Hash table

#### Operations

A symbol table should provide the following operations:

- insert
  - used to add a new symbol declaration in the symbol table
- lookup
  - used to search a identifier in the symbol table for performing semantic analyses

#### Scope Management

In general, we won't just have one giant symbol table for each program. There is a concept of scope in the `P` language. Scope refers to the visibility of symbols. That is, different parts of the program located in different scopes may not see or use symbols in other scopes.

A scope corresponds to a symbol table. `ProgramNode`, `FunctionNode`, `ForNode` and `CompoundStatementNode` are nodes that form a scope. Therefore, your parser should create a new symbol table when encountering one of these nodes and destroy it when leaving the node.

Following are the special rules that you should be careful of:

- A `FunctionNode` should share the same symbol table with its body (CompoundStatementNode). More specifically, parameters of a `FunctionNode` should be declared in the same symbol table with those declared in the `CompoundStatementNode`.
- A `ForNode` contains a symbol table for the loop variable. That is, there is a scope (symbol table) in a `ForNode` with **only one symbol of a loop variable**.

#### Scope Rules

After entering a node that forms a scope, we may encounter some declarations. Then we have to extract information from the declaration and store it in the current symbol table.

When constructing an entry in a symbol table, there are some rules to conform:

- Scope rules are similar to C.
- Name must be unique within a given scope. The identifier designates the entity declared closest to it, that is, the identifier declared in the outer scope is hidden by the one declared in the inner scope.
  - Unlike the normal variable, the symbol of a loop variable **CANNOT** be redeclared whether it's in the same scope or the inner scope.
  - If there are multiple declarations with the same identifier in the same scope, only the first declaration will be left in the symbol table.
- Declarations within a compound statement, a function, or a for statement are local to the statements in the same block or the inner block, and no longer exist after exiting the block in which it's declared.

If there is a violation, your parser should report a semantic error. (we'll discuss it later)

#### Output Format

> Note that your parser should dump the symbol table to **`stdout`**.

Format of each component:

- Name
  - just characters
- Kind
  - 6 kinds of symbols with respective strings: `program`, `function`, `parameter`, `variable`, `loop_var`, and `constant`
- Level
  - 0: `"0(global)"`
  - other level: `n(local)`
- Type
  - just type string, same rule as hw3
- Attribute
  - constant
    - just string of constant
  - types of formal parameters
    - type strings separated by `", "` (e.g., `real, real [2]`)

Format of whole table:

```c
void dumpDemarcation(const char chr) {
  for (size_t i = 0; i < 110; ++i) {
    printf("%c", chr);
  }
  puts("");
}

void dumpSymbol(void) {
  dumpDemarcation('=');
  printf("%-33s%-11s%-11s%-17s%-11s\n", "Name", "Kind", "Level", "Type",
                                        "Attribute");
  dumpDemarcation('-')
  {
    printf("%-33s", "func");
    printf("%-11s", "function");
    printf("%d%-10s", 0, "(global)");
    printf("%-17s", "boolean");
    printf("%-11s", "integer, real [2][3]");
    puts("");
  }
  dumpDemarcation('-')
}
```

**Example:**

Assume we have the following function in a `P` program:

```
foo()
begin
    // constant
    var int1, int2 : 10;
    var str : "Gimme Gimme Gimme!!";
    var bool : true;
    var float : 2.56;
    var scientific : 111.111E-3;
    var octal : 0777;
end
end
```

Then the symbol table of the scope formed by the `CompoundStatementNode` in this function `foo()`:

```
==============================================================================================================
Name                             Kind       Level      Type             Attribute
--------------------------------------------------------------------------------------------------------------
int1                             constant   1(local)   integer          10
int2                             constant   1(local)   integer          10
str                              constant   1(local)   string           Gimme Gimme Gimme!!
bool                             constant   1(local)   boolean          true
float                            constant   1(local)   real             2.560000
scientific                       constant   1(local)   real             0.111111
octal                            constant   1(local)   integer          511
--------------------------------------------------------------------------------------------------------------
```

#### Pseudocomments

In the first part, we have defined:

- `S`
  - `&S+` turns on source program listing, and `&S-` turns it off.
- `T`
  - `&T+` turns on token (which will be returned to the parser) listing, and `&T-` turns it off.

In this part, one more option is added:

- `D`
  - Dump the contents of the symbol table associated with a block when exiting from that block.
  - `&D+` turns on symbol table dumping, and `&D-` turns it off.
  - By default, this option is on.
  - In test cases, this option won't be turned on/off in the middle of the program, it will only be set before the `ProgramName`.

### 0x01. Semantic Analysis

Now we have a basic grasp of what the symbol table is. Let's see how to use it in semantic analysis.

Before that, we need to talk about when to perform semantic analyses. Basically, semantic analyses can be separated into two parts by the performed order. One is performed in pre-order, while another one is in post-order. There is only one semantic analysis that should be performed in pre-order, that is symbol redeclaration. Except for symbol redeclaration, all other semantic analyses are performed in post-order.

In this part, you have to implement a semantic analyzer to perform semantic analyses on a given program by traversing the AST of it. When meeting a node, your analyzer should behave like this:

```c
void visitXXXNode(/* emitted for simplicity */) {
    /*
     * 1. Push a new symbol table if this node forms a scope.
     * 2. Insert the symbol into current symbol table if this node is related to
     *    declaration.
     * 3. Travere child nodes of this node.
     * 4. Perform semantic analyses of this node.
     * 5. Pop the symbol table pushed at the 1st step.
     */
}
```

Note that **once your parser has found a semantic error in a child node of some node, the parser has no need to check semantic errors related to the child node since the parser cannot use the wrong information for the rest examinations.**


Let's look at a simple example:

```
example;

begin // 1.
    var a: 55146; // 2.
    var a: integer; // 3.
    var b: "SSLAB"; // 4.

    a := 26980; // 5.
    b := 26980 + "team"; // 6.
end
end
```

In this example, I'll skip the `ProgramNode` and directly demonstrate how should your analyzer do when meeting a `CompoundStatementNode`.

1. A `CompoundStatementNode` forms a scope. The analyzer should push a new symbol table as the current symbol table (Step 1). Then, it skips Step 2 since this node is not related to the declaration.

2. Next, the analyzer traverses the child nodes of this node, starting from the variable declaration `var a: 55146;`. When meeting the node of the variable declaration, it also performs the tasks described in `visitXXXNode()`. In Step 2, it inserts the symbol `a` into the current symbol table as a constant variable. (Emit description of other steps for simplicity.)

3. After traversing the variable declaration `var a: 55146;`, the analyzer traverse the next variable declaration `var a: integer;`. When it tries to insert the symbol `a` into the current symbol table, it finds that it's a symbol redeclaration! Therefore, it reports the error to the `stderr` and moves on to the next step. <br>
**This is why the symbol redeclared is classified into pre-order, the semantic error of it is found and reported before visiting child nodes (Step 3).** (Emit description of the rest steps for simplicity.)

4. Emit the description of traversing the variable declaration `var b: "SSLAB";` since it's similar to the previous two.

5. The analyzer meets the part node `a := 26980;`. Again, it performs the tasks described in `visitXXXNode()`:
  1. Skip since part node doesn't form a scope.
  2. Skip since part node doesn't do declaration.
  3. Traverse child nodes (variable reference and expression)
        1. Traverse variable reference:
      1. Emit steps 1, 2, 3 for simplicity.
      2. In step 4, the semantic analyses of a `VariableReferenceNode` basically check whether this variable is in visible symbol tables. (More checks are described in [Section "0x02. Semantic Definition"](#0x02-semantic-definition)). It will do a lookup and find that symbol `a` is a constant variable declared in `2.`. Everything is fine, move on!
        2. Traverse expression:
      1. Emit steps 1, 2, 3 for simplicity.
      2. In step 4, since there are no semantic analyses related to a `ConstantValueNode`, just move on.
  4. Perform semantic analyses of an `partNode`, which basically check whether the variable reference is a constant or not and whether the variable reference and the expression are the same types. <br>

    The analyzer will find that the variable reference is a reference to a constant variable, and we cannot assign a value to a constant variable. As a result, it'll report the semantic error and skip the rest checks of the `partNode`.
6. Let's see a more complicated example. Also, the analyzer performs the same tasks on the part node `b := 26980 + "team";`:
  1. Emit steps 1, 2 for simplicity.
  2. Traverse child nodes (variable reference and expression)
        1. Traverse variable reference:
      1. Here is basically the same as the process described in 5-iii-a.
        2. Traverse expression:
      1. Emit steps 1, 2 for simplicity.
      2. Traverse child nodes (constant value and constant value)
        1. Nothing special. Emitted.
      3. In step 4, the semantic analyses of a `BinaryOperatorNode` basically check whether the operands are the same types. <br>
      The analyzer will find that the left operand is an integer, while the right operand is a string. We cannot add an integer with a string, so it will report the semantic error and skip the rest checks of the `BinaryOperatorNode`.
  3. Perform semantic analyses of an `partNode`.

    - Note that the spec has mentioned that we don't have to do further checks if the current node's child nodes have semantic errors. Be careful! The spec says that we don't have to do further checks **that are related to the child node which has a semantic error rather than all checks in the current node.**<br>
    Therefore, the analyzer will still find that the variable reference is a reference to a constant variable, which is prohibited and report the semantic error! After all, the variable reference is unrelated to the expression. We can still check the semantic definitions of the variable reference in the `partNode`.

More details about semantic definitions of each kind of node are listed in the next section.

### 0x02. Semantic Definition

This section describes the semantic definitions of each kind of node. Each kind of node may have several "groups", each group lists semantic definitions that should be conformed for different situations. Your parser should perform the checks in the same order listed in each group and if there is a violation in the middle of a group, your parser should report the error and skip the rest checks in the same group.

When your parser encounters a semantic error, the parser should report an error with relevant error messages and format, which are described in [error-message.md](./error-message.md).

> Note that your parser should report the error to **`stderr`**.

#### Symbol Table

##### Group 1

- When inserting a new symbol, the scope rules described in ["Scope Rule"](#scope-rules) should be conformed.

#### Variable Declaration

##### Group 1

- In an array declaration, each dimension's size has to be greater than 0.

#### Variable Reference

##### Group 1

- The identifier has to be in symbol tables.
- The kind of symbol has to be a parameter, variable, loop_var, or constant.
- There is no error in the node of the declaration of this symbol. (no error message needed here)
- Each index of an array reference must be of the integer type.
  - Once an incorrect (not an integer type) or unknown (an error has occurred in the child node) index was found, further checking regarding current array reference is unnecessary.
  - Bound checking is not performed at compile time as in C language.
- An over array subscript is forbidden, that is, the number of indices of an array reference cannot be greater than the one of dimensions in the declaration.

#### Binary/Unary operator

##### Group 1

Arithmetic operator (`+`, `-`, `*`, or `/`)

- There is no error in the nodes of operands. (no error message needed here)
- Operands must be an integer or real type.
  - The types of operands can be different after appropriate type coercion.
  - The operation produces an integer or a real value.

##### Group 2

Neg operator (`-`)

- There is no error in the node of the operand. (no error message needed here)
- The operand must be an integer or real type.
  - The operation produces an integer or a real value.

##### Group 3

Mod operator (`mod`)

- There is no error in the node of operands. (no error message needed here)
- Operands must be an integer type.
  - The operation produces an integer value.

##### Group 4

Boolean operator (`and`, `or`, or `not`)

- There is no error in the node(s) of the operand(s). (no error message needed here)
- Operands must be boolean type.
  - The operation produces a boolean value.

##### Group 5

Relational operator (`<`, `<=`, `=`, `>=`, `>`, or `<>`)

- There is no error in the nodes of operands. (no error message needed here)
- Operands must be an integer or real type.
  - The types of operands can be different after appropriate type coercion.
  - The operation produces a boolean value.

##### Group 6

String concatenation (`+`)

- There is no error in the nodes of operands. (no error message needed here)
- Operands must be a string type.
  - The operation produces a string value.

#### Type Coercion and Comparison

- Integer type can be implicitly converted into the real type in several situations: part, argument passing, arithmetic operation, relational operation, or return statement.
- The result of an arithmetic operation will be real type if one of the operands is real type. For example, `1.2 + 1` produces a real value.
- Two arrays are considered to be the same type if they have the same number of elements and the same type of the element.
  - More specifically, the following attributes have to be the same:
    - type of element
    - number of dimensions
    - size of each dimension
  - Type coercion is not permitted.

#### Function Invocation

Argument (actual parameter, the expression passed in), parameter (formal parameter, the variable declared in the function prototype)

##### Group 1

- The identifier has to be in symbol tables.
- The kind of symbol has to be function.
- The number of arguments must be the same as one of the parameters.
- Traverse arguments:
  - There is no error in the node of the expression (argument). (no error message needed here)
  - The type of the result of the expression (argument) must be the same type of the corresponding parameter after appropriate type coercion.

#### Print and Read Statement

##### Group 1

Print statement

- There is no error in the node of the expression (target). (no error message needed here)
- The type of the expression (target) must be scalar type.

##### Group 2

Read statement

- There is no error in the node of the variable reference. (no error message needed here)
- The type of the variable reference must be scalar type.
- The kind of symbol of the variable reference cannot be constant or loop_var.

#### part

##### Group 1

- There is no error in the node of the variable reference (lvalue). (no error message needed here)
- The type of the result of the variable reference cannot be an array type.
- The variable reference cannot be a reference to a constant variable.
- The variable reference cannot be a reference to a loop variable when the context is within a loop body.
- There is no error in the node of the expression. (no error message needed here)
- The type of the result of the expression cannot be an array type.
- The type of the variable reference (lvalue) must be the same as the one of the expression after appropriate type coercion.

#### If and While

##### Group 1

- There is no error in the node of the expression (condition). (no error message needed here)
- The type of the result of the expression (condition) must be boolean type.

#### For

##### Group 1

- The initial value of the loop variable and the constant value of the condition must be in the incremental order.

#### Return

##### Group 1

- The current context shouldn't be in the program or a procedure since their return type is void.
- There is no error in the node of the expression (return value). (no error message needed here)
- The type of the result of the expression (return value) must be the same type as the return type of current function after appropriate type coercion.

## What the Parser is capable of?

If the input file is syntactically and semantically correct, output the following message.

```
|---------------------------------------------|
|  There is no syntactic and semantic error!  |
|---------------------------------------------|
```

Once the parser encounters a semantic error, output the related error message.

Notice that semantic errors should **not** cause the parser to stop its execution. You should let the parser keep working on finding semantic errors as much as possible.

