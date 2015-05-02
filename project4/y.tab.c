/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "miniscript.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "AST.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


extern "C" int yylex();
extern "C" FILE *yyin;
extern "C" int yylineno;
int yyerror(const char *s);

bool simpleStmt = false;
bool isDecl = false;

map < string, Value* > tbl;
vector <int>  arithTable;

stack <vector <Statement*> * > blocks;
stack <IfStmt *> ifStmt;
vector <Statement*> block;
stack <FuncCall *> fcstack;

Function * func;

Program prog;
DocumentWrite * docuwrite;
ObjectDef * objDef;
ArrayDef * arrDef;
string parent;

void addStatement(Statement * stmt){
	blocks.top() -> push_back(stmt);
}

void pushBlock( vector <Statement *> * newBlock ) {
	blocks.push(newBlock);
}

void popBlock() {
	blocks.pop();
}

void getTop(vector <Statement * > & block)
{
	block = *blocks.top();
}

/*
 * varType
 */
int varType;
int lineQuit;
string curID;

int yP = 0;



/* Line 189 of yacc.c  */
#line 139 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     QQUO = 259,
     NUM = 260,
     SCRIPTYPE = 261,
     SLASHSCRIPT = 262,
     NEWLINE = 263,
     VAR = 264,
     EQUAL = 265,
     COLON = 266,
     SEMICOLON = 267,
     DOCUWRITE = 268,
     OPENPARENT = 269,
     CLOSEPARENT = 270,
     COMMA = 271,
     WS = 272,
     DOT = 273,
     CUROPENBRAC = 274,
     CURCLOSEBRAC = 275,
     PLUS = 276,
     MINUS = 277,
     TIME = 278,
     DIVIDE = 279,
     IF = 280,
     ELSE = 281,
     LESS = 282,
     GREAT = 283,
     LESSEQUAL = 284,
     GREATEQUAL = 285,
     EQEQUAL = 286,
     NOTEQUAL = 287,
     ANDAND = 288,
     OROR = 289,
     EXCLAMATION = 290,
     OPENBRAC = 291,
     CLOSEBRAC = 292,
     WHILE = 293,
     BREAK = 294,
     CONTINUE = 295,
     FUNCTION = 296,
     RETURN = 297
   };
#endif
/* Tokens.  */
#define ID 258
#define QQUO 259
#define NUM 260
#define SCRIPTYPE 261
#define SLASHSCRIPT 262
#define NEWLINE 263
#define VAR 264
#define EQUAL 265
#define COLON 266
#define SEMICOLON 267
#define DOCUWRITE 268
#define OPENPARENT 269
#define CLOSEPARENT 270
#define COMMA 271
#define WS 272
#define DOT 273
#define CUROPENBRAC 274
#define CURCLOSEBRAC 275
#define PLUS 276
#define MINUS 277
#define TIME 278
#define DIVIDE 279
#define IF 280
#define ELSE 281
#define LESS 282
#define GREAT 283
#define LESSEQUAL 284
#define GREATEQUAL 285
#define EQEQUAL 286
#define NOTEQUAL 287
#define ANDAND 288
#define OROR 289
#define EXCLAMATION 290
#define OPENBRAC 291
#define CLOSEBRAC 292
#define WHILE 293
#define BREAK 294
#define CONTINUE 295
#define FUNCTION 296
#define RETURN 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 66 "miniscript.y"

	char *string_val;
	int int_val;
	Expression *expr_val;
	Variable * var_val;
	Block * block_val;
	FuncCall * func_val;



