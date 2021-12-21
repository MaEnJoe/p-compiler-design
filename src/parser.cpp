/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/print.hpp"
#include "AST/expression.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/read.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"
#include "AST/AstDumper.hpp"
#include "sema/SemanticAnalyzer.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>

#define YYLTYPE yyltype
const char* filename;

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

/* Declared by scanner.l */
extern uint32_t line_num;
extern char buffer[512];
extern FILE *yyin;
extern char *yytext;
/* End */

static AstNode *root;

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);

std::string lineBuffer;


#line 122 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
#line 57 "parser.y" /* yacc.c:355  */

    #include "AST/PType.hpp"
    #include "AST/utils.hpp"
    #include "sema/SymbolTableUtility.hpp"

    #include <vector>
    #include <memory>

    class AstNode;
    class DeclNode;
    class FunctionNode;
    class ExpressionNode;

#line 166 "parser.cpp" /* yacc.c:355  */

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
#line 72 "parser.y" /* yacc.c:355  */

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

#line 248 "parser.cpp" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 279 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   319

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   145,   145,   162,   166,   170,   176,   181,   188,   192,
     196,   201,   208,   210,   214,   222,   233,   237,   241,   247,
     252,   259,   266,   273,   281,   285,   295,   300,   308,   310,
     315,   317,   319,   321,   325,   334,   338,   345,   354,   363,
     367,   371,   377,   385,   393,   403,   411,   425,   427,   429,
     431,   433,   435,   437,   441,   452,   458,   463,   470,   475,
     483,   488,   495,   507,   512,   518,   528,   566,   573,   577,
     585,   589,   595,   600,   607,   611,   617,   622,   629,   633,
     638,   645,   652,   659,   666,   673,   680,   687,   694,   701,
     708,   715,   720,   727,   734,   736,   738,   740,   746
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMA", "SEMICOLON", "COLON",
  "L_PARENTHESIS", "R_PARENTHESIS", "L_BRACKET", "R_BRACKET", "ASSIGN",
  "OR", "AND", "NOT", "LESS", "LESS_OR_EQUAL", "EQUAL", "GREATER",
  "GREATER_OR_EQUAL", "NOT_EQUAL", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MOD", "UNARY_MINUS", "ARRAY", "BOOLEAN", "INTEGER", "REAL", "STRING",
  "END", "BEGIN_", "DO", "ELSE", "FOR", "IF", "THEN", "WHILE", "DEF", "OF",
  "TO", "RETURN", "VAR", "FALSE", "TRUE", "PRINT", "READ", "ID",
  "INT_LITERAL", "REAL_LITERAL", "STRING_LITERAL", "$accept", "Program",
  "ProgramName", "DeclarationList", "Declarations", "FunctionList",
  "Functions", "Function", "FunctionDeclaration", "FunctionDefinition",
  "FunctionName", "FormalArgList", "FormalArgs", "FormalArg", "IdList",
  "ReturnType", "Declaration", "Type", "ScalarType", "ArrType", "ArrDecl",
  "LiteralConstant", "NegOrNot", "StringAndBoolean", "IntegerAndReal",
  "Statement", "CompoundStatement", "Simple", "VariableReference",
  "ArrRef", "Condition", "ElseOrNot", "While", "For", "Return",
  "FunctionCall", "FunctionInvocation", "ExpressionList", "Expressions",
  "StatementList", "Statements", "Expression", "Epsilon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

