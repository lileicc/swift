/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ELSE = 258,
     IF = 259,
     THEN = 260,
     TYPE = 261,
     RANDOM = 262,
     FIXED = 263,
     ORIGIN = 264,
     DISTINCT = 265,
     QUERY = 266,
     OBS = 267,
     PARAM = 268,
     LIST = 269,
     MAP = 270,
     DISTRIBUTION = 271,
     CASE = 272,
     IN = 273,
     EXISTS_ = 274,
     FORALL_ = 275,
     FOR = 276,
     NULLITY = 277,
     INT_LITERAL = 278,
     DOUBLE_LITERAL = 279,
     BOOLEAN_LITERAL = 280,
     CHAR_LITERAL = 281,
     STRING_LITERAL = 282,
     ID = 283,
     PARFACTOR = 284,
     FACTOR = 285,
     ERROR = 286,
     ELSEIF = 287,
     AT_ = 288,
     PLUS_ = 289,
     MULT_ = 290,
     DIV_ = 291,
     MOD_ = 292,
     POWER_ = 293,
     MINUS_ = 294,
     UMINUS = 295,
     LST = 296,
     LT_ = 297,
     GT_ = 298,
     LEQ_ = 299,
     GEQ_ = 300,
     EQEQ_ = 301,
     NEQ_ = 302,
     EQ_ = 303,
     DISTRIB = 304,
     NOT_ = 305,
     AND_ = 306,
     OR_ = 307,
     DOUBLERIGHTARROW = 308,
     COMMA = 309,
     SEMI = 310,
     COLON = 311,
     DOT = 312,
     NUMSIGN = 313,
     RIGHTARROW = 314,
     LPAREN = 315,
     RPAREN = 316,
     LBRACE = 317,
     RBRACE = 318,
     LBRACKET = 319,
     RBRACKET = 320
   };
#endif
/* Tokens.  */
#define ELSE 258
#define IF 259
#define THEN 260
#define TYPE 261
#define RANDOM 262
#define FIXED 263
#define ORIGIN 264
#define DISTINCT 265
#define QUERY 266
#define OBS 267
#define PARAM 268
#define LIST 269
#define MAP 270
#define DISTRIBUTION 271
#define CASE 272
#define IN 273
#define EXISTS_ 274
#define FORALL_ 275
#define FOR 276
#define NULLITY 277
#define INT_LITERAL 278
#define DOUBLE_LITERAL 279
#define BOOLEAN_LITERAL 280
#define CHAR_LITERAL 281
#define STRING_LITERAL 282
#define ID 283
#define PARFACTOR 284
#define FACTOR 285
#define ERROR 286
#define ELSEIF 287
#define AT_ 288
#define PLUS_ 289
#define MULT_ 290
#define DIV_ 291
#define MOD_ 292
#define POWER_ 293
#define MINUS_ 294
#define UMINUS 295
#define LST 296
#define LT_ 297
#define GT_ 298
#define LEQ_ 299
#define GEQ_ 300
#define EQEQ_ 301
#define NEQ_ 302
#define EQ_ 303
#define DISTRIB 304
#define NOT_ 305
#define AND_ 306
#define OR_ 307
#define DOUBLERIGHTARROW 308
#define COMMA 309
#define SEMI 310
#define COLON 311
#define DOT 312
#define NUMSIGN 313
#define RIGHTARROW 314
#define LPAREN 315
#define RPAREN 316
#define LBRACE 317
#define RBRACE 318
#define LBRACKET 319
#define RBRACKET 320




/* Copy the first part of user declarations.  */
#line 1 "blog.yacc"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "BLOGSymbol.h"
#include "../absyn/Absyn.h"
#include "../absyn/ArrayExpr.h"
#include "../absyn/BoolLiteral.h"
#include "../absyn/BlogProgram.h"
#include "../absyn/CardinalityExpr.h"
#include "../absyn/CondSet.h"
#include "../absyn/Decl.h"
#include "../absyn/DistinctDecl.h"
#include "../absyn/DistrExpr.h"
#include "../absyn/DoubleLiteral.h"
#include "../absyn/Evidence.h"
#include "../absyn/Expr.h"
#include "../absyn/FuncApp.h"
#include "../absyn/FuncDecl.h"
#include "../absyn/IfExpr.h"
#include "../absyn/IntLiteral.h"
#include "../absyn/Literal.h"
#include "../absyn/ListSet.h"
#include "../absyn/MapExpr.h"
#include "../absyn/NullLiteral.h"
#include "../absyn/NumStDecl.h"
#include "../absyn/OpExpr.h"
#include "../absyn/OriginDecl.h"
#include "../absyn/QuantExpr.h"
#include "../absyn/Query.h"
#include "../absyn/SetExpr.h"
#include "../absyn/Stmt.h"
#include "../absyn/StringLiteral.h"
#include "../absyn/Symbol.h"
#include "../absyn/TimeStampLiteral.h"
#include "../absyn/Ty.h"
#include "../absyn/TypDecl.h"
#include "../absyn/VarDecl.h"
#include "../absyn/VarRef.h"
#include "../absyn/CaseExpr.h"
#include "../absyn/TupleSetExpr.h"
using namespace std;
using namespace swift::absyn;

// stuff from flex that bison needs to know about: 
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int yylineno;
extern "C" int curr_line;
extern "C" int curr_col;

void yyerror(const char *s);
BlogProgram *blog;

