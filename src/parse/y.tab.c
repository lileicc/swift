
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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
#include "../absyn/NumStRef.h"
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


/* Line 189 of yacc.c  */
#line 150 "y.tab.c"

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
     EXISTS_ = 272,
     FORALL_ = 273,
     FOR = 274,
     NULLITY = 275,
     INT_LITERAL = 276,
     DOUBLE_LITERAL = 277,
     BOOLEAN_LITERAL = 278,
     CHAR_LITERAL = 279,
     STRING_LITERAL = 280,
     ID = 281,
     PARFACTOR = 282,
     FACTOR = 283,
     ERROR = 284,
     ELSEIF = 285,
     AT_ = 286,
     PLUS_ = 287,
     MULT_ = 288,
     DIV_ = 289,
     MOD_ = 290,
     POWER_ = 291,
     MINUS_ = 292,
     LST = 293,
     LT_ = 294,
     GT_ = 295,
     LEQ_ = 296,
     GEQ_ = 297,
     EQEQ_ = 298,
     NEQ_ = 299,
     EQ_ = 300,
     DISTRIB = 301,
     NOT_ = 302,
     AND_ = 303,
     OR_ = 304,
     DOUBLERIGHTARROW = 305,
     COMMA = 306,
     SEMI = 307,
     COLON = 308,
     DOT = 309,
     NUMSIGN = 310,
     RIGHTARROW = 311,
     LPAREN = 312,
     RPAREN = 313,
     LBRACE = 314,
     RBRACE = 315,
     LBRACKET = 316,
     RBRACKET = 317
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
#define EXISTS_ 272
#define FORALL_ 273
#define FOR 274
#define NULLITY 275
#define INT_LITERAL 276
#define DOUBLE_LITERAL 277
#define BOOLEAN_LITERAL 278
#define CHAR_LITERAL 279
#define STRING_LITERAL 280
#define ID 281
#define PARFACTOR 282
#define FACTOR 283
#define ERROR 284
#define ELSEIF 285
#define AT_ 286
#define PLUS_ 287
#define MULT_ 288
#define DIV_ 289
#define MOD_ 290
#define POWER_ 291
#define MINUS_ 292
#define LST 293
#define LT_ 294
#define GT_ 295
#define LEQ_ 296
#define GEQ_ 297
#define EQEQ_ 298
#define NEQ_ 299
#define EQ_ 300
#define DISTRIB 301
#define NOT_ 302
#define AND_ 303
#define OR_ 304
#define DOUBLERIGHTARROW 305
#define COMMA 306
#define SEMI 307
#define COLON 308
#define DOT 309
#define NUMSIGN 310
#define RIGHTARROW 311
#define LPAREN 312
#define RPAREN 313
#define LBRACE 314
#define RBRACE 315
#define LBRACKET 316
#define RBRACKET 317




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 77 "blog.yacc"

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
  class NumStRef* numref;
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
  vector<VarDecl>* varlist;
  vector<tuple<Expr*, Expr*>>* exptuplst;
  vector<Expr*>* explst;
  vector<tuple<Symbol, Symbol>>* varlst;