#define YYPACT_NINF -59

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-59)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -35,   -59,    18,    31,   -59,     2,   -26,     1,     2,   -59,
     -59,   -59,     7,   -59,    45,     1,   -59,   -59,   -59,    44,
     -59,   -59,    33,    58,     2,    51,   -59,   -26,   -59,   -59,
      47,   -59,   -59,   -59,   -59,   -59,   -59,   -59,    90,   -59,
     -59,    11,   100,   -18,   -59,   -59,   -21,   -59,    98,   103,
     -59,    70,   -59,    68,   -59,    64,   -59,   -59,   -59,   -59,
      66,     3,     3,     3,     3,    67,    72,   -59,   -59,   -59,
     106,   -59,   -59,   -59,   -59,   -59,   117,   113,   -21,   -59,
     141,   -26,    29,   -59,   107,   138,     3,     3,     3,   -59,
     -59,   -59,   -59,   -59,   -59,   108,   153,   176,   197,   142,
     145,     3,     3,   143,     3,   -59,   -59,   -59,    71,     4,
     -59,   -59,   -59,   -59,   104,   236,   119,   -59,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,    45,    45,   -59,   -59,   -59,   147,   149,   282,   -59,
     252,     3,   218,   -59,   -59,   124,   118,   -59,   295,   119,
      69,    69,    69,    69,    69,    69,    88,    88,   -59,   -59,
     -59,   126,   127,   -59,     3,   -59,   268,   -59,   -59,   112,
      45,   131,   -59,   130,   282,   -59,   146,   -59,   148,   -59,
      45,   -59,   150,   152,   -59
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     1,    98,     0,    98,     5,     6,
       4,    22,     0,    16,     0,     9,    10,    12,    13,     0,
       8,     7,     0,    98,    98,     0,    11,    98,    23,    41,
       0,    33,    30,    31,    32,    44,    43,    42,     0,    28,
      29,     0,     0,     0,    39,    40,    98,     2,     0,    18,
      19,     0,    17,     0,    26,     0,    34,    27,    37,    38,
       0,     0,     0,     0,     0,     0,    58,    76,    47,    48,
       0,    49,    50,    51,    52,    53,     0,     0,    75,    74,
      98,     0,     0,    35,     0,     0,     0,     0,     0,    45,
      46,    95,    94,    96,    97,     0,     0,     0,     0,    58,
       0,    98,     0,    59,     0,    68,    54,    77,     0,     0,
      25,    20,    21,    36,     0,     0,    91,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    67,    56,    57,     0,    71,    72,    70,
       0,     0,     0,    24,    14,     0,     0,    78,    93,    92,
      85,    86,    89,    87,    88,    90,    83,    84,    80,    81,
      82,    98,     0,    69,     0,    60,     0,    55,    15,     0,
       0,     0,    64,     0,    73,    61,     0,    63,     0,    65,
       0,    62,     0,     0,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   -59,   154,   -59,   -59,   -59,   167,   -59,   -59,
     -59,   -59,   -59,   102,   183,   -59,   194,   121,   -34,   -59,
     -59,   -59,   -59,   181,   -59,   128,   -14,   -59,   -45,   -59,
     -59,   -59,   -59,   -59,   -59,   -59,   -44,   -59,   -59,   -59,
     -59,   -58,    -4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    14,    15,    16,    17,    18,
      19,    48,    49,    50,    51,   109,     9,    38,    39,    40,
      41,    42,    43,    91,    92,    67,    68,    69,    93,   103,
      71,   171,    72,    73,    74,    75,    94,   136,   137,    77,
      78,    95,    10
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    70,    76,    20,    96,    97,    98,    56,   144,    86,
      22,    24,    23,     1,    60,    61,    87,    62,     4,    45,
     100,    63,    11,    52,    88,    64,    65,    66,   115,   116,
     117,    58,    59,    70,    76,     5,    24,    55,    31,    32,
      33,    34,    79,   138,   140,     6,   142,    35,    36,    13,
      27,    66,    89,    90,    37,    30,    31,    32,    33,    34,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,    22,   143,    82,   110,    24,   101,    29,
     102,    28,    47,   166,    30,    31,    32,    33,    34,   126,
     127,   128,   129,   130,    54,   145,    53,   139,    31,    32,
      33,    34,    35,    36,    57,    80,   174,    81,    83,    37,
     128,   129,   130,    84,    85,    99,   104,   161,   162,   118,
     119,   105,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   106,   131,   108,   113,   114,   135,
     102,   141,   164,   146,   163,   168,   177,   172,   173,   169,
     170,   176,   178,   179,   118,   119,   182,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,    46,   180,
     133,   183,    26,   111,   181,   184,   132,   118,   119,    12,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   134,    21,   112,    44,     0,   107,     0,   118,   119,
       0,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   167,     0,     0,     0,     0,     0,     0,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   147,     0,     0,     0,   118,   119,     0,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   165,     0,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   175,     0,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   119,     0,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130
};

