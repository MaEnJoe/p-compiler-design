/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 57 "parser.y" /* yacc.c:1909  */

    #include "AST/PType.hpp"
    #include "AST/utils.hpp"
    #include "sema/SymbolTableUtility.hpp"

    #include <vector>
    #include <memory>

    class AstNode;
    class DeclNode;
    class FunctionNode;
    class ExpressionNode;

#line 58 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMA = 258,
    SEMICOLON = 259,
    COLON = 260,
    L_PARENTHESIS = 261,
    R_PARENTHESIS = 262,
    L_BRACKET = 263,
    R_BRACKET = 264,
    ASSIGN = 265,
    OR = 266,
    AND = 267,
    NOT = 268,
    LESS = 269,
    LESS_OR_EQUAL = 270,
    EQUAL = 271,
    GREATER = 272,
    GREATER_OR_EQUAL = 273,
    NOT_EQUAL = 274,
    PLUS = 275,
    MINUS = 276,
    MULTIPLY = 277,
    DIVIDE = 278,
    MOD = 279,
    UNARY_MINUS = 280,
    ARRAY = 281,
    BOOLEAN = 282,
    INTEGER = 283,
    REAL = 284,
    STRING = 285,
    END = 286,
    BEGIN_ = 287,
    DO = 288,
    ELSE = 289,
    FOR = 290,
    IF = 291,
    THEN = 292,
    WHILE = 293,
    DEF = 294,
    OF = 295,
    TO = 296,
    RETURN = 297,
    VAR = 298,
    FALSE = 299,
    TRUE = 300,
    PRINT = 301,
    READ = 302,
    ID = 303,
    INT_LITERAL = 304,
    REAL_LITERAL = 305,
    STRING_LITERAL = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 72 "parser.y" /* yacc.c:1909  */

    /* basic semantic value */
    char *identifier;
    int32_t integer;
    double real;
    char *string;
    bool boolean;

    AstNode *node;
    std::vector<IdInfo> *ids;
    std::vector<std::unique_ptr<AstNode>> *nodes;
    std::vector<std::unique_ptr<DeclNode>> *decls;
    std::vector<std::unique_ptr<FunctionNode>> *funcs;
    std::vector<std::unique_ptr<ExpressionNode>> *exprs;
    PType *type;
    std::vector<uint64_t> *dimensions;

#line 140 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