/* Line 214 of yacc.c  */
#line 270 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 282 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  177

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     9,    12,    14,    17,    18,    22,
      23,    31,    37,    38,    45,    50,    51,    58,    60,    62,
      64,    66,    68,    71,    75,    78,    80,    81,    88,    89,
      95,    97,    98,   103,   104,   105,   115,   117,   118,   120,
     121,   126,   128,   130,   131,   132,   141,   145,   148,   150,
     152,   153,   159,   163,   168,   170,   173,   175,   177,   179,
     180,   185,   186,   190,   194,   196,   198,   202,   204,   206,
     208,   212,   216,   218,   222,   226,   230,   234,   236,   240,
     244,   246,   250,   252,   256,   258,   262,   264,   267,   270,
     274,   278,   283,   289,   291,   295,   300,   304,   307,   310,
     312,   314,   319
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    -1,     6,    45,    47,    46,    -1,     7,
       8,    -1,     7,    -1,    48,    47,    -1,    -1,     9,     3,
      74,    -1,    -1,    73,    10,    19,    49,    85,    20,    74,
      -1,    73,    10,    19,    20,    74,    -1,    -1,    73,    10,
      36,    50,    87,    74,    -1,    73,    10,    83,    74,    -1,
      -1,    13,    51,    14,    75,    15,    74,    -1,    66,    -1,
      52,    -1,    64,    -1,    65,    -1,    58,    -1,    54,    74,
      -1,    42,    83,    74,    -1,    42,    74,    -1,     8,    -1,
      -1,    38,    14,    70,    15,    53,    71,    -1,    -1,     3,
      14,    55,    56,    15,    -1,    83,    -1,    -1,    83,    57,
      16,    56,    -1,    -1,    -1,    41,     3,    14,    59,    61,
      15,    71,    60,     8,    -1,    62,    -1,    -1,     3,    -1,
      -1,     3,    63,    16,    61,    -1,    39,    -1,    40,    -1,
      -1,    -1,    25,    14,    70,    15,    67,    71,    68,    69,
      -1,    26,    71,     8,    -1,    26,    66,    -1,     8,    -1,
      83,    -1,    -1,    19,     8,    47,    72,    20,    -1,     3,
      18,     3,    -1,     3,    36,    83,    37,    -1,     3,    -1,
       9,     3,    -1,    12,    -1,     8,    -1,    83,    -1,    -1,
      83,    76,    16,    75,    -1,    -1,    77,    23,    78,    -1,
      77,    24,    78,    -1,    78,    -1,     4,    -1,    14,    83,
      15,    -1,     5,    -1,    73,    -1,    54,    -1,    79,    21,
      77,    -1,    79,    22,    77,    -1,    77,    -1,    80,    28,
      79,    -1,    80,    30,    79,    -1,    80,    27,    79,    -1,
      80,    29,    79,    -1,    79,    -1,    81,    31,    80,    -1,
      81,    32,    80,    -1,    80,    -1,    82,    33,    81,    -1,
      81,    -1,    83,    34,    82,    -1,    82,    -1,     3,    11,
      83,    -1,    84,    -1,    84,     8,    -1,     8,    84,    -1,
       8,    84,     8,    -1,    85,    16,    84,    -1,    85,    16,
       8,    84,    -1,    85,    16,     8,    84,     8,    -1,    83,
      -1,    88,     8,    37,    -1,     8,    88,     8,    37,    -1,
       8,    88,    37,    -1,    88,    37,    -1,     8,    37,    -1,
      37,    -1,    86,    -1,    88,    16,     8,    86,    -1,    88,
      16,    86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    84,    84,    84,    92,    93,    96,    97,   100,   103,
     103,   108,   111,   111,   115,   118,   118,   121,   122,   123,
     124,   125,   126,   129,   132,   135,   138,   138,   148,   148,
     158,   162,   162,   169,   174,   169,   181,   182,   185,   188,
     188,   193,   198,   203,   209,   203,   218,   219,   220,   223,
     228,   228,   234,   238,   241,   245,   253,   254,   257,   260,
     260,   263,   266,   269,   272,   275,   280,   283,   286,   289,
     294,   297,   300,   305,   308,   311,   314,   317,   321,   324,
     327,   331,   334,   338,   341,   345,   350,   352,   353,   354,
     355,   356,   357,   361,   366,   367,   368,   369,   370,   371,
     374,   375,   376
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "QQUO", "NUM", "SCRIPTYPE",
  "SLASHSCRIPT", "NEWLINE", "VAR", "EQUAL", "COLON", "SEMICOLON",
  "DOCUWRITE", "OPENPARENT", "CLOSEPARENT", "COMMA", "WS", "DOT",
  "CUROPENBRAC", "CURCLOSEBRAC", "PLUS", "MINUS", "TIME", "DIVIDE", "IF",
  "ELSE", "LESS", "GREAT", "LESSEQUAL", "GREATEQUAL", "EQEQUAL",
  "NOTEQUAL", "ANDAND", "OROR", "EXCLAMATION", "OPENBRAC", "CLOSEBRAC",
  "WHILE", "BREAK", "CONTINUE", "FUNCTION", "RETURN", "$accept", "parse",
  "$@1", "end", "lines", "line", "$@2", "$@3", "$@4", "while", "$@5",
  "funcCall", "$@6", "fcparam", "$@7", "funcDecl", "$@8", "$@9",
  "funcparam", "funcparam2", "$@10", "break", "continue", "ifstmt", "$@11",
  "$@12", "elsestmt", "cond", "body", "$@13", "id", "over", "param",
  "$@14", "exp4", "exp5", "exp3", "exp2", "exp1", "exp0", "exps",
  "object1", "object", "arrayE", "array", "arrayL", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    45,    44,    46,    46,    47,    47,    48,    49,
      48,    48,    50,    48,    48,    51,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    53,    52,    55,    54,
      56,    57,    56,    59,    60,    58,    61,    61,    62,    63,
      62,    64,    65,    67,    68,    66,    69,    69,    69,    70,
      72,    71,    73,    73,    73,    73,    74,    74,    75,    76,
      75,    75,    77,    77,    77,    77,    78,    78,    78,    78,
      79,    79,    79,    80,    80,    80,    80,    80,    81,    81,
      81,    82,    82,    83,    83,    84,    85,    85,    85,    85,
      85,    85,    85,    86,    87,    87,    87,    87,    87,    87,
      88,    88,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     2,     1,     2,     0,     3,     0,
       7,     5,     0,     6,     4,     0,     6,     1,     1,     1,
       1,     1,     2,     3,     2,     1,     0,     6,     0,     5,
       1,     0,     4,     0,     0,     9,     1,     0,     1,     0,
       4,     1,     1,     0,     0,     8,     3,     2,     1,     1,
       0,     5,     3,     4,     1,     2,     1,     1,     1,     0,
       4,     0,     3,     3,     1,     1,     3,     1,     1,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     2,     2,     3,
       3,     4,     5,     1,     3,     4,     3,     2,     2,     1,
       1,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     7,     1,    54,    25,     0,    15,     0,
       0,    41,    42,     0,     0,     0,     7,    18,     0,    21,
      19,    20,    17,     0,    28,     0,     0,    55,     0,     0,
       0,     0,    65,    67,    57,     0,    56,     0,    69,    68,
      24,    72,    64,    77,    80,    82,    84,     0,     5,     3,
       6,    22,     0,     0,    52,     0,     8,    61,     0,    49,
       0,    33,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,     4,     9,    12,
       0,     0,    30,    53,     0,    58,    43,    26,    37,    66,
      62,    63,    70,    71,    75,    73,    76,    74,    78,    79,
      81,    83,     0,     0,     0,    14,    29,     0,     0,     0,
       0,     0,    38,     0,    36,    11,     0,     0,    86,     0,
       0,    99,    93,   100,     0,     0,     0,    16,    61,     0,
      44,    27,     0,     0,     0,    88,    87,     0,     0,    98,
       0,    13,     0,     0,    97,    32,    60,     7,     0,    37,
      34,    85,    89,     0,    90,    10,     0,    96,    94,     0,
     102,    50,    48,     0,    45,    40,     0,    91,    95,   101,
       0,    47,     0,    35,    92,    51,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    49,    15,    16,   103,   104,    28,    17,
     111,    38,    53,    81,   107,    19,    88,   166,   113,   114,
     132,    20,    21,    22,   110,   148,   164,    58,   130,   170,
      39,    40,    84,   109,    41,    42,    43,    44,    45,    46,
     122,   118,   119,   123,   124,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -114