static const yytype_int16 yycheck[] =
{
      14,    46,    46,     7,    62,    63,    64,    41,     4,     6,
       3,    32,     5,    48,    35,    36,    13,    38,     0,    23,
      65,    42,    48,    27,    21,    46,    47,    48,    86,    87,
      88,    49,    50,    78,    78,     4,    32,    26,    27,    28,
      29,    30,    46,   101,   102,    43,   104,    44,    45,    48,
       6,    48,    49,    50,    51,    26,    27,    28,    29,    30,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     3,   108,     5,    80,    32,     6,    21,
       8,    48,    31,   141,    26,    27,    28,    29,    30,    20,
      21,    22,    23,    24,     4,   109,    49,   101,    27,    28,
      29,    30,    44,    45,     4,     7,   164,     4,    40,    51,
      22,    23,    24,    49,    48,    48,    10,   131,   132,    11,
      12,     4,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    31,    37,     5,    40,    10,     4,
       8,     8,     3,    49,     7,    31,   170,   161,    31,    41,
      34,    49,    31,    33,    11,    12,   180,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    24,    33,
       4,    31,    15,    81,    36,    33,    33,    11,    12,     6,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     4,     8,    82,    23,    -1,    78,    -1,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     4,    -1,    -1,    -1,    -1,    -1,    -1,    11,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     7,    -1,    -1,    -1,    11,    12,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     9,    -1,    11,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     9,    -1,    11,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    11,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    12,    -1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    53,    54,     0,     4,    43,    55,    56,    68,
      94,    48,    66,    48,    57,    58,    59,    60,    61,    62,
      94,    68,     3,     5,    32,    78,    59,     6,    48,    21,
      26,    27,    28,    29,    30,    44,    45,    51,    69,    70,
      71,    72,    73,    74,    75,    94,    55,    31,    63,    64,
      65,    66,    94,    49,     4,    26,    70,     4,    49,    50,
      35,    36,    38,    42,    46,    47,    48,    77,    78,    79,
      80,    82,    84,    85,    86,    87,    88,    91,    92,    94,
       7,     4,     5,    40,    49,    48,     6,    13,    21,    49,
      50,    75,    76,    80,    88,    93,    93,    93,    93,    48,
      80,     6,     8,    81,    10,     4,    31,    77,     5,    67,
      94,    65,    69,    40,    10,    93,    93,    93,    11,    12,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    37,    33,     4,     4,     4,    89,    90,    93,    94,
      93,     8,    93,    70,     4,    78,    49,     7,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    78,    78,     7,     3,     9,    93,     4,    31,    41,
      34,    83,    94,    31,    93,     9,    49,    78,    31,    33,
      33,    36,    78,    31,    33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    55,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    61,    62,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    70,    71,    72,    72,    73,    73,    73,
      74,    74,    75,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    78,    79,    79,    79,    80,    80,
      81,    81,    82,    83,    83,    84,    85,    86,    87,    88,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     6,     7,     1,     1,     1,     1,
       3,     3,     1,     3,     2,     1,     5,     5,     1,     1,
       1,     1,     1,     1,     2,     3,     4,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     3,     3,     1,     2,
       3,     4,     7,     2,     1,     6,    10,     3,     2,     4,
       1,     1,     1,     3,     1,     1,     1,     2,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     1,     1,     1,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 149 "parser.y" /* yacc.c:1646  */
    {
        root = new ProgramNode((yylsp[-5]).first_line, (yylsp[-5]).first_column,
                               new PType(PType::PrimitiveTypeEnum::kVoidType),
                               (yyvsp[-5].identifier), (yyvsp[-3].decls), (yyvsp[-2].funcs),
                               static_cast<CompoundStatementNode *>((yyvsp[-1].node)));

        free((yyvsp[-5].identifier));
        delete (yyvsp[-3].decls);
        delete (yyvsp[-2].funcs);
    }
#line 1624 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 166 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decls) = new std::vector<std::unique_ptr<DeclNode>>();
    }
#line 1632 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 170 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decls) = (yyvsp[0].decls);
    }
#line 1640 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 176 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decls) = new std::vector<std::unique_ptr<DeclNode>>;
        (yyval.decls)->emplace_back(static_cast<DeclNode *>((yyvsp[0].node)));
    }
#line 1649 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 181 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].decls)->emplace_back(static_cast<DeclNode *>((yyvsp[0].node)));
        (yyval.decls) = (yyvsp[-1].decls);
    }
#line 1658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 188 "parser.y" /* yacc.c:1646  */
    {
        (yyval.funcs) = new std::vector<std::unique_ptr<FunctionNode>>();
    }
#line 1666 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 196 "parser.y" /* yacc.c:1646  */
    {
        (yyval.funcs) = new std::vector<std::unique_ptr<FunctionNode>>;
        (yyval.funcs)->emplace_back(static_cast<FunctionNode *>((yyvsp[0].node)));
    }