/* Line 214 of yacc.c  */
#line 360 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 372 "y.tab.c"

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
# if YYENABLE_NLS
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   596

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNRULES -- Number of states.  */
#define YYNSTATES  254

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

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
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    39,
      41,    43,    45,    47,    52,    59,    60,    63,    67,    70,
      74,    76,    84,    91,    97,   101,   102,   108,   112,   121,
     125,   128,   134,   138,   145,   147,   151,   154,   156,   162,
     166,   169,   170,   175,   182,   184,   186,   188,   190,   192,
     194,   196,   198,   200,   202,   204,   206,   208,   210,   212,
     214,   218,   222,   226,   230,   234,   238,   242,   246,   250,
     254,   258,   262,   266,   270,   274,   279,   281,   284,   287,
     290,   294,   299,   304,   309,   311,   317,   319,   320,   324,
     326,   330,   334,   338,   342,   346,   352,   356,   359,   362,
     370,   372,   374,   378,   385,   390,   394,   396,   398,   402,
     406,   410
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    65,    -1,    -1,    66,    -1,    66,    67,
      -1,    67,    -1,    68,    -1,   108,    -1,   112,    -1,    69,
      -1,    77,    -1,    78,    -1,   104,    -1,    79,    -1,    83,
      -1,    88,    -1,    82,    -1,     6,    26,    52,    -1,    71,
      -1,    72,    -1,    73,    -1,    26,    -1,    14,    39,    26,
      40,    -1,    15,    39,    70,    51,    70,    40,    -1,    -1,
      57,    58,    -1,    57,    76,    58,    -1,    70,    26,    -1,
      76,    51,    75,    -1,    75,    -1,     8,    70,    26,    74,
      45,    89,    52,    -1,     7,    70,    26,    74,    86,    52,
      -1,    55,    71,    80,    86,    52,    -1,    57,    81,    58,
      -1,    -1,    81,    51,    26,    45,    26,    -1,    26,    45,
      26,    -1,    16,    26,    45,    85,    57,    97,    58,    52,
      -1,    10,    84,    52,    -1,    71,    26,    -1,    71,    26,
      61,    21,    62,    -1,    84,    51,    26,    -1,    84,    51,
      26,    61,    21,    62,    -1,    26,    -1,    26,    54,    85,
      -1,    45,    89,    -1,    96,    -1,     4,    89,     5,    86,
      87,    -1,    59,    86,    60,    -1,     3,    86,    -1,    -1,
      13,    70,    26,    52,    -1,    13,    70,    26,    53,    89,
      52,    -1,    91,    -1,    96,    -1,    90,    -1,    94,    -1,
      99,    -1,   101,    -1,    93,    -1,   105,    -1,   103,    -1,
      95,    -1,    25,    -1,    24,    -1,    21,    -1,    22,    -1,
      23,    -1,    20,    -1,    89,    32,    89,    -1,    89,    37,
      89,    -1,    89,    33,    89,    -1,    89,    34,    89,    -1,
      89,    35,    89,    -1,    89,    36,    89,    -1,    89,    39,
      89,    -1,    89,    40,    89,    -1,    89,    41,    89,    -1,
      89,    42,    89,    -1,    89,    43,    89,    -1,    89,    44,
      89,    -1,    89,    48,    89,    -1,    89,    49,    89,    -1,
      89,    50,    89,    -1,    89,    61,    89,    62,    -1,    92,
      -1,    37,    89,    -1,    47,    89,    -1,    31,    89,    -1,
      57,    89,    58,    -1,    18,    70,    26,    89,    -1,    17,
      70,    26,    89,    -1,    85,    57,    97,    58,    -1,    26,
      -1,    46,    85,    57,    97,    58,    -1,    98,    -1,    -1,
      98,    51,    89,    -1,    89,    -1,    61,    97,    62,    -1,
      61,   100,    62,    -1,    98,    52,   100,    -1,    98,    52,
      98,    -1,    59,   102,    60,    -1,   102,    51,    89,    56,
      89,    -1,    89,    56,    89,    -1,    55,   105,    -1,    55,
      70,    -1,     9,    70,    26,    57,    70,    58,    52,    -1,
     106,    -1,   107,    -1,    59,    97,    60,    -1,    59,    70,
      26,    53,    89,    60,    -1,    59,    70,    26,    60,    -1,
      12,   109,    52,    -1,   111,    -1,   110,    -1,    89,    45,
      89,    -1,   107,    45,   106,    -1,    11,   113,    52,    -1,
      89,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   196,   196,   199,   201,   205,   211,   215,   216,   217,
     222,   223,   224,   225,   226,   227,   228,   229,   233,   238,
     239,   240,   244,   249,   264,   268,   269,   270,   274,   280,
     287,   296,   310,   324,   338,   339,   344,   349,   358,   363,
     370,   375,   380,   385,   406,   409,   415,   416,   417,   419,
     424,   425,   430,   431,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   448,   450,   452,   454,   456,   458,
     463,   467,   469,   471,   473,   475,   477,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   501,   503,   505,
     507,   511,   513,   518,   532,   536,   553,   554,   558,   562,
     571,   572,   577,   578,   582,   595,   602,   613,   614,   620,
     625,   626,   631,   645,   651,   669,   672,   673,   678,   686,
     691,   695
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ELSE", "IF", "THEN", "TYPE", "RANDOM",
  "FIXED", "ORIGIN", "DISTINCT", "QUERY", "OBS", "PARAM", "LIST", "MAP",
  "DISTRIBUTION", "EXISTS_", "FORALL_", "FOR", "NULLITY", "INT_LITERAL",
  "DOUBLE_LITERAL", "BOOLEAN_LITERAL", "CHAR_LITERAL", "STRING_LITERAL",
  "ID", "PARFACTOR", "FACTOR", "ERROR", "ELSEIF", "AT_", "PLUS_", "MULT_",
  "DIV_", "MOD_", "POWER_", "MINUS_", "LST", "LT_", "GT_", "LEQ_", "GEQ_",
  "EQEQ_", "NEQ_", "EQ_", "DISTRIB", "NOT_", "AND_", "OR_",
  "DOUBLERIGHTARROW", "COMMA", "SEMI", "COLON", "DOT", "NUMSIGN",
  "RIGHTARROW", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "$accept", "program", "opt_statement_lst", "statement_lst",
  "statement", "declaration_stmt", "type_decl", "type", "name_type",
  "list_type", "map_type", "opt_parenthesized_type_var_lst", "var_decl",
  "type_var_lst", "fixed_func_decl", "rand_func_decl", "number_stmt",
  "opt_parenthesized_origin_var_list", "origin_var_list",
  "distribution_decl", "distinct_decl", "id_or_subid_list", "class_name",
  "dependency_statement_body", "elseif_list", "parameter_decl",
  "expression", "literal", "operation_expr", "unary_operation_expr",
  "quantified_formula", "function_call", "symbol_expr",
  "distribution_expr", "opt_expression_list", "expression_list",
  "list_construct_expression", "semi_colon_separated_expression_list",
  "map_construct_expression", "expression_pair_list", "number_expr",
  "origin_func_decl", "set_expr", "explicit_set", "implicit_set",
  "evidence_stmt", "evidence", "value_evidence", "symbol_evidence",
  "query_stmt", "query", 0
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
     315,   316,   317
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    67,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    70,
      70,    70,    71,    72,    73,    74,    74,    74,    75,    76,
      76,    77,    78,    79,    80,    80,    81,    81,    82,    83,
      84,    84,    84,    84,    85,    85,    86,    86,    86,    86,
      87,    87,    88,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    90,    90,    90,    90,    90,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      92,    93,    93,    94,    95,    96,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   102,   102,   103,   103,   104,
     105,   105,   106,   107,   107,   108,   109,   109,   110,   111,
     112,   113
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     4,     6,     0,     2,     3,     2,     3,
       1,     7,     6,     5,     3,     0,     5,     3,     8,     3,
       2,     5,     3,     6,     1,     3,     2,     1,     5,     3,
       2,     0,     4,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     1,     2,     2,     2,
       3,     4,     4,     4,     1,     5,     1,     0,     3,     1,
       3,     3,     3,     3,     3,     5,     3,     2,     2,     7,
       1,     1,     3,     6,     4,     3,     1,     1,     3,     3,
       3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     4,     6,     7,    10,    11,    12,    14,
      17,    15,    16,    13,     8,     9,     0,     0,     0,    22,
       0,    19,    20,    21,     0,     0,     0,     0,     0,     0,
      69,    66,    67,    68,    65,    64,    94,     0,     0,     0,
       0,     0,     0,    97,    97,     0,   121,    56,    54,    86,
      60,    57,    63,    55,    58,    59,    62,    61,   110,   111,
       0,     0,   111,     0,   117,   116,     0,     0,    35,     1,
       5,    18,     0,     0,    25,    25,     0,    40,     0,    39,
       0,     0,     0,    89,    87,    44,     0,    88,    97,   108,
     107,     0,    94,     0,    99,     0,    96,     0,    99,     0,
      96,     0,    97,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
       0,     0,   115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,    45,    97,    90,
       0,     0,   112,     0,     0,   104,   100,     0,   101,     0,
      70,    72,    73,    74,    75,    71,    76,    77,    78,    79,
      80,    81,    82,    83,    84,     0,   118,    97,   119,    52,
       0,     0,     0,     0,     0,     0,     0,     0,    47,    23,
       0,    26,     0,    30,     0,     0,     0,     0,     0,     0,
      92,    91,     0,     0,   114,   106,    98,     0,   103,   102,
      93,    85,     0,    97,     0,     0,    34,     0,    46,     0,
      33,     0,    28,     0,    27,    32,     0,     0,    41,     0,
      95,     0,     0,    53,     0,    37,     0,     0,    49,    24,
      29,    31,   109,    43,   113,   105,     0,     0,    51,    38,
      36,     0,    48,    50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    15,    16,   103,    31,    32,
      33,   140,   193,   194,    17,    18,    19,   136,   183,    20,
      21,    37,    55,   187,   252,    22,   108,    57,    58,    59,
      60,    61,    62,    63,   105,   106,    64,   111,    65,   107,
      66,    23,    67,    68,    69,    24,    73,    74,    75,    25,
      70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -115