BlogProgram* parse(const char* inp) {
  blog = new BlogProgram(0, 0);
  // open a file handle to a particular file:
  FILE *myfile = fopen(inp, "r");
  // make sure it is valid:
  if (!myfile) {
    cout << "I can't open input.in" << endl;
    exit(0);
    //return -1;
  }
  // set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  // parse through the input until there is no more:
  do {
    yyparse();
  } while (!feof(yyin));
  return blog;  
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 79 "blog.yacc"
{
  int i;
  class BLOGSymbol<int>* ival;
  class BLOGSymbol<double>* dblval;
  class BLOGSymbol<char>* chrval;
  class BLOGSymbol<bool>* boolval;
  class BLOGSymbol<string>* sval;
  vector<tuple<string,int>>* symbintvect;
  tuple<string,int>* symbintpair;
  class Absyn* ast;
  class ArrayExpr* arrayexp;
  class BoolLiteral* boollit;
  class BlogProgram* bprog;
  class CardinalityExpr* cardexp;
  class CondSet* cset;
  class Decl* dec;
  class DistinctDecl* distdec;
  class DistrExpr* distrexp;
  class DoubleLiteral* doublelit;
  class Evidence* evid;
  class Expr* exp;
  class FuncApp* fapp;
  class FuncDecl* funcdec;
  class IfExpr* ifexp;
  class IntLiteral* intlit;
  class Literal* lit;
  class ListSet* lset;
  class MapExpr* mapexp;
  class NullLiteral* nullit;
  class NumStDecl* numstdec;
  class OpExpr* opexp;
  class OriginDecl* origdec;
  class QuantExpr* quantexp;
  class Query* query;
  class SetExpr* setexp;
  class Stmt* stmt;
  class StringLiteral* stringlit;
  class Symbol* symb;
  class Ty* typ;
  class TypDecl* typdec;
  class VarDecl* vardec;
  class VarRef* varref;
  void *compexp[3];
  void *pair[2];
  vector<VarDecl>* varlist;
  vector<tuple<Expr*, Expr*>>* exptuplst;
  vector<Expr*>* explst;
  vector<tuple<Symbol, Symbol>>* varlst;
}
/* Line 193 of yacc.c.  */
#line 354 "parser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 367 "parser.cpp"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   929

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNRULES -- Number of states.  */
#define YYNSTATES  284

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    12,    15,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    47,    50,    52,    54,    56,    58,    63,    66,
      69,    73,    80,    81,    84,    88,    90,    93,    96,    99,
     103,   105,   109,   112,   116,   123,   126,   132,   136,   139,
     144,   148,   154,   158,   161,   165,   166,   172,   178,   184,
     189,   193,   196,   203,   210,   216,   222,   225,   229,   231,
     235,   238,   242,   244,   249,   257,   259,   263,   266,   270,
     276,   278,   280,   282,   284,   286,   288,   290,   292,   294,
     296,   298,   300,   302,   304,   306,   308,   312,   316,   320,
     324,   328,   332,   336,   340,   344,   348,   352,   356,   360,
     364,   368,   373,   375,   378,   381,   384,   388,   393,   398,
     403,   405,   409,   416,   421,   426,   428,   429,   433,   437,
     439,   443,   447,   451,   455,   459,   465,   469,   472,   475,
     478,   480,   482,   486,   492,   496,   500,   503,   506,   508,
     512,   516,   520,   523
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    68,    -1,    -1,    69,    -1,    69,    70,
      55,    -1,    70,    55,    -1,    69,    70,    -1,    70,    -1,
      71,    -1,   114,    -1,   117,    -1,     1,    -1,    72,    -1,
      82,    -1,    83,    -1,    87,    -1,    84,    -1,    88,    -1,
      94,    -1,    91,    -1,     6,    28,    -1,     6,     1,    -1,
      92,    -1,    74,    -1,    77,    -1,    76,    -1,    14,    42,
      28,    43,    -1,    92,    64,    -1,    75,    65,    -1,    76,
      64,    65,    -1,    15,    42,    73,    54,    73,    43,    -1,
      -1,    60,    61,    -1,    60,    81,    61,    -1,    81,    -1,
      73,    28,    -1,    54,    54,    -1,    80,    54,    -1,    81,
      54,    79,    -1,    79,    -1,    81,    80,    79,    -1,    81,
      79,    -1,    81,    54,     1,    -1,     8,    73,    28,    78,
      48,    95,    -1,     8,     1,    -1,     7,    73,    28,    78,
      93,    -1,     7,     1,    93,    -1,     7,     1,    -1,    58,
      92,    85,    93,    -1,    58,    85,    93,    -1,    58,    92,
      85,    49,     1,    -1,    58,    92,     1,    -1,    58,     1,
      -1,    60,    86,    61,    -1,    -1,    86,    54,    28,    48,
      28,    -1,    86,    80,    28,    48,    28,    -1,    86,    54,
      28,    48,     1,    -1,    86,    28,    48,    28,    -1,    28,
      48,    28,    -1,    28,    28,    -1,     9,    73,    28,    60,
      73,    61,    -1,     9,    73,    28,    60,     1,    61,    -1,
       9,    73,    60,    73,    61,    -1,     9,    73,    28,    73,
      61,    -1,     9,     1,    -1,    10,    92,    89,    -1,    90,
      -1,    89,    54,    90,    -1,    89,    90,    -1,    89,    80,
      90,    -1,    28,    -1,    28,    64,    23,    65,    -1,    16,
      28,    48,    92,    60,   103,    61,    -1,    28,    -1,    28,
      57,    92,    -1,    49,    95,    -1,    13,    73,    28,    -1,
      13,    73,    28,    56,    95,    -1,    97,    -1,    96,    -1,
     100,    -1,   105,    -1,   107,    -1,    99,    -1,   110,    -1,
     109,    -1,   101,    -1,   102,    -1,    27,    -1,    26,    -1,
      23,    -1,    24,    -1,    25,    -1,    22,    -1,    95,    34,
      95,    -1,    95,    39,    95,    -1,    95,    35,    95,    -1,
      95,    36,    95,    -1,    95,    37,    95,    -1,    95,    38,
      95,    -1,    95,    42,    95,    -1,    95,    43,    95,    -1,
      95,    44,    95,    -1,    95,    45,    95,    -1,    95,    46,
      95,    -1,    95,    47,    95,    -1,    95,    51,    95,    -1,
      95,    52,    95,    -1,    95,    53,    95,    -1,    95,    64,
      95,    65,    -1,    98,    -1,    39,    95,    -1,    50,    95,
      -1,    33,    95,    -1,    60,    95,    61,    -1,    20,    73,
      28,    95,    -1,    19,    73,    28,    95,    -1,    92,    60,
     103,    61,    -1,    92,    -1,    92,    60,     1,    -1,     4,
      95,     5,    95,     3,    95,    -1,     4,    95,     5,    95,
      -1,    17,    95,    18,   107,    -1,   104,    -1,    -1,   104,
      54,    95,    -1,   104,    80,    95,    -1,    95,    -1,    64,
     103,    65,    -1,    64,   106,    65,    -1,   104,    55,   106,
      -1,   104,    55,   104,    -1,    62,   108,    63,    -1,   108,
      54,    95,    59,    95,    -1,    95,    59,    95,    -1,    58,
     110,    -1,    58,    73,    -1,    58,     1,    -1,   111,    -1,
     113,    -1,    62,   103,    63,    -1,   104,    21,    81,    56,
      95,    -1,   104,    21,    81,    -1,    62,   112,    63,    -1,
      12,   115,    -1,    12,     1,    -1,   116,    -1,    95,    48,
      95,    -1,     1,    48,    95,    -1,    95,    48,     1,    -1,
      11,    95,    -1,    11,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   199,   199,   202,   204,   208,   214,   215,   219,   225,
     226,   227,   228,   235,   236,   237,   238,   239,   240,   241,
     242,   246,   248,   255,   256,   257,   258,   266,   271,   275,
     277,   283,   287,   288,   289,   290,   296,   302,   303,   306,
     311,   316,   319,   322,   329,   339,   346,   356,   360,   367,
     378,   382,   386,   390,   397,   398,   402,   407,   411,   415,
     419,   424,   431,   433,   435,   439,   443,   450,   463,   469,
     475,   479,   488,   492,   501,   506,   509,   515,   522,   523,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     540,   542,   544,   546,   548,   550,   555,   559,   561,   563,
     565,   567,   569,   571,   573,   575,   577,   579,   581,   583,
     585,   587,   589,   593,   595,   597,   599,   603,   605,   610,
     620,   624,   631,   633,   638,   650,   651,   655,   659,   663,
     672,   673,   678,   679,   683,   695,   700,   708,   710,   715,
     723,   724,   728,   739,   743,   752,   766,   767,   774,   778,
     782,   786,   793,   795
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ELSE", "IF", "THEN", "TYPE", "RANDOM",
  "FIXED", "ORIGIN", "DISTINCT", "QUERY", "OBS", "PARAM", "LIST", "MAP",
  "DISTRIBUTION", "CASE", "IN", "EXISTS_", "FORALL_", "FOR", "NULLITY",
  "INT_LITERAL", "DOUBLE_LITERAL", "BOOLEAN_LITERAL", "CHAR_LITERAL",
  "STRING_LITERAL", "ID", "PARFACTOR", "FACTOR", "ERROR", "ELSEIF", "AT_",
  "PLUS_", "MULT_", "DIV_", "MOD_", "POWER_", "MINUS_", "UMINUS", "LST",
  "LT_", "GT_", "LEQ_", "GEQ_", "EQEQ_", "NEQ_", "EQ_", "DISTRIB", "NOT_",
  "AND_", "OR_", "DOUBLERIGHTARROW", "COMMA", "SEMI", "COLON", "DOT",
  "NUMSIGN", "RIGHTARROW", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "$accept", "program", "opt_statement_lst",
  "statement_lst", "statement", "declaration_stmt", "type_decl", "type",
  "list_type", "array_type_or_sub", "array_type", "map_type",
  "opt_parenthesized_type_var_lst", "var_decl", "extra_commas",
  "type_var_lst", "fixed_func_decl", "rand_func_decl", "number_stmt",
  "opt_parenthesized_origin_var_list", "origin_var_list",
  "origin_func_decl", "distinct_decl", "id_or_subid_list", "id_or_subid",
  "distribution_decl", "refer_name", "dependency_statement_body",
  "parameter_decl", "expression", "literal", "operation_expr",
  "unary_operation_expr", "quantified_formula", "function_call", "if_expr",
  "case_expr", "opt_expression_list", "expression_list",
  "list_construct_expression", "semi_colon_separated_expression_list",
  "map_construct_expression", "expression_pair_list", "number_expr",
  "set_expr", "explicit_set", "comprehension_expr", "tuple_set",
  "evidence_stmt", "evidence", "value_evidence", "query_stmt", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    68,    68,    69,    69,    69,    69,    70,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    73,    73,    73,    73,    74,    75,    76,
      76,    77,    78,    78,    78,    78,    79,    80,    80,    81,
      81,    81,    81,    81,    82,    82,    83,    83,    83,    84,
      84,    84,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    87,    87,    87,    87,    87,    88,    89,    89,
      89,    89,    90,    90,    91,    92,    92,    93,    94,    94,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    98,    98,    98,    98,    99,    99,   100,
     100,   100,   101,   101,   102,   103,   103,   104,   104,   104,
     105,   105,   106,   106,   107,   108,   108,   109,   109,   109,
     110,   110,   111,   112,   112,   113,   114,   114,   115,   116,
     116,   116,   117,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     4,     2,     2,
       3,     6,     0,     2,     3,     1,     2,     2,     2,     3,
       1,     3,     2,     3,     6,     2,     5,     3,     2,     4,
       3,     5,     3,     2,     3,     0,     5,     5,     5,     4,
       3,     2,     6,     6,     5,     5,     2,     3,     1,     3,
       2,     3,     1,     4,     7,     1,     3,     2,     3,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     1,     2,     2,     2,     3,     4,     4,     4,
       1,     3,     6,     4,     4,     1,     0,     3,     3,     1,
       3,     3,     3,     3,     3,     5,     3,     2,     2,     2,
       1,     1,     3,     5,     3,     3,     2,     2,     1,     3,
       3,     3,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     0,     8,     9,    13,    14,    15,
      17,    16,    18,    20,    19,    10,    11,    22,    21,    48,
       0,     0,    75,     0,    24,     0,    26,    25,    23,    45,
       0,    66,     0,     0,   153,     0,     0,     0,     0,    95,
      92,    93,    94,    91,    90,     0,     0,     0,     0,     0,
     126,   126,   120,   152,    81,    80,   112,    85,    82,    88,
      89,    83,    84,    87,    86,   140,   141,   147,     0,   146,
     148,     0,     0,    53,     0,     0,     0,     1,     7,     6,
       0,    47,     0,     0,     0,    32,    29,     0,    28,    32,
       0,     0,    72,    67,    68,     0,     0,     0,     0,   115,
     113,   114,   139,   126,   138,   137,     0,   129,     0,   125,
       0,     0,   129,     0,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,     0,     0,     0,    50,
      52,     0,     5,    77,     0,     0,    76,     0,     0,     0,
      40,    35,    30,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,   116,     0,   142,     0,     0,
       0,     0,   134,   145,   130,     0,   131,   121,     0,   125,
      96,    98,    99,   100,   101,    97,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,   150,   151,   149,     0,
       0,    61,     0,     0,     0,    54,     0,     0,    49,    27,
       0,    33,     0,    36,    46,     0,    42,     0,     0,     0,
       0,    65,    64,     0,    37,    69,    38,    71,   123,     0,
     124,   118,   117,   136,   144,   127,   128,     0,   133,   132,
     119,   111,    79,   126,    60,     0,     0,     0,    51,     0,
      34,    43,    39,    41,    44,    63,    62,    73,     0,     0,
       0,     0,     0,    59,     0,     0,    31,   122,   143,   135,
      74,    58,    56,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,   158,    34,    35,
      36,    37,   159,   160,   180,   161,    18,    19,    20,    85,
     148,    21,    22,   103,   104,    23,    62,    91,    24,   122,
      64,    65,    66,    67,    68,    69,    70,   118,   119,    71,
     125,    72,   120,    73,    74,    75,   121,    76,    25,    79,
      80,    26
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
     140,  -155,    30,   190,   202,   251,   -13,   271,   319,   179,
       6,     5,    51,  -155,   306,     1,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,    10,
      47,    53,    44,    82,  -155,    52,    54,  -155,    75,  -155,
     126,  -155,     0,   127,  -155,   588,   588,   179,   179,  -155,
    -155,  -155,  -155,  -155,  -155,   588,   588,   588,    15,   588,
     588,   588,   101,   805,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,   114,   689,  -155,
    -155,   142,   120,  -155,   160,    10,    31,  -155,   141,  -155,
     588,  -155,   167,   179,   -13,     7,  -155,   134,  -155,     7,
     162,   179,   137,    50,  -155,   619,   642,   183,   184,   149,
     149,   149,  -155,   588,  -155,  -155,   712,   743,   151,    -9,
      33,   152,   805,   155,    39,   158,   223,   588,   588,   588,
     588,   588,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   588,   588,   588,   367,   169,   -13,   161,   -17,  -155,
    -155,   180,  -155,   805,   188,   181,  -155,    83,   205,    10,
    -155,    88,  -155,   189,   254,   177,   192,   221,    58,   129,
    -155,   588,   195,   588,   588,  -155,   588,  -155,   179,   492,
     540,   588,  -155,  -155,  -155,   588,  -155,  -155,   193,   206,
     144,   149,   149,   149,   149,   144,   851,   851,   851,   851,
     851,   851,   865,   865,   828,   665,   805,  -155,   805,   588,
     199,  -155,   239,   222,   130,  -155,   131,   415,  -155,  -155,
     179,  -155,    27,  -155,  -155,    12,  -155,    91,   588,   210,
     213,  -155,  -155,   211,  -155,  -155,  -155,  -155,   446,   588,
    -155,   805,   805,   805,   172,   805,   805,   774,    39,  -155,
    -155,  -155,   805,   588,  -155,   249,   230,   232,  -155,   243,
    -155,  -155,  -155,  -155,   805,  -155,  -155,  -155,   588,   743,
     588,   588,   228,  -155,    35,   264,  -155,   805,   805,   805,
    -155,  -155,  -155,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,  -155,   286,  -155,  -155,    -1,  -155,  -155,
    -155,  -155,   203,  -154,   -79,   -93,  -155,  -155,  -155,   215,
    -155,  -155,  -155,  -155,   -94,  -155,    14,   -75,  -155,    -7,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,   -56,   -47,  -155,
     118,   133,  -155,  -155,   250,  -155,  -155,  -155,  -155,  -155,
    -155,  -155
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -127
static const yytype_int16 yytable[] =
{
      63,    78,    33,    40,    42,   123,    83,   226,    81,   170,
     149,   213,   178,   261,   124,    32,   112,    38,    38,    38,
      43,    30,    31,    38,   169,    86,    30,    31,   100,    30,
      31,    27,   150,    32,    82,    32,   281,   214,   105,   106,
      32,    30,    31,    32,   215,   179,   107,   108,   109,   110,
     111,    87,   116,   117,   -55,    32,    89,   114,    28,    90,
     101,    38,    38,   282,   222,    84,   234,   157,   226,   216,
     188,   262,    38,   263,   235,   237,   218,   113,   102,   189,
     -55,   225,   227,   153,   224,   244,   102,   181,   260,    92,
     226,    84,   155,   179,   185,    93,   182,    30,    31,   165,
     166,    94,    30,    31,   168,    30,    31,    38,   156,    38,
      95,    32,   234,    38,    38,    38,    32,    96,    97,    32,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   208,   248,    98,
      -3,     1,   225,   227,   221,   236,     2,     3,     4,     5,
       6,     7,     8,     9,    99,   102,    10,   102,   256,   257,
     210,   126,   143,   230,   238,   227,   241,   242,   146,   243,
     145,    38,   245,   246,   247,    38,    30,    31,    38,   128,
     129,   130,   131,   236,   234,   236,    30,    31,   147,   211,
      32,    29,    38,    30,    31,   154,   152,   272,    11,   162,
      32,   167,   252,    39,    30,    31,   189,    32,   142,   212,
     153,   173,   174,   142,   177,   183,    30,    31,    32,   259,
     184,   264,   164,   186,   187,   209,   225,    45,   270,   217,
      32,   219,   269,   223,    38,   220,    38,   228,   231,    38,
      46,    38,    47,    48,   233,    49,    50,    51,    52,    53,
      54,    32,    41,   232,   250,   229,    55,   239,    38,   253,
     179,   277,    56,   278,   279,    30,    31,   254,    30,    31,
     255,   265,    44,    57,   266,    45,   267,   273,   274,    32,
     275,    58,    32,    59,  -126,    60,   276,    61,    46,   280,
      47,    48,   283,    49,    50,    51,    52,    53,    54,    32,
      88,   151,   163,   249,    55,   240,    -4,     1,   115,     0,
      56,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      77,    57,    10,    45,     0,     0,     0,     0,     0,    58,
       0,    59,     0,    60,     0,    61,    46,     0,    47,    48,
       0,    49,    50,    51,    52,    53,    54,    32,     0,     0,
       0,     0,    55,     0,     0,     0,     0,     0,    56,     0,
       0,     0,     0,     0,    11,     0,     0,     0,   207,    57,
       0,    45,     0,     0,     0,     0,     0,    58,     0,    59,
       0,    60,     0,    61,    46,     0,    47,    48,     0,    49,
      50,    51,    52,    53,    54,    32,     0,     0,     0,     0,
      55,     0,     0,     0,     0,     0,    56,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   258,    57,     0,    45,
       0,     0,     0,     0,     0,    58,     0,    59,     0,    60,
       0,    61,    46,     0,    47,    48,     0,    49,    50,    51,
      52,    53,    54,    32,     0,     0,     0,     0,    55,   268,
       0,     0,     0,     0,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,     0,
       0,     0,     0,    58,     0,    59,     0,    60,     0,    61,
     127,   128,   129,   130,   131,   132,     0,     0,   133,   134,
     135,   136,   137,   138,     0,     0,    45,   139,   140,   141,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
     142,    47,    48,     0,    49,    50,    51,    52,    53,    54,
      32,     0,     0,     0,     0,    55,     0,     0,     0,     0,
       0,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,    45,     0,   234,     0,     0,     0,
      58,     0,    59,     0,    60,     0,    61,    46,     0,    47,
      48,     0,    49,    50,    51,    52,    53,    54,    32,     0,
       0,     0,     0,    55,     0,     0,     0,     0,     0,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,    45,     0,   236,     0,     0,     0,    58,     0,
      59,     0,    60,     0,    61,    46,     0,    47,    48,     0,
      49,    50,    51,    52,    53,    54,    32,     0,     0,     0,
       0,    55,     0,     0,   171,     0,     0,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,     0,
       0,     0,     0,     0,     0,     0,    58,     0,    59,     0,
      60,     0,    61,   127,   128,   129,   130,   131,   132,     0,
     172,   133,   134,   135,   136,   137,   138,     0,     0,     0,
     139,   140,   141,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,   142,   133,   134,   135,   136,   137,   138,
       0,     0,     0,   139,   140,   141,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,   142,   133,   134,   135,
     136,   137,   138,     0,     0,     0,   139,   140,   141,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   142,
     251,   133,   134,   135,   136,   137,   138,   144,     0,     0,
     139,   140,   141,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,   142,   133,   134,   135,   136,   137,   138,
       0,     0,     0,   139,   140,   141,     0,     0,     0,     0,
       0,     0,     0,   175,     0,     0,   142,   127,   128,   129,
     130,   131,   132,     0,     0,   133,   134,   135,   136,   137,
     138,     0,     0,     0,   139,   140,   141,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,   142,   127,   128,
     129,   130,   131,   132,     0,     0,   133,   134,   135,   136,
     137,   138,     0,     0,     0,   139,   140,   141,     0,     0,
       0,     0,     0,   271,     0,     0,     0,     0,   142,   127,
     128,   129,   130,   131,   132,     0,     0,   133,   134,   135,
     136,   137,   138,     0,     0,     0,   139,   140,   141,     0,
       0,     0,   127,   128,   129,   130,   131,   132,     0,   142,
     133,   134,   135,   136,   137,   138,     0,     0,     0,   139,
     140,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,     0,   142,  -127,  -127,  -127,  -127,  -127,  -127,   127,
     128,   129,   130,   131,   132,     0,     0,   133,   134,   135,
     136,   137,   138,     0,     0,   142,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   142
};

static const yytype_int16 yycheck[] =
{
       7,     8,     3,     4,     5,    61,     1,   161,     9,   103,
      85,    28,    21,     1,    61,    28,     1,     3,     4,     5,
       6,    14,    15,     9,   103,    11,    14,    15,    28,    14,
      15,     1,     1,    28,    28,    28,     1,    54,    45,    46,
      28,    14,    15,    28,    61,    54,    47,    48,    55,    56,
      57,     0,    59,    60,    49,    28,    55,    58,    28,    49,
      60,    47,    48,    28,   157,    60,    54,    60,   222,   148,
     126,   225,    58,   227,   168,   169,   151,    62,    28,   126,
      49,    54,   161,    90,   159,   178,    28,    54,    61,    42,
     244,    60,    93,    54,    55,    42,    63,    14,    15,   100,
     101,    57,    14,    15,    54,    14,    15,    93,    94,    95,
      28,    28,    54,    99,   100,   101,    28,    65,    64,    28,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   185,    64,
       0,     1,    54,   222,    61,    54,     6,     7,     8,     9,
      10,    11,    12,    13,    28,    28,    16,    28,    28,    28,
     146,    60,    48,   164,   171,   244,   173,   174,    48,   176,
      28,   157,   179,   180,   181,   161,    14,    15,   164,    35,
      36,    37,    38,    54,    54,    54,    14,    15,    28,    28,
      28,     1,   178,    14,    15,    28,    55,   253,    58,    65,
      28,    64,   209,     1,    14,    15,   253,    28,    64,    48,
     217,    28,    28,    64,    63,    63,    14,    15,    28,   220,
      65,   228,    60,    65,     1,    56,    54,     4,    56,    49,
      28,    43,   239,    28,   220,    54,   222,    48,    61,   225,
      17,   227,    19,    20,    23,    22,    23,    24,    25,    26,
      27,    28,     1,    61,    61,     1,    33,    62,   244,    60,
      54,   268,    39,   270,   271,    14,    15,    28,    14,    15,
      48,    61,     1,    50,    61,     4,    65,    28,    48,    28,
      48,    58,    28,    60,    61,    62,    43,    64,    17,    61,
      19,    20,    28,    22,    23,    24,    25,    26,    27,    28,
      14,    86,    99,   185,    33,   172,     0,     1,    58,    -1,
      39,    -1,     6,     7,     8,     9,    10,    11,    12,    13,
       1,    50,    16,     4,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    60,    -1,    62,    -1,    64,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,     1,    50,
      -1,     4,    -1,    -1,    -1,    -1,    -1,    58,    -1,    60,
      -1,    62,    -1,    64,    17,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    50,    -1,     4,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    60,    -1,    62,
      -1,    64,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    -1,    33,     3,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    60,    -1,    62,    -1,    64,
      34,    35,    36,    37,    38,    39,    -1,    -1,    42,    43,
      44,    45,    46,    47,    -1,    -1,     4,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      64,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,     4,    -1,    54,    -1,    -1,    -1,
      58,    -1,    60,    -1,    62,    -1,    64,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,     4,    -1,    54,    -1,    -1,    -1,    58,    -1,
      60,    -1,    62,    -1,    64,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      -1,    33,    -1,    -1,     5,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    60,    -1,
      62,    -1,    64,    34,    35,    36,    37,    38,    39,    -1,
      18,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      51,    52,    53,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    -1,    64,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    -1,    64,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    51,    52,    53,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    64,
      65,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      51,    52,    53,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    -1,    64,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    64,    34,    35,    36,
      37,    38,    39,    -1,    -1,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    64,    34,    35,
      36,    37,    38,    39,    -1,    -1,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,
      -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    64,    34,
      35,    36,    37,    38,    39,    -1,    -1,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    51,    52,    53,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    39,    -1,    64,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    -1,    64,    42,    43,    44,    45,    46,    47,    34,
      35,    36,    37,    38,    39,    -1,    -1,    42,    43,    44,
      45,    46,    47,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,     8,     9,    10,    11,    12,    13,
      16,    58,    67,    68,    69,    70,    71,    72,    82,    83,
      84,    87,    88,    91,    94,   114,   117,     1,    28,     1,
      14,    15,    28,    73,    74,    75,    76,    77,    92,     1,
      73,     1,    73,    92,     1,     4,    17,    19,    20,    22,
      23,    24,    25,    26,    27,    33,    39,    50,    58,    60,
      62,    64,    92,    95,    96,    97,    98,    99,   100,   101,
     102,   105,   107,   109,   110,   111,   113,     1,    95,   115,
     116,    73,    28,     1,    60,    85,    92,     0,    70,    55,
      49,    93,    42,    42,    57,    28,    65,    64,    64,    28,
      28,    60,    28,    89,    90,    95,    95,    73,    73,    95,
      95,    95,     1,    62,    73,   110,    95,    95,   103,   104,
     108,   112,    95,   103,   104,   106,    60,    34,    35,    36,
      37,    38,    39,    42,    43,    44,    45,    46,    47,    51,
      52,    53,    64,    48,    48,    28,    48,    28,    86,    93,
       1,    85,    55,    95,    28,    73,    92,    60,    73,    78,
      79,    81,    65,    78,    60,    73,    73,    64,    54,    80,
      90,     5,    18,    28,    28,    61,    59,    63,    21,    54,
      80,    54,    63,    63,    65,    55,    65,     1,   103,   104,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,     1,    95,    56,
      92,    28,    48,    28,    54,    61,    80,    49,    93,    43,
      54,    61,    81,    28,    93,    54,    79,    80,    48,     1,
      73,    61,    61,    23,    54,    90,    54,    90,    95,    62,
     107,    95,    95,    95,    81,    95,    95,    95,   104,   106,
      61,    65,    95,    60,    28,    48,    28,    28,     1,    73,
      61,     1,    79,    79,    95,    61,    61,    65,     3,    95,
      56,    59,   103,    28,    48,    48,    43,    95,    95,    95,
      61,     1,    28,    28
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 5:
#line 209 "blog.yacc"
    {
    if((yyvsp[(2) - (3)].stmt) != NULL){
      blog->add((yyvsp[(2) - (3)].stmt));
    }
  }
    break;

  case 6:
#line 214 "blog.yacc"
    { blog->add((yyvsp[(1) - (2)].stmt)); }
    break;

  case 7:
#line 216 "blog.yacc"
    {
    yyerror("missing ; after statement");
  }
    break;

  case 8:
#line 219 "blog.yacc"
    {
    yyerror("missing ; after statement");
  }
    break;

  case 9:
#line 225 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 10:
#line 226 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 11:
#line 227 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 12:
#line 228 "blog.yacc"
    {
    yyerror("incorrect statement");
  }
    break;

  case 13:
#line 235 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 14:
#line 236 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].funcdec); }
    break;

  case 15:
#line 237 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].funcdec); }
    break;

  case 16:
#line 238 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].origdec); }
    break;

  case 17:
#line 239 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(1) - (1)].numstdec); }
    break;

  case 18:
#line 240 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].distdec); }
    break;

  case 19:
#line 241 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 20:
#line 242 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 21:
#line 247 "blog.yacc"
    { (yyval.stmt) = new TypDecl(curr_line, curr_col, Symbol((yyvsp[(2) - (2)].sval)->getValue())); }
    break;

  case 22:
#line 249 "blog.yacc"
    {
    yyerror("invalid type declaration");
  }
    break;

  case 23:
#line 255 "blog.yacc"
    { (yyval.typ) = new Ty(curr_line, curr_col, Symbol((yyvsp[(1) - (1)].sval)->getValue())); }
    break;

  case 24:
#line 256 "blog.yacc"
    { (yyval.typ) = (yyvsp[(1) - (1)].typ); }
    break;

  case 25:
#line 257 "blog.yacc"
    { (yyval.typ) = (yyvsp[(1) - (1)].typ); }
    break;

  case 26:
#line 258 "blog.yacc"
    {(yyval.typ) = (yyvsp[(1) - (1)].typ);}
    break;

  case 27:
#line 267 "blog.yacc"
    { (yyval.typ) = new Ty(curr_line, curr_col, Symbol((yyvsp[(3) - (4)].sval)->getValue())); }
    break;

  case 28:
#line 271 "blog.yacc"
    {}
    break;

  case 29:
#line 276 "blog.yacc"
    {}
    break;

  case 30:
#line 278 "blog.yacc"
    {}
    break;

  case 31:
#line 283 "blog.yacc"
    { (yyval.typ) = (yyvsp[(3) - (6)].typ); }
    break;

  case 32:
#line 287 "blog.yacc"
    { (yyval.varlist) = NULL; }
    break;

  case 33:
#line 288 "blog.yacc"
    {(yyval.varlist) = NULL; }
    break;

  case 34:
#line 289 "blog.yacc"
    { (yyval.varlist) = (yyvsp[(2) - (3)].varlist); }
    break;

  case 35:
#line 290 "blog.yacc"
    {
    yyerror("missing parentheses");
  }
    break;

  case 36:
#line 296 "blog.yacc"
    { 
    (yyval.vardec) = new VarDecl(curr_line, curr_col, *(yyvsp[(1) - (2)].typ), Symbol((yyvsp[(2) - (2)].sval)->getValue())); 
  }
    break;

  case 39:
#line 306 "blog.yacc"
    { 
      (yyval.varlist) = (yyvsp[(1) - (3)].varlist); 
      (yyval.varlist)->push_back(*(yyvsp[(3) - (3)].vardec));
      delete((yyvsp[(3) - (3)].vardec));
    }
    break;

  case 40:
#line 311 "blog.yacc"
    { 
      (yyval.varlist) = new vector<VarDecl>();
      (yyval.varlist)->push_back(*(yyvsp[(1) - (1)].vardec));
      delete((yyvsp[(1) - (1)].vardec));
    }
    break;

  case 41:
#line 316 "blog.yacc"
    {
    yyerror("extra commas in type variable list");
  }
    break;

  case 42:
#line 319 "blog.yacc"
    {
    yyerror("missing commas");
  }
    break;

  case 43:
#line 323 "blog.yacc"
    {
    yyerror("incorrect variable declaration");
  }
    break;

  case 44:
#line 330 "blog.yacc"
    { 
      (yyval.funcdec) = new FuncDecl(curr_line, curr_col, false, *((yyvsp[(2) - (6)].typ)), Symbol((yyvsp[(3) - (6)].sval)->getValue()), (yyvsp[(6) - (6)].exp));
      if((yyvsp[(4) - (6)].varlist) != NULL){
        for(size_t i = 0; i < (yyvsp[(4) - (6)].varlist)->size(); i++){
          (yyval.funcdec)->addArg((*(yyvsp[(4) - (6)].varlist))[i]);
        }
        delete((yyvsp[(4) - (6)].varlist));
      }
    }
    break;

  case 45:
#line 340 "blog.yacc"
    {
    yyerror("error in fixed function declaration");
  }
    break;

  case 46:
#line 347 "blog.yacc"
    { 
      (yyval.funcdec) = new FuncDecl(curr_line, curr_col, true, *((yyvsp[(2) - (5)].typ)), Symbol((yyvsp[(3) - (5)].sval)->getValue()), (yyvsp[(5) - (5)].exp));
      if((yyvsp[(4) - (5)].varlist) != NULL){
        for(size_t i = 0; i < (yyvsp[(4) - (5)].varlist)->size(); i++){
          (yyval.funcdec)->addArg((*(yyvsp[(4) - (5)].varlist))[i]);
        }
        delete((yyvsp[(4) - (5)].varlist));
      }
    }
    break;

  case 47:
#line 357 "blog.yacc"
    {
      yyerror("incorrect function header, return type, or function name");
    }
    break;

  case 48:
#line 361 "blog.yacc"
    {
      yyerror("error in random function declaration");
    }
    break;

  case 49:
#line 368 "blog.yacc"
    {
      (yyval.numstdec) = new NumStDecl(curr_line, curr_col, Symbol((yyvsp[(2) - (4)].sval)->getValue()), (yyvsp[(4) - (4)].exp));
      if((yyvsp[(3) - (4)].varlst) != NULL){
        for(size_t i = 0; i < (yyvsp[(3) - (4)].varlst)->size(); i++){
          (yyval.numstdec)->add(get<0>((*(yyvsp[(3) - (4)].varlst))[i]), get<1>((*(yyvsp[(3) - (4)].varlst))[i]));
        }
        delete((yyvsp[(3) - (4)].varlst));
      }
      //$$->add(Symbol($4->getValue()), Symbol($6->getValue()));
    }
    break;

  case 50:
#line 379 "blog.yacc"
    {
    yyerror("missing type name in number statement");
  }
    break;

  case 51:
#line 383 "blog.yacc"
    {
    yyerror("missing body in number statement");
  }
    break;

  case 52:
#line 387 "blog.yacc"
    {
    yyerror("missing body in number statement");
  }
    break;

  case 53:
#line 391 "blog.yacc"
    {
    yyerror("error in number statement");
  }
    break;

  case 54:
#line 397 "blog.yacc"
    {(yyval.varlst) = (yyvsp[(2) - (3)].varlst); }
    break;

  case 55:
#line 398 "blog.yacc"
    {(yyval.varlst) = NULL; }
    break;

  case 56:
#line 403 "blog.yacc"
    {
    (yyval.varlst) = (yyvsp[(1) - (5)].varlst);
    (yyval.varlst)->push_back(make_tuple(Symbol((yyvsp[(3) - (5)].sval)->getValue()), Symbol((yyvsp[(5) - (5)].sval)->getValue())));
  }
    break;

  case 57:
#line 408 "blog.yacc"
    {
    yyerror("extra commas");
  }
    break;

  case 58:
#line 412 "blog.yacc"
    {
    yyerror("missing origin variable name");
  }
    break;

  case 59:
#line 416 "blog.yacc"
    {
    yyerror("missing comma");
  }
    break;

  case 60:
#line 420 "blog.yacc"
    { 
    (yyval.varlst) = new vector<tuple<Symbol, Symbol>>();
    (yyval.varlst)->push_back(make_tuple(Symbol((yyvsp[(1) - (3)].sval)->getValue()), Symbol((yyvsp[(3) - (3)].sval)->getValue())));
  }
    break;

  case 61:
#line 425 "blog.yacc"
    {
    yyerror("missing =");
  }
    break;

  case 62:
#line 432 "blog.yacc"
    { (yyval.origdec) = new OriginDecl(curr_line, curr_col, (yyvsp[(2) - (6)].typ)->getTyp(), Symbol((yyvsp[(3) - (6)].sval)->getValue()), (yyvsp[(5) - (6)].typ)->getTyp());  }
    break;

  case 63:
#line 434 "blog.yacc"
    { yyerror("syntax error in type argument of origin function"); }
    break;

  case 64:
#line 436 "blog.yacc"
    {
    yyerror("missing type or origin function name");
  }
    break;

  case 65:
#line 440 "blog.yacc"
    {
    yyerror("missing ( in origin function");
  }
    break;

  case 66:
#line 444 "blog.yacc"
    {
    yyerror("error in origin function definition");
  }
    break;

  case 67:
#line 451 "blog.yacc"
    {
      (yyval.distdec) = new DistinctDecl(curr_line, curr_col, Symbol((yyvsp[(2) - (3)].sval)->getValue()));
      if ((yyvsp[(3) - (3)].symbintvect) != NULL){
        for(size_t i = 0; i < (yyvsp[(3) - (3)].symbintvect)->size(); i++){
          (yyval.distdec)->add(get<0>((*(yyvsp[(3) - (3)].symbintvect))[i]), get<1>((*(yyvsp[(3) - (3)].symbintvect))[i]));
        }
        delete((yyvsp[(3) - (3)].symbintvect));
      }
    }
    break;

  case 68:
#line 464 "blog.yacc"
    {
      (yyval.symbintvect) = new vector<tuple<string, int>>();
      (yyval.symbintvect)->push_back(*(yyvsp[(1) - (1)].symbintpair));
      delete((yyvsp[(1) - (1)].symbintpair));
    }
    break;

  case 69:
#line 470 "blog.yacc"
    {
      (yyval.symbintvect) = (yyvsp[(1) - (3)].symbintvect);
      (yyval.symbintvect)->push_back(*(yyvsp[(3) - (3)].symbintpair));
      delete((yyvsp[(3) - (3)].symbintpair));
    }
    break;

  case 70:
#line 476 "blog.yacc"
    {
      yyerror("missing comma");
    }
    break;

  case 71:
#line 480 "blog.yacc"
    {
      yyerror("missing comma");
    }
    break;

  case 72:
#line 488 "blog.yacc"
    { 
        //tuple<string, int> idint = make_tuple($1->getValue(), 1);
        (yyval.symbintpair) = new tuple<string, int>((yyvsp[(1) - (1)].sval)->getValue(), 1);
       }
    break;

  case 73:
#line 493 "blog.yacc"
    { 
      //tuple<string, int> idint2 = make_tuple($1->getValue(), $3->getValue());
      (yyval.symbintpair) = new tuple<string, int>((yyvsp[(1) - (4)].sval)->getValue(), (yyvsp[(3) - (4)].ival)->getValue());
    }
    break;

  case 74:
#line 502 "blog.yacc"
    { }
    break;

  case 75:
#line 506 "blog.yacc"
    { 
      (yyval.sval) = new BLOGSymbol<string>(curr_line, curr_col, (yyvsp[(1) - (1)].sval)->getValue());
    }
    break;

  case 76:
#line 509 "blog.yacc"
    {
      (yyval.sval) = new BLOGSymbol<string>(curr_line, curr_col, (yyvsp[(1) - (3)].sval)->getValue() + "." + (yyvsp[(3) - (3)].sval)->getValue());
    }
    break;

  case 77:
#line 516 "blog.yacc"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp); }
    break;

  case 78:
#line 522 "blog.yacc"
    { }
    break;

  case 79:
#line 523 "blog.yacc"
    { }
    break;

  case 80:
#line 527 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 81:
#line 528 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 82:
#line 529 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 83:
#line 530 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 84:
#line 531 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].mapexp);}
    break;

  case 85:
#line 532 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 86:
#line 533 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].setexp); }
    break;

  case 87:
#line 534 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].cardexp); }
    break;

  case 88:
#line 535 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 89:
#line 536 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 90:
#line 541 "blog.yacc"
    {(yyval.exp) = new StringLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].sval)->getValue()); }
    break;

  case 91:
#line 543 "blog.yacc"
    {string charstr(1, (yyvsp[(1) - (1)].chrval)->getValue()); (yyval.exp) = new StringLiteral(curr_line, curr_col, charstr); }
    break;

  case 92:
#line 545 "blog.yacc"
    {(yyval.exp) = new IntLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].ival)->getValue()); }
    break;

  case 93:
#line 547 "blog.yacc"
    {(yyval.exp) = new DoubleLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].dblval)->getValue()); }
    break;

  case 94:
#line 549 "blog.yacc"
    {(yyval.exp) = new BoolLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].boolval)->getValue()); }
    break;

  case 95:
#line 551 "blog.yacc"
    {(yyval.exp) = new NullLiteral(curr_line, curr_col); }
    break;

  case 96:
#line 556 "blog.yacc"
    { 
      (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::PLUS, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));   
    }
    break;

  case 97:
#line 560 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::MINUS, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 98:
#line 562 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::MUL, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 99:
#line 564 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::DIV, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 100:
#line 566 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::MOD, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 101:
#line 568 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::POWER, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 102:
#line 570 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::LT, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 103:
#line 572 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::GT, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 104:
#line 574 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::LE, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 105:
#line 576 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::GE, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 106:
#line 578 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::EQ, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 107:
#line 580 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::NEQ, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 108:
#line 582 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::AND, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 109:
#line 584 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::OR, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 110:
#line 586 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::IMPLY, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 111:
#line 588 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].exp)); }
    break;

  case 112:
#line 589 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 113:
#line 594 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, new IntLiteral(curr_line, curr_col, 0), (yyvsp[(2) - (2)].exp)); }
    break;

  case 114:
#line 596 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::NOT, NULL, (yyvsp[(2) - (2)].exp)); }
    break;

  case 115:
#line 598 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::AT, NULL, (yyvsp[(2) - (2)].exp)); }
    break;

  case 116:
#line 599 "blog.yacc"
    {(yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 117:
#line 604 "blog.yacc"
    {(yyval.exp) = new QuantExpr(curr_line, curr_col, AbsynConstant::FORALL, *(new VarDecl(curr_line, curr_col, *(yyvsp[(2) - (4)].typ), Symbol((yyvsp[(3) - (4)].sval)->getValue()))), (yyvsp[(4) - (4)].exp)); }
    break;

  case 118:
#line 606 "blog.yacc"
    {(yyval.exp) = new QuantExpr(curr_line, curr_col, AbsynConstant::EXISTS, *(new VarDecl(curr_line, curr_col, *(yyvsp[(2) - (4)].typ), Symbol((yyvsp[(3) - (4)].sval)->getValue()))), (yyvsp[(4) - (4)].exp)); }
    break;

  case 119:
#line 611 "blog.yacc"
    { 
    (yyval.exp) = new FuncApp(curr_line, curr_col, Symbol((yyvsp[(1) - (4)].sval)->getValue())); 
    if ((yyvsp[(3) - (4)].explst) != NULL){
      for(size_t i = 0; i < (yyvsp[(3) - (4)].explst)->size(); i++){
        (yyval.exp)->add((*(yyvsp[(3) - (4)].explst))[i]);
      }
      delete((yyvsp[(3) - (4)].explst));
    }
  }
    break;

  case 120:
#line 621 "blog.yacc"
    {
    (yyval.exp) = new FuncApp(curr_line, curr_col, Symbol((yyvsp[(1) - (1)].sval)->getValue()));
  }
    break;

  case 121:
#line 625 "blog.yacc"
    {
    yyerror("error in body of function call");
  }
    break;

  case 122:
#line 632 "blog.yacc"
    { (yyval.exp) = new IfExpr(curr_line, curr_col, (yyvsp[(2) - (6)].exp), (yyvsp[(4) - (6)].exp), (yyvsp[(6) - (6)].exp)); }
    break;

  case 123:
#line 634 "blog.yacc"
    { (yyval.exp) = new IfExpr(curr_line, curr_col, (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].exp)); }
    break;

  case 124:
#line 639 "blog.yacc"
    {
    if ((yyvsp[(2) - (4)].exp) != NULL && (yyvsp[(4) - (4)].mapexp) != NULL){
      (yyval.exp) = new CaseExpr(curr_line, curr_col, (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].mapexp));
    }
    else{
      yyerror("error in case expression");
    }
  }
    break;

  case 125:
#line 650 "blog.yacc"
    {(yyval.explst) = (yyvsp[(1) - (1)].explst);}
    break;

  case 126:
#line 651 "blog.yacc"
    {(yyval.explst) = NULL; }
    break;

  case 127:
#line 656 "blog.yacc"
    { (yyval.explst) = (yyvsp[(1) - (3)].explst);
      (yyval.explst)->push_back((yyvsp[(3) - (3)].exp));
    }
    break;

  case 128:
#line 660 "blog.yacc"
    {
    yyerror("extra commas in expression list");
  }
    break;

  case 129:
#line 664 "blog.yacc"
    { 
      (yyval.explst) = new vector<Expr*>();
      (yyval.explst)->push_back((yyvsp[(1) - (1)].exp));
    }
    break;

  case 130:
#line 672 "blog.yacc"
    { }
    break;

  case 131:
#line 673 "blog.yacc"
    { }
    break;

  case 132:
#line 678 "blog.yacc"
    { }
    break;

  case 133:
#line 679 "blog.yacc"
    { }
    break;

  case 134:
#line 683 "blog.yacc"
    { 
    //$$ = $2; 
    (yyval.mapexp) = new MapExpr(curr_line, curr_col);
    for (size_t i = 0; i < (yyvsp[(2) - (3)].exptuplst)->size(); i++){
      (yyval.mapexp)->addMap(get<0>((*(yyvsp[(2) - (3)].exptuplst))[i]), get<1>((*(yyvsp[(2) - (3)].exptuplst))[i]));
    }
    delete((yyvsp[(2) - (3)].exptuplst));
    
  }
    break;

  case 135:
#line 696 "blog.yacc"
    { 
      (yyval.exptuplst) = (yyvsp[(1) - (5)].exptuplst);
      (yyval.exptuplst)->push_back(make_tuple((yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].exp)));
    }
    break;

  case 136:
#line 701 "blog.yacc"
    { 
      (yyval.exptuplst) = new vector<tuple<Expr*, Expr*>>();
      (yyval.exptuplst)->push_back(make_tuple((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)));
    }
    break;

  case 137:
#line 709 "blog.yacc"
    { (yyval.cardexp) = new CardinalityExpr(curr_line, curr_col, (Expr*)(yyvsp[(2) - (2)].setexp)); }
    break;

  case 138:
#line 711 "blog.yacc"
    { 
      VarDecl var(curr_line, curr_col, *(yyvsp[(2) - (2)].typ));
      (yyval.cardexp) = new CardinalityExpr(curr_line, curr_col, new CondSet(curr_line, curr_col, var));
  }
    break;

  case 139:
#line 716 "blog.yacc"
    {
    yyerror("expecting number expression here.");
  }
    break;

  case 140:
#line 723 "blog.yacc"
    {(yyval.setexp) = (yyvsp[(1) - (1)].setexp); }
    break;

  case 141:
#line 724 "blog.yacc"
    {(yyval.setexp) = (yyvsp[(1) - (1)].setexp); }
    break;

  case 142:
#line 729 "blog.yacc"
    {
      (yyval.setexp) = new ListSet(curr_line, curr_col);
      for(size_t i = 0; i < (yyvsp[(2) - (3)].explst)->size(); i++){
        (yyval.setexp)->add((*(yyvsp[(2) - (3)].explst))[i]);
      }
      delete((yyvsp[(2) - (3)].explst));
    }
    break;

  case 143:
#line 740 "blog.yacc"
    {
      (yyval.compexp)[0] = (yyvsp[(1) - (5)].explst); (yyval.compexp)[1] = (yyvsp[(3) - (5)].varlist); (yyval.compexp)[2] = (yyvsp[(5) - (5)].exp);
    }
    break;

  case 144:
#line 744 "blog.yacc"
    {
      (yyval.compexp)[0] = (yyvsp[(1) - (3)].explst); (yyval.compexp)[1] = (yyvsp[(3) - (3)].varlist); (yyval.compexp)[2] = NULL;
    }
    break;

  case 145:
#line 753 "blog.yacc"
    { 
    if ((yyvsp[(2) - (3)].compexp) != NULL){
      (yyval.setexp) = new TupleSetExpr(curr_line, curr_col, *((vector<Expr*>*)(yyvsp[(2) - (3)].compexp)[0]), *((vector<VarDecl>*)(yyvsp[(2) - (3)].compexp)[1]), (Expr*)(yyvsp[(2) - (3)].compexp)[2]); 
      delete((vector<Expr*>*)(yyvsp[(2) - (3)].compexp)[0]);
      delete((vector<VarDecl>*)(yyvsp[(2) - (3)].compexp)[1]);
    }
    else{
      yyerror("invalid tupleset");
    }
  }
    break;

  case 146:
#line 766 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(2) - (2)].stmt); }
    break;

  case 147:
#line 768 "blog.yacc"
    {
    yyerror("incorrect obs statement");
  }
    break;

  case 148:
#line 774 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 149:
#line 779 "blog.yacc"
    {
    (yyval.stmt) = new Evidence(curr_line, curr_col, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); 
  }
    break;

  case 150:
#line 783 "blog.yacc"
    {
    yyerror("incorrect lefthand expression in evidence");
  }
    break;

  case 151:
#line 787 "blog.yacc"
    {
    yyerror("incorrect righthand expression in evidence");
  }
    break;

  case 152:
#line 794 "blog.yacc"
    { (yyval.stmt) = new Query(curr_line, curr_col, (yyvsp[(2) - (2)].exp)); }
    break;

  case 153:
#line 796 "blog.yacc"
    {
    yyerror("invalid query");
  }
    break;


/* Line 1267 of yacc.c.  */
#line 2901 "parser.cpp"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 801 "blog.yacc"




void yyerror(const char *s) {
  cout << "Parse error at line number: " << curr_line << " and column number: " << curr_col << "!  Message: " << s << endl;
  // might as well halt now:
  //exit(-1);
}