#line 1675 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 201 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].funcs)->emplace_back(static_cast<FunctionNode *>((yyvsp[0].node)));
        (yyval.funcs) = (yyvsp[-1].funcs);
    }
#line 1684 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 214 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new FunctionNode((yylsp[-5]).first_line, (yylsp[-5]).first_column, (yyvsp[-5].identifier), (yyvsp[-3].decls), (yyvsp[-1].type), nullptr);
        free((yyvsp[-5].identifier));
        delete (yyvsp[-3].decls);
    }
#line 1694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 224 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new FunctionNode((yylsp[-6]).first_line, (yylsp[-6]).first_column, (yyvsp[-6].identifier), (yyvsp[-4].decls), (yyvsp[-2].type),
                              static_cast<CompoundStatementNode *>((yyvsp[-1].node)));
        free((yyvsp[-6].identifier));
        delete (yyvsp[-4].decls);
    }
#line 1705 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 237 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decls) = new std::vector<std::unique_ptr<DeclNode>>();
    }
#line 1713 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 241 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decls) = (yyvsp[0].decls);
    }
#line 1721 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 247 "parser.y" /* yacc.c:1646  */
    {
        (yyval.decls) = new std::vector<std::unique_ptr<DeclNode>>;
        (yyval.decls)->emplace_back(static_cast<DeclNode *>((yyvsp[0].node)));
    }
#line 1730 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 252 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].decls)->emplace_back(static_cast<DeclNode *>((yyvsp[0].node)));
        (yyval.decls) = (yyvsp[-2].decls);
    }
#line 1739 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 259 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new DeclNode((yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].ids), (yyvsp[0].type));
        delete (yyvsp[-2].ids);
    }
#line 1748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 266 "parser.y" /* yacc.c:1646  */
    {
        auto ids = new std::vector<IdInfo>();
        ids->emplace_back((yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].identifier));
        free((yyvsp[0].identifier));
        (yyval.ids) = ids;
    }
#line 1759 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 273 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].ids)->emplace_back((yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].identifier));
        free((yyvsp[0].identifier));
        (yyval.ids) = (yyvsp[-2].ids);
    }
#line 1769 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 281 "parser.y" /* yacc.c:1646  */
    {
        (yyval.type) = (yyvsp[0].type);
    }
#line 1777 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 285 "parser.y" /* yacc.c:1646  */
    {
        (yyval.type) = new PType(PType::PrimitiveTypeEnum::kVoidType);
    }
#line 1785 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 295 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new DeclNode((yylsp[-4]).first_line, (yylsp[-4]).first_column, (yyvsp[-3].ids), (yyvsp[-1].type));
        delete (yyvsp[-3].ids);
    }
#line 1794 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 300 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new DeclNode((yylsp[-4]).first_line, (yylsp[-4]).first_column, (yyvsp[-3].ids),
                          static_cast<ConstantValueNode *>((yyvsp[-1].node)));
        delete (yyvsp[-3].ids);
    }
#line 1804 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 315 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new PType(PType::PrimitiveTypeEnum::kIntegerType); }
#line 1810 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 317 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new PType(PType::PrimitiveTypeEnum::kRealType); }
#line 1816 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 319 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new PType(PType::PrimitiveTypeEnum::kStringType); }
#line 1822 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 321 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new PType(PType::PrimitiveTypeEnum::kBoolType); }
#line 1828 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 325 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[0].type)->setDimensions(*(yyvsp[-1].dimensions));
        delete (yyvsp[-1].dimensions);

        (yyval.type) = (yyvsp[0].type);
    }
#line 1839 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 334 "parser.y" /* yacc.c:1646  */
    {
        (yyval.dimensions) = new std::vector<uint64_t>{static_cast<uint64_t>((yyvsp[-1].integer))};
    }
#line 1847 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 338 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-3].dimensions)->emplace_back((yyvsp[-1].integer));
        (yyval.dimensions) = (yyvsp[-3].dimensions);
    }
#line 1856 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 345 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        value.integer = static_cast<int32_t>((yyvsp[-1].integer) * (yyvsp[0].integer));
        auto *constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kIntegerType), value);
        auto *pos = ((yyvsp[-1].integer) == 1) ? &(yylsp[0]) : &(yylsp[-1]);
        (yyval.node) = new ConstantValueNode(pos->first_line, pos->first_column, constant);
    }