static const yytype_int16 yypact[] =
{
      27,    32,    -9,    -9,    -9,    37,   226,   226,    -9,    49,
      37,    45,  -115,    27,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,    25,    39,    40,  -115,
      54,  -115,  -115,  -115,    55,    57,    58,   -43,    -9,    -9,
    -115,  -115,  -115,  -115,  -115,  -115,     0,   226,   226,    59,
     226,     5,   226,   181,   226,    29,   476,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
      35,   287,    43,    38,  -115,  -115,    63,    46,    41,  -115,
    -115,  -115,    69,    -9,    42,    42,    44,    36,    74,  -115,
      76,    77,    59,   476,    33,    50,    48,   522,   181,  -115,
    -115,   310,    -1,    99,   340,    66,    78,   -28,   476,    68,
      22,    70,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,  -115,
     226,    72,  -115,    18,    59,   107,     6,    94,    84,     1,
       6,    91,    -9,   117,    81,   226,   226,  -115,   226,  -115,
     -49,   226,  -115,   226,   226,  -115,  -115,   226,  -115,    85,
      33,    83,    83,    83,    83,    33,   535,   535,   535,   535,
     535,   535,   522,   522,   499,   256,   476,   226,  -115,  -115,
     226,    89,   105,   -30,   226,   226,     6,   101,  -115,  -115,
      -9,  -115,   125,  -115,     4,   102,   226,   110,   108,   148,
     476,   476,   118,   226,  -115,   476,   476,   370,    22,  -115,
    -115,  -115,   400,   226,   149,   151,  -115,   123,   476,   120,
    -115,   141,  -115,    -9,  -115,  -115,   423,   130,  -115,   121,
    -115,   446,   226,  -115,   127,  -115,   142,     6,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,   476,   134,   162,   186,  -115,
    -115,     6,  -115,  -115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,  -115,  -115,   178,  -115,  -115,    10,    19,  -115,
    -115,   109,   -31,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,   -42,  -110,  -115,  -115,    -6,  -115,  -115,  -115,
    -115,  -115,  -115,  -114,   -52,   -51,  -115,    51,  -115,  -115,
    -115,  -115,   158,    62,   203,  -115,  -115,  -115,  -115,  -115,
    -115
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -45
static const yytype_int16 yytable[] =
{
      56,    71,   109,   110,   203,    27,    28,    96,    88,    89,
     184,   204,    30,    34,    35,    27,    28,    29,    76,    27,
      28,   215,   188,   154,    36,   -22,   188,    29,   216,    78,
     195,    29,   155,     1,     2,     3,     4,     5,     6,     7,
       8,    93,    94,     9,    97,    79,   101,   104,    90,    91,
     147,   185,    49,    92,    92,   223,   -44,   -44,    26,   191,
     159,    99,   224,    29,    98,   186,   114,   115,   116,   117,
     179,   180,   188,   153,   157,    77,   219,    81,    82,    83,
      84,    85,    10,    86,    87,    95,   112,   129,   131,   133,
     132,   134,   181,   138,   128,   137,   202,   143,   135,   139,
     144,   142,   145,   146,    92,   148,   208,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   188,   176,   150,   152,   248,   237,   153,
     156,   177,   158,   182,   189,   190,   196,   188,   198,   200,
     201,   253,   199,   210,   128,   205,   213,   206,   207,   192,
     214,   222,   197,   220,   225,   113,   114,   115,   116,   117,
     118,   234,   119,   120,   121,   122,   123,   124,   227,   229,
     228,   125,   126,   127,   212,   235,   230,   236,   217,   218,
     238,   239,   242,   243,   128,   246,   249,   247,   250,   251,
     226,    80,   240,   178,   141,    27,    28,   231,    38,    39,
     221,    40,    41,    42,    43,    44,    45,   102,   209,   100,
      72,     0,    47,     0,     0,     0,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,   245,    49,    50,     0,
       0,     0,     0,   192,     0,     0,    51,     0,    52,     0,
      53,     0,    54,    38,    39,     0,    40,    41,    42,    43,
      44,    45,    46,     0,     0,     0,     0,    47,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,    51,     0,    52,     0,    53,     0,    54,   113,   114,
     115,   116,   117,   118,     0,   119,   120,   121,   122,   123,
     124,     0,     0,     0,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   211,   113,
     114,   115,   116,   117,   118,     0,   119,   120,   121,   122,
     123,   124,   130,     0,     0,   125,   126,   127,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   128,   119,
     120,   121,   122,   123,   124,     0,     0,     0,   125,   126,
     127,     0,     0,     0,     0,     0,     0,     0,   149,     0,
       0,   128,   113,   114,   115,   116,   117,   118,     0,   119,
     120,   121,   122,   123,   124,     0,     0,     0,   125,   126,
     127,     0,     0,     0,     0,     0,   151,     0,     0,     0,
       0,   128,   113,   114,   115,   116,   117,   118,     0,   119,
     120,   121,   122,   123,   124,     0,     0,     0,   125,   126,
     127,     0,     0,     0,     0,     0,   232,     0,     0,     0,
       0,   128,   113,   114,   115,   116,   117,   118,     0,   119,
     120,   121,   122,   123,   124,     0,     0,     0,   125,   126,
     127,     0,   233,     0,     0,   113,   114,   115,   116,   117,
     118,   128,   119,   120,   121,   122,   123,   124,     0,     0,
       0,   125,   126,   127,     0,   241,     0,     0,   113,   114,
     115,   116,   117,   118,   128,   119,   120,   121,   122,   123,
     124,     0,     0,     0,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   244,   128,   113,   114,
     115,   116,   117,   118,     0,   119,   120,   121,   122,   123,
     124,     0,     0,     0,   125,   126,   127,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   128,   119,   120,
     121,   122,   123,   124,     0,     0,     0,   125,   126,     0,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
     128,   119,   120,   121,   122,   123,   124,   113,   114,   115,
     116,   117,   118,     0,   -45,   -45,   -45,   -45,   -45,   -45,
       0,     0,     0,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128
};

static const yytype_int16 yycheck[] =
{
       6,     7,    54,    54,    53,    14,    15,    49,    51,    52,
       4,    60,     2,     3,     4,    14,    15,    26,     8,    14,
      15,    51,   136,    51,     5,    26,   140,    26,    58,    10,
     140,    26,    60,     6,     7,     8,     9,    10,    11,    12,
      13,    47,    48,    16,    50,     0,    52,    53,    38,    39,
      92,    45,    46,    54,    54,    51,    57,    57,    26,    58,
     112,    51,    58,    26,    59,    59,    33,    34,    35,    36,
      52,    53,   186,    51,    52,    26,   186,    52,    39,    39,
      26,    26,    55,    26,    26,    26,    57,    52,    45,    26,
      52,    45,   134,    83,    61,    26,   148,    61,    57,    57,
      26,    57,    26,    26,    54,    57,   157,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   237,   130,    26,    60,   237,     5,    51,
      62,    59,    62,    26,    40,    51,    45,   251,    21,   145,
     146,   251,    61,    58,    61,   151,    57,   153,   154,   139,
      45,    26,   142,    52,    52,    32,    33,    34,    35,    36,
      37,   213,    39,    40,    41,    42,    43,    44,    58,    21,
      62,    48,    49,    50,   180,    26,    58,    26,   184,   185,
      60,    40,    52,    62,    61,    58,    52,    45,    26,     3,
     196,    13,   223,   131,    85,    14,    15,   203,    17,    18,
     190,    20,    21,    22,    23,    24,    25,    26,   157,    51,
       7,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   232,    46,    47,    -1,
      -1,    -1,    -1,   223,    -1,    -1,    55,    -1,    57,    -1,
      59,    -1,    61,    17,    18,    -1,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    57,    -1,    59,    -1,    61,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    32,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    48,    49,    50,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    61,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    61,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    61,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    61,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    48,    49,
      50,    -1,    52,    -1,    -1,    32,    33,    34,    35,    36,
      37,    61,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    -1,    -1,    32,    33,
      34,    35,    36,    37,    61,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    37,    61,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    48,    49,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      61,    39,    40,    41,    42,    43,    44,    32,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,     9,    10,    11,    12,    13,    16,
      55,    64,    65,    66,    67,    68,    69,    77,    78,    79,
      82,    83,    88,   104,   108,   112,    26,    14,    15,    26,
      70,    71,    72,    73,    70,    70,    71,    84,    17,    18,
      20,    21,    22,    23,    24,    25,    26,    31,    37,    46,
      47,    55,    57,    59,    61,    85,    89,    90,    91,    92,
      93,    94,    95,    96,    99,   101,   103,   105,   106,   107,
     113,    89,   107,   109,   110,   111,    70,    26,    71,     0,
      67,    52,    39,    39,    26,    26,    26,    26,    51,    52,
      70,    70,    54,    89,    89,    26,    85,    89,    59,    70,
     105,    89,    26,    70,    89,    97,    98,   102,    89,    97,
      98,   100,    57,    32,    33,    34,    35,    36,    37,    39,
      40,    41,    42,    43,    44,    48,    49,    50,    61,    52,
      45,    45,    52,    26,    45,    57,    80,    26,    70,    57,
      74,    74,    57,    61,    26,    26,    26,    85,    57,    58,
      26,    56,    60,    51,    51,    60,    62,    52,    62,    97,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    59,   106,    52,
      53,    85,    26,    81,     4,    45,    59,    86,    96,    40,
      51,    58,    70,    75,    76,    86,    45,    70,    21,    61,
      89,    89,    97,    53,    60,    89,    89,    89,    98,   100,
      58,    62,    89,    57,    45,    51,    58,    89,    89,    86,
      52,    70,    26,    51,    58,    52,    89,    58,    62,    21,
      58,    89,    56,    52,    97,    26,    26,     5,    60,    40,
      75,    52,    52,    62,    60,    89,    58,    45,    86,    52,
      26,     3,    87,    86
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
# if YYLTYPE_IS_TRIVIAL
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
        case 5:

/* Line 1455 of yacc.c  */
#line 206 "blog.yacc"
    {
    if((yyvsp[(2) - (2)].stmt) != NULL){
      blog->add((yyvsp[(2) - (2)].stmt));
    }
  }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 211 "blog.yacc"
    { blog->add((yyvsp[(1) - (1)].stmt)); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 215 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 216 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 217 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 222 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 223 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].funcdec); }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 224 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].funcdec); }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 225 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].origdec); }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 226 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(1) - (1)].numstdec); }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 227 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].distdec); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 228 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 229 "blog.yacc"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 234 "blog.yacc"
    { (yyval.stmt) = new TypDecl(curr_line, curr_col, Symbol((yyvsp[(2) - (3)].sval)->getValue())); }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 238 "blog.yacc"
    { (yyval.typ) = (yyvsp[(1) - (1)].typ); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 239 "blog.yacc"
    { (yyval.typ) = (yyvsp[(1) - (1)].typ); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 240 "blog.yacc"
    { (yyval.typ) = (yyvsp[(1) - (1)].typ); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 244 "blog.yacc"
    { (yyval.typ) = new Ty(curr_line, curr_col, Symbol((yyvsp[(1) - (1)].sval)->getValue())); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 249 "blog.yacc"
    { (yyval.typ) = new Ty(curr_line, curr_col, Symbol((yyvsp[(3) - (4)].sval)->getValue())); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 264 "blog.yacc"
    { (yyval.typ) = (yyvsp[(3) - (6)].typ); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 268 "blog.yacc"
    { (yyval.varlist) = NULL; }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 269 "blog.yacc"
    {(yyval.varlist) = NULL; }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 270 "blog.yacc"
    { (yyval.varlist) = (yyvsp[(2) - (3)].varlist); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 274 "blog.yacc"
    { 
    (yyval.vardec) = new VarDecl(curr_line, curr_col, *(yyvsp[(1) - (2)].typ), Symbol((yyvsp[(2) - (2)].sval)->getValue())); 
  }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 280 "blog.yacc"
    { 
      (yyval.varlist) = (yyvsp[(1) - (3)].varlist); 
      (yyval.varlist)->push_back(*(yyvsp[(3) - (3)].vardec));
      delete((yyvsp[(3) - (3)].vardec));
      //$$ = $1; 
      //$$->add((Expr*)(new VarDecl(curr_line, curr_col, *$3, Symbol($4->getValue())))); 
    }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 287 "blog.yacc"
    { 
      (yyval.varlist) = new vector<VarDecl>();
      (yyval.varlist)->push_back(*(yyvsp[(1) - (1)].vardec));
      delete((yyvsp[(1) - (1)].vardec));
      //$$ = new VarDecl(curr_line, curr_col, *$1, Symbol($2->getValue())); 
    }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 297 "blog.yacc"
    { 
      (yyval.funcdec) = new FuncDecl(curr_line, curr_col, false, *((yyvsp[(2) - (7)].typ)), Symbol((yyvsp[(3) - (7)].sval)->getValue()), (yyvsp[(6) - (7)].exp));
      if((yyvsp[(4) - (7)].varlist) != NULL){
        for(size_t i = 0; i < (yyvsp[(4) - (7)].varlist)->size(); i++){
          (yyval.funcdec)->addArg((*(yyvsp[(4) - (7)].varlist))[i]);
        }
        delete((yyvsp[(4) - (7)].varlist));
      }
      //if ($4 != NULL) $$->addArg(*$4);
    }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 311 "blog.yacc"
    { 
      (yyval.funcdec) = new FuncDecl(curr_line, curr_col, true, *((yyvsp[(2) - (6)].typ)), Symbol((yyvsp[(3) - (6)].sval)->getValue()), (yyvsp[(5) - (6)].exp));
      if((yyvsp[(4) - (6)].varlist) != NULL){
        for(size_t i = 0; i < (yyvsp[(4) - (6)].varlist)->size(); i++){
          (yyval.funcdec)->addArg((*(yyvsp[(4) - (6)].varlist))[i]);
        }
        delete((yyvsp[(4) - (6)].varlist));
      }
      //if ($4 != NULL) $$->addArg(*$4);
    }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 325 "blog.yacc"
    {
      (yyval.numstdec) = new NumStDecl(curr_line, curr_col, (yyvsp[(2) - (5)].typ)->getTyp(), (yyvsp[(4) - (5)].exp));
      if((yyvsp[(3) - (5)].varlst) != NULL){
        for(size_t i = 0; i < (yyvsp[(3) - (5)].varlst)->size(); i++){
          (yyval.numstdec)->add(get<0>((*(yyvsp[(3) - (5)].varlst))[i]), get<1>((*(yyvsp[(3) - (5)].varlst))[i]));
        }
        delete((yyvsp[(3) - (5)].varlst));
      }
      //$$->add(Symbol($4->getValue()), Symbol($6->getValue()));
    }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 338 "blog.yacc"
    {(yyval.varlst) = (yyvsp[(2) - (3)].varlst); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 339 "blog.yacc"
    {(yyval.varlst) = NULL; }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 345 "blog.yacc"
    {
    (yyval.varlst) = (yyvsp[(1) - (5)].varlst);
    (yyval.varlst)->push_back(make_tuple(Symbol((yyvsp[(3) - (5)].sval)->getValue()), Symbol((yyvsp[(5) - (5)].sval)->getValue())));
  }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 350 "blog.yacc"
    { 
    (yyval.varlst) = new vector<tuple<Symbol, Symbol>>();
    (yyval.varlst)->push_back(make_tuple(Symbol((yyvsp[(1) - (3)].sval)->getValue()), Symbol((yyvsp[(3) - (3)].sval)->getValue())));
  }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 359 "blog.yacc"
    { }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 364 "blog.yacc"
    {
      (yyval.distdec) = (yyvsp[(2) - (3)].distdec);
    }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 371 "blog.yacc"
    {
        (yyval.distdec) = new DistinctDecl(curr_line, curr_col, (yyvsp[(1) - (2)].typ)->getTyp());
        (yyval.distdec)->add(Symbol((yyvsp[(2) - (2)].sval)->getValue()), 1);
      }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 376 "blog.yacc"
    {
        (yyval.distdec) = new DistinctDecl(curr_line, curr_col, (yyvsp[(1) - (5)].typ)->getTyp());
        (yyval.distdec)->add(Symbol((yyvsp[(2) - (5)].sval)->getValue()), (yyvsp[(4) - (5)].ival)->getValue());
      }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 381 "blog.yacc"
    { 
        (yyval.distdec) = (yyvsp[(1) - (3)].distdec);
        (yyval.distdec)->add(Symbol((yyvsp[(3) - (3)].sval)->getValue()), 1);
      }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 386 "blog.yacc"
    { 
        (yyval.distdec) = (yyvsp[(1) - (6)].distdec);
        (yyval.distdec)->add(Symbol((yyvsp[(3) - (6)].sval)->getValue()), (yyvsp[(5) - (6)].ival)->getValue());
      }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 406 "blog.yacc"
    { 
      (yyval.sval) = new BLOGSymbol<string>(curr_line, curr_col, (yyvsp[(1) - (1)].sval)->getValue());
    }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 409 "blog.yacc"
    {
      (yyval.sval) = new BLOGSymbol<string>(curr_line, curr_col, (yyvsp[(1) - (3)].sval)->getValue() + "." + (yyvsp[(3) - (3)].sval)->getValue());
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 415 "blog.yacc"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 416 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 418 "blog.yacc"
    { (yyval.exp) = new IfExpr(curr_line, curr_col, (yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].exp), (yyvsp[(5) - (5)].exp)); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 420 "blog.yacc"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 424 "blog.yacc"
    {(yyval.exp) = (yyvsp[(2) - (2)].exp); }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 425 "blog.yacc"
    {(yyval.exp) = NULL; }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 430 "blog.yacc"
    { }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 431 "blog.yacc"
    { }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 435 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 436 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 437 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 438 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 439 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 440 "blog.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].mapexp);}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 441 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 442 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].setexp); }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 443 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].numref); }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 444 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 449 "blog.yacc"
    {(yyval.exp) = new StringLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].sval)->getValue()); }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 451 "blog.yacc"
    {string charstr(1, (yyvsp[(1) - (1)].chrval)->getValue()); (yyval.exp) = new StringLiteral(curr_line, curr_col, charstr); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 453 "blog.yacc"
    {(yyval.exp) = new IntLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].ival)->getValue()); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 455 "blog.yacc"
    {(yyval.exp) = new DoubleLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].dblval)->getValue()); }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 457 "blog.yacc"
    {(yyval.exp) = new BoolLiteral(curr_line, curr_col, (yyvsp[(1) - (1)].boolval)->getValue()); }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 459 "blog.yacc"
    {(yyval.exp) = new NullLiteral(curr_line, curr_col); }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 464 "blog.yacc"
    { 
      (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::PLUS, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));   
    }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 468 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::MINUS, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 470 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::MUL, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 472 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::DIV, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 474 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::MOD, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 476 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::POWER, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 478 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::LT, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 480 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::GT, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 482 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::LE, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 484 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::GE, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 486 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::EQ, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 488 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::NEQ, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 490 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::AND, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 492 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::OR, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 494 "blog.yacc"
    { (yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::IMPLY, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 496 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].exp)); }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 497 "blog.yacc"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 502 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, new IntLiteral(curr_line, curr_col, 0), (yyvsp[(2) - (2)].exp)); }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 504 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::NOT, NULL, (yyvsp[(2) - (2)].exp)); }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 506 "blog.yacc"
    {(yyval.exp) = new OpExpr(curr_line, curr_col, AbsynConstant::AT, NULL, (yyvsp[(2) - (2)].exp)); }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 507 "blog.yacc"
    {(yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 512 "blog.yacc"
    {(yyval.exp) = new QuantExpr(curr_line, curr_col, AbsynConstant::FORALL, *(new VarDecl(curr_line, curr_col, *(yyvsp[(2) - (4)].typ), Symbol((yyvsp[(3) - (4)].sval)->getValue()))), (yyvsp[(4) - (4)].exp)); }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 514 "blog.yacc"
    {(yyval.exp) = new QuantExpr(curr_line, curr_col, AbsynConstant::EXISTS, *(new VarDecl(curr_line, curr_col, *(yyvsp[(2) - (4)].typ), Symbol((yyvsp[(3) - (4)].sval)->getValue()))), (yyvsp[(4) - (4)].exp)); }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 519 "blog.yacc"
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

  case 94:

/* Line 1455 of yacc.c  */
#line 532 "blog.yacc"
    { (yyval.exp) = new VarRef(curr_line, curr_col, Symbol((yyvsp[(1) - (1)].sval)->getValue())); }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 537 "blog.yacc"
    {
      (yyval.exp) = new DistrExpr(curr_line, curr_col, Symbol((yyvsp[(2) - (5)].sval)->getValue()));
      if((yyvsp[(4) - (5)].explst) != NULL){
        for(size_t i = 0; i < (yyvsp[(4) - (5)].explst)->size(); i++){
          (yyval.exp)->add((*(yyvsp[(4) - (5)].explst))[i]);
        }
        delete((yyvsp[(4) - (5)].explst));
      }
      //$$->add($4);
      //for(size_t i = 0; i < $4->size(); i++){
      //  $$->add($4->get(i));
      //} 
    }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 553 "blog.yacc"
    {(yyval.explst) = (yyvsp[(1) - (1)].explst);}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 554 "blog.yacc"
    {(yyval.explst) = NULL; }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 559 "blog.yacc"
    { (yyval.explst) = (yyvsp[(1) - (3)].explst);
      (yyval.explst)->push_back((yyvsp[(3) - (3)].exp));
    }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 563 "blog.yacc"
    { 
      (yyval.explst) = new vector<Expr*>();
      (yyval.explst)->push_back((yyvsp[(1) - (1)].exp));
    }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 571 "blog.yacc"
    { }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 572 "blog.yacc"
    { }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 577 "blog.yacc"
    { }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 578 "blog.yacc"
    { }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 582 "blog.yacc"
    { 
    //$$ = $2; 
    (yyval.mapexp) = new MapExpr(curr_line, curr_col);
    for (size_t i = 0; i < (yyvsp[(2) - (3)].exptuplst)->size(); i++){
      (yyval.mapexp)->addMap(get<0>((*(yyvsp[(2) - (3)].exptuplst))[i]), get<1>((*(yyvsp[(2) - (3)].exptuplst))[i]));
    }
    delete((yyvsp[(2) - (3)].exptuplst));
    
  }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 596 "blog.yacc"
    { 
      (yyval.exptuplst) = (yyvsp[(1) - (5)].exptuplst);
      (yyval.exptuplst)->push_back(make_tuple((yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].exp)));
      //$$ = $1;
      //$$->addMap($3, $5);
    }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 603 "blog.yacc"
    { 
      (yyval.exptuplst) = new vector<tuple<Expr*, Expr*>>();
      (yyval.exptuplst)->push_back(make_tuple((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)));
      //$$ = new MapExpr(curr_line, curr_col);
      //$$->addMap($1, $3);
    }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 613 "blog.yacc"
    {(yyval.numref) = new NumStRef(curr_line, curr_col, (Expr*)(yyvsp[(2) - (2)].setexp)); }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 614 "blog.yacc"
    { 
      VarDecl* var = new VarDecl(curr_line, curr_col, *(yyvsp[(2) - (2)].typ), Symbol("a"));
      (yyval.numref) = new NumStRef(curr_line, curr_col, new CondSet(curr_line, curr_col, *var, new BoolLiteral(curr_line, curr_col, true)));
  }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 621 "blog.yacc"
    { (yyval.origdec) = new OriginDecl(curr_line, curr_col, (yyvsp[(2) - (7)].typ)->getTyp(), Symbol((yyvsp[(3) - (7)].sval)->getValue()), (yyvsp[(5) - (7)].typ)->getTyp());  }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 625 "blog.yacc"
    {(yyval.setexp) = (yyvsp[(1) - (1)].setexp); }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 626 "blog.yacc"
    {(yyval.setexp) = (yyvsp[(1) - (1)].setexp); }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 632 "blog.yacc"
    {
      (yyval.setexp) = new ListSet(curr_line, curr_col);
      for(size_t i = 0; i < (yyvsp[(2) - (3)].explst)->size(); i++){
        (yyval.setexp)->add((*(yyvsp[(2) - (3)].explst))[i]);
      }
      delete((yyvsp[(2) - (3)].explst));
      //$$ = new SetExpr(curr_line, curr_col); 
      //$$->add($2);
    }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 646 "blog.yacc"
    { 
      (yyval.setexp) = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *(yyvsp[(2) - (6)].typ), Symbol((yyvsp[(3) - (6)].sval)->getValue())), (yyvsp[(5) - (6)].exp));
      //$$ = new CondSet(curr_line, curr_col, NULL);
      //$$->add($5);
    }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 652 "blog.yacc"
    { 
      (yyval.setexp) = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *(yyvsp[(2) - (4)].typ), Symbol((yyvsp[(3) - (4)].sval)->getValue())));
    }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 669 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(2) - (3)].stmt); }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 672 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 673 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 679 "blog.yacc"
    {
    (yyval.stmt) = new Evidence(curr_line, curr_col, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); 
  }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 687 "blog.yacc"
    { (yyval.stmt) = new Evidence(curr_line, curr_col, (yyvsp[(1) - (3)].setexp), (yyvsp[(3) - (3)].setexp)); }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 691 "blog.yacc"
    {(yyval.stmt) = (yyvsp[(2) - (3)].stmt); }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 695 "blog.yacc"
    { (yyval.stmt) = new Query(curr_line, curr_col, (yyvsp[(1) - (1)].exp)); }
    break;



/* Line 1455 of yacc.c  */
#line 2826 "y.tab.c"
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



/* Line 1675 of yacc.c  */
#line 698 "blog.yacc"




void yyerror(const char *s) {
  cout << "Parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}