static const yytype_int16 yypact[] =
{
       1,  -114,     9,    20,  -114,    18,  -114,    36,  -114,    29,
      64,  -114,  -114,   107,    76,   106,    20,  -114,    23,  -114,
    -114,  -114,  -114,   130,  -114,   140,    98,    23,   134,    98,
      98,   135,  -114,  -114,  -114,   147,  -114,    98,  -114,  -114,
    -114,    85,  -114,   104,   102,    88,   118,    41,   144,  -114,
    -114,  -114,    68,    98,  -114,    87,  -114,    98,   138,   120,
     141,  -114,  -114,    -9,   113,   113,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,  -114,  -114,   137,  -114,
      41,   143,     4,  -114,   145,    32,  -114,  -114,   152,  -114,
    -114,  -114,    85,    85,   104,   104,   104,   104,   102,   102,
      88,   118,    23,    83,    60,  -114,  -114,   146,    23,   148,
     142,   142,   149,   151,  -114,  -114,   156,   160,   161,    73,
       7,  -114,   120,  -114,    23,    14,    98,  -114,    98,   162,
    -114,  -114,   155,   142,    98,   164,  -114,   103,    23,  -114,
      39,  -114,   122,    91,  -114,  -114,  -114,    20,    26,   152,
    -114,   120,  -114,   160,  -114,  -114,   131,  -114,  -114,    98,
    -114,  -114,  -114,    31,  -114,  -114,   165,   166,  -114,  -114,
     157,  -114,   167,  -114,  -114,  -114,  -114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,  -114,   -14,  -114,  -114,  -114,  -114,  -114,
    -114,    -3,  -114,    50,  -114,  -114,  -114,  -114,    30,  -114,
    -114,  -114,  -114,    15,  -114,  -114,  -114,   150,  -106,  -114,
      -2,   -10,    53,  -114,    72,    77,    66,    74,   108,   109,
     -11,  -113,  -114,   -76,  -114,    63
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -60
static const yytype_int16 yytable[] =
{
      18,    23,    50,    47,   135,   131,    89,     1,    51,     4,
       5,    32,    33,    18,    23,    55,    35,    56,    59,    59,
     -31,    37,   142,     5,   154,    75,    63,   150,     6,     7,
     143,    34,    24,     8,   162,    36,    25,    76,    75,    27,
     167,    80,    82,    29,   139,     9,    85,   156,   -59,    34,
     129,   144,   163,    36,    26,   143,     9,   172,    10,    11,
      12,    13,    14,     5,    32,    33,    75,   160,   120,    35,
     105,     5,    32,    33,    37,    75,   157,    35,    30,     5,
      32,    33,    37,   169,    34,    35,   116,    78,    36,   137,
      37,   117,   115,   138,     5,    32,    33,   121,   127,   159,
      35,     5,    32,    33,    79,    37,   116,    35,    64,    65,
      31,   153,    37,    48,   141,    82,     5,    85,    33,    72,
      73,    75,    35,   151,    83,    66,    67,    37,   155,    68,
      69,    70,    71,   161,    94,    95,    96,    97,    92,    93,
      52,    90,    91,    54,    18,    23,    98,    99,    57,    61,
      62,    74,    77,    86,    75,   112,    87,   102,   106,   158,
     108,   129,   126,   116,   128,   -39,   133,   134,   168,   136,
     147,   149,   152,   173,   174,   176,   145,   175,   171,   165,
      60,   146,   100,   140,   101
};

static const yytype_uint8 yycheck[] =
{
       3,     3,    16,    14,   117,   111,    15,     6,    18,     0,
       3,     4,     5,    16,    16,    26,     9,    27,    29,    30,
      16,    14,     8,     3,   137,    34,    37,   133,     8,     9,
      16,     8,    14,    13,     8,    12,    18,    47,    34,     3,
     153,    52,    53,    14,    37,    25,    57,     8,    16,     8,
      19,    37,    26,    12,    36,    16,    25,   163,    38,    39,
      40,    41,    42,     3,     4,     5,    34,   143,     8,     9,
      80,     3,     4,     5,    14,    34,    37,     9,    14,     3,
       4,     5,    14,   159,     8,     9,     3,    19,    12,    16,
      14,     8,   102,    20,     3,     4,     5,    37,   108,     8,
       9,     3,     4,     5,    36,    14,     3,     9,    23,    24,
       3,     8,    14,     7,   124,   126,     3,   128,     5,    31,
      32,    34,     9,   134,    37,    21,    22,    14,   138,    27,
      28,    29,    30,   147,    68,    69,    70,    71,    66,    67,
      10,    64,    65,     3,   147,   147,    72,    73,    14,    14,
       3,    33,     8,    15,    34,     3,    15,    20,    15,    37,
      15,    19,    16,     3,    16,    16,    15,    11,    37,     8,
       8,    16,     8,     8,     8,     8,   126,    20,   163,   149,
      30,   128,    74,   120,    75
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    44,    45,     0,     3,     8,     9,    13,    25,
      38,    39,    40,    41,    42,    47,    48,    52,    54,    58,
      64,    65,    66,    73,    14,    18,    36,     3,    51,    14,
      14,     3,     4,     5,     8,     9,    12,    14,    54,    73,
      74,    77,    78,    79,    80,    81,    82,    83,     7,    46,
      47,    74,    10,    55,     3,    83,    74,    14,    70,    83,
      70,    14,     3,    83,    23,    24,    21,    22,    27,    28,
      29,    30,    31,    32,    33,    34,    74,     8,    19,    36,
      83,    56,    83,    37,    75,    83,    15,    15,    59,    15,
      78,    78,    77,    77,    79,    79,    79,    79,    80,    80,
      81,    82,    20,    49,    50,    74,    15,    57,    15,    76,
      67,    53,     3,    61,    62,    74,     3,     8,    84,    85,
       8,    37,    83,    86,    87,    88,    16,    74,    16,    19,
      71,    71,    63,    15,    11,    84,     8,    16,    20,    37,
      88,    74,     8,    16,    37,    56,    75,     8,    68,    16,
      71,    83,     8,     8,    84,    74,     8,    37,    37,     8,
      86,    47,     8,    26,    69,    61,    60,    84,    37,    86,
      72,    66,    71,     8,     8,    20,     8
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 84 "miniscript.y"
    {pushBlock(&prog.nodes);}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 84 "miniscript.y"
    {
			popBlock();
		//	prog.printAST();
			//fprintf(stderr, "DONE\n");
			prog.execute();
		}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 100 "miniscript.y"
    {
			addStatement(new Var_Decl((yyvsp[(2) - (3)].string_val), yylineno));
		}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 103 "miniscript.y"
    {
			objDef = new ObjectDef(yylineno);
			addStatement(new Assign((yyvsp[(1) - (3)].var_val), objDef, yylineno));
		}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 106 "miniscript.y"
    {
		}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 108 "miniscript.y"
    {
			addStatement(new Assign((yyvsp[(1) - (5)].var_val), new ObjectDef(yylineno),yylineno));
		}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 111 "miniscript.y"
    {
			arrDef = new ArrayDef(yylineno);
			addStatement(new Assign((yyvsp[(1) - (3)].var_val), arrDef,yylineno));
		}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 114 "miniscript.y"
    {}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 115 "miniscript.y"
    {
			addStatement(new Assign((yyvsp[(1) - (4)].var_val), (yyvsp[(3) - (4)].expr_val), yylineno));
		}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 118 "miniscript.y"
    {docuwrite = new DocumentWrite(yylineno);}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 118 "miniscript.y"
    {
			addStatement(docuwrite);
		}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 126 "miniscript.y"
    {
			addStatement((yyvsp[(1) - (2)].func_val));
		}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 129 "miniscript.y"
    {
			addStatement(new ReturnStmt((yyvsp[(2) - (3)].expr_val), yylineno));
		}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 132 "miniscript.y"
    {
			addStatement(new ReturnStmt(NULL, yylineno));
		}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 138 "miniscript.y"
    {
	   		WhileStmt * temp = new WhileStmt((yyvsp[(3) - (4)].expr_val), yylineno);
			addStatement(temp);
			pushBlock(&temp->whileBlock);
	   	}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 143 "miniscript.y"
    { 
			popBlock();
		}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 148 "miniscript.y"
    {
		 	FuncCall * fc = new FuncCall((yyvsp[(1) - (2)].string_val), yylineno);
			fcstack.push(fc);
		 }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 151 "miniscript.y"
    {
		 	FuncCall * fc = fcstack.top();
			fcstack.pop();
			(yyval.func_val) = fc;
		}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 158 "miniscript.y"
    { 
			FuncCall *fc = fcstack.top();
			fc->expressions.push_back((yyvsp[(1) - (1)].expr_val));
		}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 162 "miniscript.y"
    {
			FuncCall *fc = fcstack.top();
			fc->expressions.push_back((yyvsp[(1) - (1)].expr_val));
		}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 169 "miniscript.y"
    {
	  			func = new Function();
				funcTable[(yyvsp[(2) - (3)].string_val)] = func;
				pushBlock(&func->funcBlock);
			}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 174 "miniscript.y"
    {
				popBlock();

			}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 185 "miniscript.y"
    {
		  	func->params.push_back((yyvsp[(1) - (1)].string_val));
		  }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 188 "miniscript.y"
    {
		  	func->params.push_back((yyvsp[(1) - (1)].string_val));
		  }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 193 "miniscript.y"
    {
	   		addStatement(new BreakStmt(yylineno));
	   	}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 198 "miniscript.y"
    {
		 	addStatement(new ContStmt(yylineno));
		 }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 203 "miniscript.y"
    {
		//	pushBlock();
			IfStmt * temp = new IfStmt((yyvsp[(3) - (4)].expr_val), yylineno);
			addStatement(temp);
			ifStmt.push(temp);
			pushBlock(&temp->ifBlock);
		}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 209 "miniscript.y"
    {popBlock();
			IfStmt * temp = ifStmt.top();
			ifStmt.pop();
			pushBlock(&temp->elseBlock);
		}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 213 "miniscript.y"
    {
			popBlock();
		}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 223 "miniscript.y"
    {
	  		(yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
	  	}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 228 "miniscript.y"
    {
	  // $$ = block;
	  }
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 234 "miniscript.y"
    {
			(yyval.var_val) = new ObjectVar((yyvsp[(3) - (3)].string_val),new SimpleVar((yyvsp[(1) - (3)].string_val), yylineno), yylineno);

		}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 238 "miniscript.y"
    {
			(yyval.var_val) = new ArrayVar((yyvsp[(3) - (4)].expr_val), new SimpleVar((yyvsp[(1) - (4)].string_val), yylineno), yylineno);
		}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 241 "miniscript.y"
    {
			(yyval.var_val) = new SimpleVar((yyvsp[(1) - (1)].string_val), yylineno);
			parent = (yyvsp[(1) - (1)].string_val);
		}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 245 "miniscript.y"
    {
			SimpleVar * sv = new SimpleVar((yyvsp[(2) - (2)].string_val), yylineno);
			sv -> setDecl(true);
			(yyval.var_val) = sv;

		}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 257 "miniscript.y"
    {
	   		docuwrite->addExpression((yyvsp[(1) - (1)].expr_val));
		}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 260 "miniscript.y"
    {
			docuwrite->addExpression((yyvsp[(1) - (1)].expr_val));
		}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 266 "miniscript.y"
    {
	  		(yyval.expr_val) = new Times((yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
	  	}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 269 "miniscript.y"
    {
			(yyval.expr_val) = new Divide((yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 272 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
		}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 275 "miniscript.y"
    {
			(yyval.expr_val) = new Word((yyvsp[(1) - (1)].string_val), yylineno);
		}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 280 "miniscript.y"
    {
	  		(yyval.expr_val) = (yyvsp[(2) - (3)].expr_val);
	  	}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 283 "miniscript.y"
    {
			(yyval.expr_val) = new Number((yyvsp[(1) - (1)].int_val), yylineno);
	  	}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 286 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].var_val);
		}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 289 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].func_val);
		}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 294 "miniscript.y"
    {
	  		(yyval.expr_val) = new Plus((yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
	  	}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 297 "miniscript.y"
    {
			(yyval.expr_val) = new Minus((yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 300 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
		}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 305 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(GT, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 308 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(GE, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 311 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(LT, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 314 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(LE, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 317 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
		}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 321 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(EQ, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 324 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(NE, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 327 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
		}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 331 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(AND, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 334 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
		}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 338 "miniscript.y"
    {
			(yyval.expr_val) = new Comparison(OR, (yyvsp[(1) - (3)].expr_val), (yyvsp[(3) - (3)].expr_val), yylineno);
		}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 341 "miniscript.y"
    {
			(yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
		}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 345 "miniscript.y"
    {
			objDef->addProperty((yyvsp[(1) - (3)].string_val), (yyvsp[(3) - (3)].expr_val));
		}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 350 "miniscript.y"
    {
		}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 361 "miniscript.y"
    {
			arrDef->addProperty((yyvsp[(1) - (1)].expr_val));
		}
    break;



/* Line 1464 of yacc.c  */
#line 2239 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 383 "miniscript.y"


int yyerror(const char *s)
{
	fprintf(stderr, "%s\n", s);
//	fprintf(stderr, "line:%d, %s\n", yylineno, s);
	return 1;
}

int debug = 0;

int main(int argc, char *argv[])
{
setbuf(stdout, NULL);
	//yydebug = 1;
	if (argc == 2) {
		FILE *file;
		file = fopen(argv[1], "r");
		if (!file) {
			fprintf(stderr, "could not open %s\n", argv[1]);
		} else{
			yyin = file;
			//yyparse() will call yylex()
			yyparse();
		}
	} else {
		fprintf(stderr, "format: ./yacc_example [filename]\n");
	}
	return 0;
}