#line 1869 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 354 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        value.real = static_cast<double>((yyvsp[-1].integer) * (yyvsp[0].real));
        auto *constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kRealType), value);
        auto *pos = ((yyvsp[-1].integer) == 1) ? &(yylsp[0]) : &(yylsp[-1]);
        (yyval.node) = new ConstantValueNode(pos->first_line, pos->first_column, constant);
    }
#line 1882 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 367 "parser.y" /* yacc.c:1646  */
    {
        (yyval.integer) = 1;
    }
#line 1890 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 371 "parser.y" /* yacc.c:1646  */
    {
        (yyval.integer) = -1;
    }
#line 1898 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 377 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        value.string = (yyvsp[0].string);
        auto *constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kStringType), value);
        (yyval.node) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, constant);
    }
#line 1910 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 385 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        value.boolean = (yyvsp[0].boolean);
        auto *constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kBoolType), value);
        (yyval.node) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, constant);
    }
#line 1922 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 393 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        value.boolean = (yyvsp[0].boolean);
        auto *constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kBoolType), value);
        (yyval.node) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, constant);
    }
#line 1934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 403 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        value.integer = static_cast<int32_t>((yyvsp[0].integer));
        auto *constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kIntegerType), value);
        (yyval.node) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, constant);
    }
#line 1946 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 411 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        value.real = static_cast<double>((yyvsp[0].real));
        auto *constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kRealType), value);
        (yyval.node) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, constant);
    }
#line 1958 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 444 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new CompoundStatementNode((yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].decls), (yyvsp[-1].nodes));
        delete (yyvsp[-2].decls);
        delete (yyvsp[-1].nodes);
    }
#line 1968 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 452 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new AssignmentNode((yylsp[-2]).first_line, (yylsp[-2]).first_column,
                                static_cast<VariableReferenceNode *>((yyvsp[-3].node)),
                                static_cast<ExpressionNode *>((yyvsp[-1].node)));
    }
#line 1978 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 458 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new PrintNode((yylsp[-2]).first_line, (yylsp[-2]).first_column,
                           static_cast<ExpressionNode *>((yyvsp[-1].node)));
    }
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 463 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new ReadNode((yylsp[-2]).first_line, (yylsp[-2]).first_column,
                          static_cast<VariableReferenceNode *>((yyvsp[-1].node)));
    }
#line 1996 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 470 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new VariableReferenceNode((yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].identifier));
        delete (yyvsp[0].identifier);
    }
#line 2005 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 475 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new VariableReferenceNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[-1].identifier), (yyvsp[0].exprs));
        delete (yyvsp[-1].identifier);
        delete (yyvsp[0].exprs);
    }
#line 2015 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 483 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exprs) = new std::vector<std::unique_ptr<ExpressionNode>>;
        (yyval.exprs)->emplace_back(static_cast<ExpressionNode *>((yyvsp[-1].node)));
    }
#line 2024 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 488 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-3].exprs)->emplace_back(static_cast<ExpressionNode *>((yyvsp[-1].node)));
        (yyval.exprs) = (yyvsp[-3].exprs);
    }
#line 2033 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 498 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new IfNode((yylsp[-6]).first_line, (yylsp[-6]).first_column,
                        static_cast<ExpressionNode *>((yyvsp[-5].node)),
                        static_cast<CompoundStatementNode *>((yyvsp[-3].node)),
                        static_cast<CompoundStatementNode *>((yyvsp[-2].node)));
    }
#line 2044 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 508 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2052 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 512 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = NULL;
    }
#line 2060 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 520 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new WhileNode((yylsp[-5]).first_line, (yylsp[-5]).first_column,
                           static_cast<ExpressionNode *>((yyvsp[-4].node)),
                           static_cast<CompoundStatementNode *>((yyvsp[-2].node)));
    }
#line 2070 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 530 "parser.y" /* yacc.c:1646  */
    {
        Constant::ConstantValue value;
        Constant *constant;
        ConstantValueNode *constant_value_node;

        // DeclNode
        auto *ids = new std::vector<IdInfo>{IdInfo((yylsp[-8]).first_line, (yylsp[-8]).first_column, (yyvsp[-8].identifier))};
        auto *type = new PType(PType::PrimitiveTypeEnum::kIntegerType);
        auto *var_decl = new DeclNode((yylsp[-8]).first_line, (yylsp[-8]).first_column, ids, type);

        // AssignmentNode
        auto *var_ref = new VariableReferenceNode((yylsp[-8]).first_line, (yylsp[-8]).first_column, (yyvsp[-8].identifier));
        value.integer = static_cast<int32_t>((yyvsp[-6].integer));
        constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kIntegerType), value);
        constant_value_node = new ConstantValueNode((yylsp[-6]).first_line, (yylsp[-6]).first_column,
                                                          constant);
        auto *assignment = new AssignmentNode((yylsp[-7]).first_line, (yylsp[-7]).first_column,
                                              var_ref, constant_value_node);

        // ExpressionNode
        value.integer = static_cast<int32_t>((yyvsp[-4].integer));
        constant = new Constant(
            std::make_shared<const PType>(PType::PrimitiveTypeEnum::kIntegerType), value);
        constant_value_node = new ConstantValueNode((yylsp[-4]).first_line, (yylsp[-4]).first_column,
                                                    constant);

        (yyval.node) = new ForNode((yylsp[-9]).first_line, (yylsp[-9]).first_column,
                         var_decl, assignment, constant_value_node,
                         static_cast<CompoundStatementNode *>((yyvsp[-2].node)));
        free((yyvsp[-8].identifier));
        delete ids;
    }
#line 2108 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 566 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new ReturnNode((yylsp[-2]).first_line, (yylsp[-2]).first_column,
                            static_cast<ExpressionNode *>((yyvsp[-1].node)));
    }
#line 2117 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 577 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new FunctionInvocationNode((yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-3].identifier), (yyvsp[-1].exprs));
        delete (yyvsp[-3].identifier);
        delete (yyvsp[-1].exprs);
    }
#line 2127 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 585 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exprs) = new std::vector<std::unique_ptr<ExpressionNode>>();
    }
#line 2135 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 589 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exprs) = (yyvsp[0].exprs);
    }
#line 2143 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 595 "parser.y" /* yacc.c:1646  */
    {
        (yyval.exprs) = new std::vector<std::unique_ptr<ExpressionNode>>;
        (yyval.exprs)->emplace_back(static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2152 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 600 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].exprs)->emplace_back(static_cast<ExpressionNode *>((yyvsp[0].node)));
        (yyval.exprs) = (yyvsp[-2].exprs);
    }
#line 2161 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 607 "parser.y" /* yacc.c:1646  */
    {
        (yyval.nodes) = new std::vector<std::unique_ptr<AstNode>>();
    }
#line 2169 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 611 "parser.y" /* yacc.c:1646  */
    {
        (yyval.nodes) = (yyvsp[0].nodes);
    }
#line 2177 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 617 "parser.y" /* yacc.c:1646  */
    {
        (yyval.nodes) = new std::vector<std::unique_ptr<AstNode>>;
        (yyval.nodes)->emplace_back((yyvsp[0].node));
    }
#line 2186 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 622 "parser.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].nodes)->emplace_back((yyvsp[0].node));
        (yyval.nodes) = (yyvsp[-1].nodes);
    }
#line 2195 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 629 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2203 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 633 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new UnaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                   Operator::kNegOp, static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2212 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 638 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kMultiplyOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2223 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 645 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kDivideOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2234 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 652 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kModOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2245 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 659 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kPlusOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2256 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 666 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kMinusOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2267 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 673 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kLessOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2278 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 680 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kLessOrEqualOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2289 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 687 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kGreaterOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2300 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 694 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kGreaterOrEqualOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2311 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 701 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kEqualOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2322 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 708 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kNotEqualOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2333 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 715 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new UnaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                   Operator::kNotOp, static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2342 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 720 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kAndOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2353 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 727 "parser.y" /* yacc.c:1646  */
    {
        (yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column,
                                    Operator::kOrOp,
                                    static_cast<ExpressionNode *>((yyvsp[-2].node)),
                                    static_cast<ExpressionNode *>((yyvsp[0].node)));
    }
#line 2364 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2368 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 748 "parser.y" /* yacc.c:1906  */


void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    assert(argc >= 2 && "Usage: ./parser <filename> [--dump-ast]\n");

    yyin = fopen(argv[1], "r");
    assert(yyin != NULL && "fopen() fails.\n");

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        AstDumper dumper;
        root->accept(dumper);
    }
    filename = argv[1];
    SemanticAnalyzer analyzer;
    root->accept(analyzer);

    analyzer.printErrorMessage();



    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
