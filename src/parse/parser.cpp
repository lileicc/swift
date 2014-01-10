#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130925

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "blog.yacc"
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

/* stuff from flex that bison needs to know about: */
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
  /* open a file handle to a particular file:*/
  FILE *myfile = fopen(inp, "r");
  /* make sure it is valid:*/
  if (!myfile) {
    cout << "I can't open input.in" << endl;
    exit(0);
    /*return -1;*/
  }
  /* set flex to read from it instead of defaulting to STDIN:*/
  yyin = myfile;
  /* parse through the input until there is no more:*/
  do {
    yyparse();
  } while (!feof(yyin));
  return blog;  
}
#line 77 "blog.yacc"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 148 "parser.cpp"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ELSE 257
#define IF 258
#define THEN 259
#define TYPE 260
#define RANDOM 261
#define FIXED 262
#define ORIGIN 263
#define DISTINCT 264
#define QUERY 265
#define OBS 266
#define PARAM 267
#define LIST 268
#define MAP 269
#define DISTRIBUTION 270
#define EXISTS_ 271
#define FORALL_ 272
#define FOR 273
#define NULLITY 274
#define INT_LITERAL 275
#define DOUBLE_LITERAL 276
#define BOOLEAN_LITERAL 277
#define CHAR_LITERAL 278
#define STRING_LITERAL 279
#define ID 280
#define PARFACTOR 281
#define FACTOR 282
#define ERROR 283
#define ELSEIF 284
#define AT_ 285
#define PLUS_ 286
#define MULT_ 287
#define DIV_ 288
#define MOD_ 289
#define POWER_ 290
#define MINUS_ 291
#define LST 292
#define LT_ 293
#define GT_ 294
#define LEQ_ 295
#define GEQ_ 296
#define EQEQ_ 297
#define NEQ_ 298
#define EQ_ 299
#define DISTRIB 300
#define NOT_ 301
#define AND_ 302
#define OR_ 303
#define DOUBLERIGHTARROW 304
#define COMMA 305
#define SEMI 306
#define COLON 307
#define DOT 308
#define NUMSIGN 309
#define RIGHTARROW 310
#define LPAREN 311
#define RPAREN 312
#define LBRACE 313
#define RBRACE 314
#define LBRACKET 315
#define RBRACKET 316
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,   52,   52,   53,   53,    1,    1,    1,    2,    2,
    2,    2,    2,    2,    2,    2,    3,   38,   38,   38,
   42,   40,   39,   51,   51,   41,   44,   44,   44,   49,
   43,   43,   10,   11,    8,   45,   45,   46,   46,    4,
   12,   48,   48,   48,   48,   47,   47,   50,   50,   29,
   29,   29,   29,   26,   26,    5,    5,   17,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   18,   18,   18,
   18,   18,   18,   19,   19,   19,   19,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,   19,   19,   19,
   20,   20,   20,   20,   21,   21,   23,   25,   22,   35,
   35,   36,   36,   24,   24,   34,   34,   28,   37,   37,
   27,   27,    9,   30,   30,   31,   32,   32,   33,   33,
    6,   13,   13,   14,   15,    7,   16,
};
static const short yylen[] = {                            2,
    1,    0,    1,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    3,    1,    1,    1,
    1,    4,    2,    2,    3,    6,    0,    2,    3,    2,
    3,    1,    7,    6,    5,    3,    0,    5,    3,    8,
    3,    2,    5,    3,    6,    1,    4,    1,    3,    2,
    1,    5,    3,    2,    0,    4,    6,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    4,    1,
    2,    2,    2,    3,    4,    4,    4,    1,    5,    1,
    0,    3,    1,    3,    3,    3,    3,    3,    5,    3,
    2,    2,    7,    1,    1,    3,    6,    4,    7,    5,
    3,    1,    1,    3,    3,    3,    1,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    5,    6,    9,   16,   15,    7,    8,   13,   12,
   10,   11,   14,    1,    0,    0,    0,    0,   21,    0,
   19,   20,   18,    0,    0,    0,    0,    0,    0,   73,
   70,   71,   72,   69,   68,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   60,   58,   90,   64,
   59,   61,   62,   67,   66,   63,   65,  114,  115,    0,
    0,  123,  122,    0,    0,    0,    0,    0,    4,   17,
    0,    0,    0,    0,    0,    0,    0,   41,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  111,  112,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  126,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  121,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   49,    0,   94,    0,  116,
    0,    0,  108,    0,  105,  104,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  125,   56,    0,    0,
    0,    0,    0,    0,    0,   51,    0,   22,    0,   28,
    0,    0,   32,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  118,  106,    0,   89,   97,
    0,    0,    0,    0,   36,    0,    0,    0,   35,    0,
   30,    0,   29,   34,    0,    0,   43,    0,   99,    0,
    0,   57,    0,   39,    0,    0,   53,   26,   31,   33,
  113,   45,    0,  117,    0,    0,    0,   40,   38,    0,
   52,   54,
};
static const short yydgoto[] = {                         11,
   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
   22,   23,   71,   72,   73,   55,  107,   57,   58,   59,
   60,   61,   62,   63,   64,  251,   65,   66,  187,   67,
   68,   69,    0,  108,  103,  104,  105,  106,    0,   31,
   32,   33,  192,  139,  135,  182,    0,   37,  193,   70,
    0,   24,   25,
};
static const short yysindex[] = {                       400,
 -263, -264, -264, -264, -241,  448,  448, -264, -222, -241,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  400, -233, -202, -196,    0, -203,
    0,    0,    0, -148, -146, -138, -179, -264, -264,    0,
    0,    0,    0,    0,    0, -205,  448,  448, -127,  448,
  180,  448,  403,  448, -150,  728,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -153,
 -142,    0,    0,  539, -128, -104, -120,  -96,    0,    0,
  -97, -264,  -95,  -95,  -89, -118,  -93,    0,  -82,  -73,
 -127,  728, -278, -205,  -88,  797,  403,    0,    0,  562,
 -205,  592, -123,  -61, -287,  -31,  728,  -65,  -63, -177,
    0,  448,  448,  448,  448,  448,  448,  448,  448,  448,
  448,  448,  448,  448,  448,  448,  448,  448,    0,  448,
  -59, -176, -127,  -24, -230,  -39,  -48,  -84, -230,  -41,
 -264,  -16,  -55,  448,  448,    0,  448,    0,  448,    0,
  448,  448,    0, -240,    0,    0,  448, -278,  -40,  -40,
  -40,  -40, -278, -121, -121, -121, -121, -121, -121,  797,
  797,  774,  508,  -45,  728,  448,    0,    0,  448,  -35,
  -13, -216,  448,  448, -230,    0,  -23,    0, -264,    0,
    8, -211,    0,  -14,  448,  -22,  -21,   18,  728,  728,
  -18,  728,  728,  622,  448,    0,    0, -177,    0,    0,
  652,  448,   16,   17,    0,  354,  728,  -15,    0,    7,
    0, -264,    0,    0,  675,   -4,    0,  -12,    0,  448,
  698,    0,   -9,    0,    6, -230,    0,    0,    0,    0,
    0,    0,  728,    0,    1,   26,   51,    0,    0, -230,
    0,    0,
};
static const short yyrindex[] = {                       309,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  310,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -85,    0,    0,    0,    0,
    0,    0,    3,    9,    0,   20,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  751,    0,    0, -215,    0,    0,
    0,    0, -159,   34,    0, -158,    0,    0,    0,    0,
    0, -155,  175,   27,    0, -251,    3,    0,    0,    0,
  478, -285,    0, -276,    0,    0, -282,    0,    0,   33,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   24,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -143,    0,    0,    0,   24,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  206,  -25,   25,
   75,  125,  237, -224,  -64,   41,   91,  141,  256,  287,
  306, -124,    0,    0,   36,    3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  268,  318,
    0, -274,  -69,    0,    0,    0,    0,   38,    0,    0,
    0,   24,    0,    0,    0,    0, -250,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -248,    0,    0,    0, -246,    0,    0,    0,
    0,    0,
};
static const short yygindex[] = {                         0,
  327,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   -6,    0,    0,    0,
    0, -114,    0,    0,    0,    0,    0,    0, -113,  305,
  227,  352,    0,  203,  -52,  -32,    0,   11,    0,    0,
    0,   95,    0,  283,    0,    0,    0,    0,  153,  -46,
    0,    0,    0,
};
#define YYTABLESIZE 1112
static const short yytable[] = {                         56,
   74,  109,   95,   27,   28,   92,   50,   92,  113,  114,
  115,  116,   30,   34,   35,   29,   26,  152,   76,  103,
  186,  110,  103,  103,  186,  194,  153,  183,  103,  103,
  110,  103,   80,  103,   80,  100,  127,  100,   29,  110,
   92,   93,   37,   96,  146,  100,  102,   92,   89,   90,
   92,   92,   92,   92,   92,   50,  109,   77,   92,   55,
   92,   99,   92,   50,   92,  109,  205,   55,  184,   49,
  186,  218,   80,  206,   80,  174,   83,   80,   80,   80,
   80,   80,  185,   37,   37,   80,  180,   80,  214,   80,
   81,   80,  137,  222,  201,  215,   82,   37,   27,   36,
  223,   93,   91,   93,   78,  158,  159,  160,  161,  162,
  163,  164,  165,  166,  167,  168,  169,  170,  171,  172,
  173,  186,  247,  175,  208,   87,   88,  151,  157,  178,
  179,   84,   88,   85,   88,  186,  252,  199,  200,   27,
   27,   86,  202,   93,  203,  204,   42,   42,  191,   93,
   93,  196,   94,   27,   93,  111,   93,  128,   93,  233,
   93,   44,   44,  129,  112,  113,  114,  115,  116,  117,
  131,   98,  211,   98,   88,  132,  216,  217,  133,   88,
   88,   88,  136,   27,   28,   88,  143,   88,  225,   88,
  150,   88,   81,  127,   81,   29,  142,  144,  231,  220,
   98,   98,   98,   98,   98,   98,  145,   98,   98,   98,
   98,   98,   98,   98,  134,  138,   98,   98,   98,   98,
   98,  141,  147,  243,   98,   48,   98,  190,   98,   98,
   98,   76,  191,   76,   81,  102,  102,   81,   81,   81,
   81,   81,  102,  151,  102,   81,  102,   81,  154,   81,
  155,   81,  156,  176,  188,  181,  189,  195,  197,  198,
   76,   76,   76,   76,   76,   76,  210,   76,   76,   76,
   76,   76,   76,   76,  127,  212,   76,   76,   76,   76,
   76,   77,  219,   77,   76,  213,   76,  221,   76,  226,
   76,  224,  228,  229,  227,  234,  235,   82,  237,   82,
  238,  241,  245,  242,  246,  249,  248,  250,    2,    3,
   77,   77,   77,   77,   77,   77,  101,   77,   77,   77,
   77,   77,   77,   77,  101,  127,   77,   77,   77,   77,
   77,   78,   27,   78,   77,  101,   77,   48,   77,   82,
   77,  124,   82,   82,   82,   82,   82,   83,  100,   83,
   82,   79,   82,  107,   82,   98,   82,  177,   75,  207,
   78,   78,   78,   78,   78,   78,  140,   78,   78,   78,
   78,   78,   78,   78,  239,    0,   78,   78,   78,   78,
   78,   79,    0,   79,   78,    0,   78,    0,   78,   83,
   78,    0,   83,   83,   83,   83,   83,   84,    0,   84,
   83,    0,   83,    0,   83,    0,   83,    0,    0,    0,
   79,   79,   79,   79,   79,   79,    0,   79,   79,   79,
   79,   79,   79,   79,    0,    0,   79,   79,   79,   79,
   79,   91,    0,   91,   79,    0,   79,    0,   79,   84,
   79,    0,   84,   84,   84,   84,   84,   27,   28,    0,
   84,    0,   84,    0,   84,    0,   84,    0,    0,   29,
   91,    0,   74,    0,   74,   91,    0,   91,   91,   91,
   91,   91,   91,   91,    0,    0,   91,   91,   91,   91,
   91,    0,    0,    0,   91,    0,   91,    0,   91,    0,
   91,   74,   97,   75,    0,   75,   74,    0,   74,   74,
   74,   74,   74,   74,   74,    0,    0,   74,   74,   74,
   74,   74,   85,    0,   85,   74,    0,   74,    0,   74,
    0,   74,   75,    0,   96,    0,   96,   75,    0,   75,
   75,   75,   75,   75,   75,   75,    0,    0,   75,   75,
   75,   75,   75,   86,    0,   86,   75,    0,   75,    0,
   75,    0,   75,    0,   85,    0,    0,   85,   85,   85,
   85,   85,   87,    0,   87,   85,   96,   85,    0,   85,
    0,   85,   96,   96,   95,    0,   95,   96,    0,   96,
    0,   96,    0,   96,    0,   86,    0,    0,   86,   86,
   86,   86,   86,    0,    0,    0,   86,    0,   86,    0,
   86,    0,   86,    0,   87,    0,    0,   87,   87,   87,
   87,   87,  236,    0,    0,   87,   95,   87,    0,   87,
    0,   87,   95,   95,    0,    0,    0,   95,    0,   95,
    0,   95,    0,   95,    0,    0,    0,    0,    0,  112,
  113,  114,  115,  116,  117,    0,  118,  119,  120,  121,
  122,  123,    0,    0,    0,  124,  125,  126,    0,    1,
    2,    3,    4,    5,    6,    7,    8,    0,  127,    9,
   27,   28,    0,   38,   39,    0,   40,   41,   42,   43,
   44,   45,  101,    0,    0,    0,    0,   47,    0,    0,
    0,    0,    0,   48,    0,    0,    0,    0,    0,    0,
    0,    0,   49,   50,    0,    0,    0,    0,   10,    0,
    0,   51,    0,   52,    0,   53,    0,   54,   38,   39,
    0,   40,   41,   42,   43,   44,   45,   46,    0,    0,
    0,    0,   47,    0,    0,    0,    0,    0,   48,    0,
    0,    0,    0,    0,    0,    0,    0,   49,   50,    0,
    0,    0,    0,    0,    0,    0,   51,   21,   52,    0,
   53,    0,   54,   98,   98,   98,   98,   98,   98,    0,
   98,   98,   98,   98,   98,   98,    0,    0,    0,   98,
   98,   98,   98,    0,    0,    0,    0,   98,   48,    0,
    0,   98,   98,  112,  113,  114,  115,  116,  117,    0,
  118,  119,  120,  121,  122,  123,    0,    0,    0,  124,
  125,  126,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  127,  209,  112,  113,  114,  115,  116,  117,
    0,  118,  119,  120,  121,  122,  123,  130,    0,    0,
  124,  125,  126,    0,    0,    0,    0,  112,  113,  114,
  115,  116,  117,  127,  118,  119,  120,  121,  122,  123,
    0,    0,    0,  124,  125,  126,    0,    0,    0,    0,
    0,    0,    0,  148,    0,    0,  127,  112,  113,  114,
  115,  116,  117,    0,  118,  119,  120,  121,  122,  123,
    0,    0,    0,  124,  125,  126,    0,    0,    0,    0,
    0,  149,    0,    0,    0,    0,  127,  112,  113,  114,
  115,  116,  117,    0,  118,  119,  120,  121,  122,  123,
    0,    0,    0,  124,  125,  126,    0,    0,    0,    0,
    0,  230,    0,    0,    0,    0,  127,  112,  113,  114,
  115,  116,  117,    0,  118,  119,  120,  121,  122,  123,
    0,    0,    0,  124,  125,  126,    0,  232,    0,    0,
  112,  113,  114,  115,  116,  117,  127,  118,  119,  120,
  121,  122,  123,    0,    0,    0,  124,  125,  126,    0,
  240,    0,    0,  112,  113,  114,  115,  116,  117,  127,
  118,  119,  120,  121,  122,  123,    0,    0,    0,  124,
  125,  126,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  244,  127,  112,  113,  114,  115,  116,  117,    0,
  118,  119,  120,  121,  122,  123,    0,    0,    0,  124,
  125,  126,    0,    0,    0,    0,  115,  115,  115,  115,
  115,  115,  127,  115,  115,  115,  115,  115,  115,    0,
    0,    0,  115,  115,  115,    0,    0,    0,    0,  112,
  113,  114,  115,  116,  117,  115,  118,  119,  120,  121,
  122,  123,    0,    0,    0,  124,  125,    0,    0,    0,
    0,    0,  112,  113,  114,  115,  116,  117,  127,  118,
  119,  120,  121,  122,  123,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  127,
};
static const short yycheck[] = {                          6,
    7,   54,   49,  268,  269,  257,  257,  259,  287,  288,
  289,  290,    2,    3,    4,  280,  280,  305,    8,  305,
  135,   54,  305,  306,  139,  139,  314,  258,  314,  312,
  305,  314,  257,  316,  259,  312,  315,  314,  280,  314,
   47,   48,  258,   50,   91,   52,   53,  299,   38,   39,
  302,  303,  304,  305,  306,  306,  305,  280,  310,  306,
  312,   51,  314,  314,  316,  314,  307,  314,  299,  300,
  185,  185,  306,  314,  299,  128,  280,  302,  303,  304,
  305,  306,  313,  299,  300,  310,  133,  312,  305,  314,
  293,  316,   82,  305,  147,  312,  293,  313,  258,    5,
  312,  257,  308,  259,   10,  112,  113,  114,  115,  116,
  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
  127,  236,  236,  130,  157,  305,  306,  305,  306,  306,
  307,  280,  257,  280,  259,  250,  250,  144,  145,  299,
  300,  280,  149,  299,  151,  152,  305,  306,  138,  305,
  306,  141,  280,  313,  310,  306,  312,  311,  314,  212,
  316,  305,  306,  306,  286,  287,  288,  289,  290,  291,
  299,  257,  179,  259,  299,  280,  183,  184,  299,  304,
  305,  306,  280,  268,  269,  310,  280,  312,  195,  314,
  314,  316,  257,  315,  259,  280,  315,  280,  205,  189,
  286,  287,  288,  289,  290,  291,  280,  293,  294,  295,
  296,  297,  298,  299,  311,  311,  302,  303,  304,  305,
  306,  311,  311,  230,  310,  311,  312,  312,  314,  315,
  316,  257,  222,  259,  299,  305,  306,  302,  303,  304,
  305,  306,  312,  305,  314,  310,  316,  312,  280,  314,
  316,  316,  316,  313,  294,  280,  305,  299,  275,  315,
  286,  287,  288,  289,  290,  291,  312,  293,  294,  295,
  296,  297,  298,  299,  315,  311,  302,  303,  304,  305,
  306,  257,  306,  259,  310,  299,  312,  280,  314,  312,
  316,  306,  275,  312,  316,  280,  280,  257,  314,  259,
  294,  306,  312,  316,  299,  280,  306,  257,    0,    0,
  286,  287,  288,  289,  290,  291,  314,  293,  294,  295,
  296,  297,  298,  299,  316,  306,  302,  303,  304,  305,
  306,  257,  299,  259,  310,  312,  312,  311,  314,  299,
  316,  306,  302,  303,  304,  305,  306,  257,  316,  259,
  310,   25,  312,  316,  314,   51,  316,  131,    7,  157,
  286,  287,  288,  289,  290,  291,   84,  293,  294,  295,
  296,  297,  298,  299,  222,   -1,  302,  303,  304,  305,
  306,  257,   -1,  259,  310,   -1,  312,   -1,  314,  299,
  316,   -1,  302,  303,  304,  305,  306,  257,   -1,  259,
  310,   -1,  312,   -1,  314,   -1,  316,   -1,   -1,   -1,
  286,  287,  288,  289,  290,  291,   -1,  293,  294,  295,
  296,  297,  298,  299,   -1,   -1,  302,  303,  304,  305,
  306,  257,   -1,  259,  310,   -1,  312,   -1,  314,  299,
  316,   -1,  302,  303,  304,  305,  306,  268,  269,   -1,
  310,   -1,  312,   -1,  314,   -1,  316,   -1,   -1,  280,
  286,   -1,  257,   -1,  259,  291,   -1,  293,  294,  295,
  296,  297,  298,  299,   -1,   -1,  302,  303,  304,  305,
  306,   -1,   -1,   -1,  310,   -1,  312,   -1,  314,   -1,
  316,  286,  313,  257,   -1,  259,  291,   -1,  293,  294,
  295,  296,  297,  298,  299,   -1,   -1,  302,  303,  304,
  305,  306,  257,   -1,  259,  310,   -1,  312,   -1,  314,
   -1,  316,  286,   -1,  257,   -1,  259,  291,   -1,  293,
  294,  295,  296,  297,  298,  299,   -1,   -1,  302,  303,
  304,  305,  306,  257,   -1,  259,  310,   -1,  312,   -1,
  314,   -1,  316,   -1,  299,   -1,   -1,  302,  303,  304,
  305,  306,  257,   -1,  259,  310,  299,  312,   -1,  314,
   -1,  316,  305,  306,  257,   -1,  259,  310,   -1,  312,
   -1,  314,   -1,  316,   -1,  299,   -1,   -1,  302,  303,
  304,  305,  306,   -1,   -1,   -1,  310,   -1,  312,   -1,
  314,   -1,  316,   -1,  299,   -1,   -1,  302,  303,  304,
  305,  306,  259,   -1,   -1,  310,  299,  312,   -1,  314,
   -1,  316,  305,  306,   -1,   -1,   -1,  310,   -1,  312,
   -1,  314,   -1,  316,   -1,   -1,   -1,   -1,   -1,  286,
  287,  288,  289,  290,  291,   -1,  293,  294,  295,  296,
  297,  298,   -1,   -1,   -1,  302,  303,  304,   -1,  260,
  261,  262,  263,  264,  265,  266,  267,   -1,  315,  270,
  268,  269,   -1,  271,  272,   -1,  274,  275,  276,  277,
  278,  279,  280,   -1,   -1,   -1,   -1,  285,   -1,   -1,
   -1,   -1,   -1,  291,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  300,  301,   -1,   -1,   -1,   -1,  309,   -1,
   -1,  309,   -1,  311,   -1,  313,   -1,  315,  271,  272,
   -1,  274,  275,  276,  277,  278,  279,  280,   -1,   -1,
   -1,   -1,  285,   -1,   -1,   -1,   -1,   -1,  291,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  300,  301,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  309,  280,  311,   -1,
  313,   -1,  315,  286,  287,  288,  289,  290,  291,   -1,
  293,  294,  295,  296,  297,  298,   -1,   -1,   -1,  302,
  303,  304,  305,   -1,   -1,   -1,   -1,  310,  311,   -1,
   -1,  314,  315,  286,  287,  288,  289,  290,  291,   -1,
  293,  294,  295,  296,  297,  298,   -1,   -1,   -1,  302,
  303,  304,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  315,  316,  286,  287,  288,  289,  290,  291,
   -1,  293,  294,  295,  296,  297,  298,  299,   -1,   -1,
  302,  303,  304,   -1,   -1,   -1,   -1,  286,  287,  288,
  289,  290,  291,  315,  293,  294,  295,  296,  297,  298,
   -1,   -1,   -1,  302,  303,  304,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  312,   -1,   -1,  315,  286,  287,  288,
  289,  290,  291,   -1,  293,  294,  295,  296,  297,  298,
   -1,   -1,   -1,  302,  303,  304,   -1,   -1,   -1,   -1,
   -1,  310,   -1,   -1,   -1,   -1,  315,  286,  287,  288,
  289,  290,  291,   -1,  293,  294,  295,  296,  297,  298,
   -1,   -1,   -1,  302,  303,  304,   -1,   -1,   -1,   -1,
   -1,  310,   -1,   -1,   -1,   -1,  315,  286,  287,  288,
  289,  290,  291,   -1,  293,  294,  295,  296,  297,  298,
   -1,   -1,   -1,  302,  303,  304,   -1,  306,   -1,   -1,
  286,  287,  288,  289,  290,  291,  315,  293,  294,  295,
  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,   -1,
  306,   -1,   -1,  286,  287,  288,  289,  290,  291,  315,
  293,  294,  295,  296,  297,  298,   -1,   -1,   -1,  302,
  303,  304,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  314,  315,  286,  287,  288,  289,  290,  291,   -1,
  293,  294,  295,  296,  297,  298,   -1,   -1,   -1,  302,
  303,  304,   -1,   -1,   -1,   -1,  286,  287,  288,  289,
  290,  291,  315,  293,  294,  295,  296,  297,  298,   -1,
   -1,   -1,  302,  303,  304,   -1,   -1,   -1,   -1,  286,
  287,  288,  289,  290,  291,  315,  293,  294,  295,  296,
  297,  298,   -1,   -1,   -1,  302,  303,   -1,   -1,   -1,
   -1,   -1,  286,  287,  288,  289,  290,  291,  315,  293,
  294,  295,  296,  297,  298,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  315,
};
#define YYFINAL 11
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 316
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ELSE","IF","THEN","TYPE",
"RANDOM","FIXED","ORIGIN","DISTINCT","QUERY","OBS","PARAM","LIST","MAP",
"DISTRIBUTION","EXISTS_","FORALL_","FOR","NULLITY","INT_LITERAL",
"DOUBLE_LITERAL","BOOLEAN_LITERAL","CHAR_LITERAL","STRING_LITERAL","ID",
"PARFACTOR","FACTOR","ERROR","ELSEIF","AT_","PLUS_","MULT_","DIV_","MOD_",
"POWER_","MINUS_","LST","LT_","GT_","LEQ_","GEQ_","EQEQ_","NEQ_","EQ_",
"DISTRIB","NOT_","AND_","OR_","DOUBLERIGHTARROW","COMMA","SEMI","COLON","DOT",
"NUMSIGN","RIGHTARROW","LPAREN","RPAREN","LBRACE","RBRACE","LBRACKET",
"RBRACKET",
};
static const char *yyrule[] = {
"$accept : program",
"program : opt_statement_lst",
"opt_statement_lst :",
"opt_statement_lst : statement_lst",
"statement_lst : statement_lst statement",
"statement_lst : statement",
"statement : declaration_stmt",
"statement : evidence_stmt",
"statement : query_stmt",
"declaration_stmt : type_decl",
"declaration_stmt : fixed_func_decl",
"declaration_stmt : rand_func_decl",
"declaration_stmt : origin_func_decl",
"declaration_stmt : number_stmt",
"declaration_stmt : distinct_decl",
"declaration_stmt : parameter_decl",
"declaration_stmt : distribution_decl",
"type_decl : TYPE ID SEMI",
"type : name_type",
"type : list_type",
"type : map_type",
"name_type : ID",
"list_type : LIST LT_ ID GT_",
"array_type : ID dims",
"dims : LBRACKET RBRACKET",
"dims : LBRACKET RBRACKET dims",
"map_type : MAP LT_ type COMMA type GT_",
"opt_parenthesized_type_var_lst :",
"opt_parenthesized_type_var_lst : LPAREN RPAREN",
"opt_parenthesized_type_var_lst : LPAREN type_var_lst RPAREN",
"var_decl : type ID",
"type_var_lst : type_var_lst COMMA var_decl",
"type_var_lst : var_decl",
"fixed_func_decl : FIXED type ID opt_parenthesized_type_var_lst EQ_ expression SEMI",
"rand_func_decl : RANDOM type ID opt_parenthesized_type_var_lst dependency_statement_body SEMI",
"number_stmt : NUMSIGN name_type opt_parenthesized_origin_var_list dependency_statement_body SEMI",
"opt_parenthesized_origin_var_list : LPAREN origin_var_list RPAREN",
"opt_parenthesized_origin_var_list :",
"origin_var_list : origin_var_list COMMA ID EQ_ ID",
"origin_var_list : ID EQ_ ID",
"distribution_decl : DISTRIBUTION ID EQ_ class_name LPAREN opt_expression_list RPAREN SEMI",
"distinct_decl : DISTINCT id_or_subid_list SEMI",
"id_or_subid_list : name_type ID",
"id_or_subid_list : name_type ID LBRACKET INT_LITERAL RBRACKET",
"id_or_subid_list : id_or_subid_list COMMA ID",
"id_or_subid_list : id_or_subid_list COMMA ID LBRACKET INT_LITERAL RBRACKET",
"id_or_subid : ID",
"id_or_subid : ID LBRACKET INT_LITERAL RBRACKET",
"class_name : ID",
"class_name : ID DOT class_name",
"dependency_statement_body : EQ_ expression",
"dependency_statement_body : distribution_expr",
"dependency_statement_body : IF expression THEN dependency_statement_body elseif_list",
"dependency_statement_body : LBRACE dependency_statement_body RBRACE",
"elseif_list : ELSE dependency_statement_body",
"elseif_list :",
"parameter_decl : PARAM type ID SEMI",
"parameter_decl : PARAM type ID COLON expression SEMI",
"expression : operation_expr",
"expression : distribution_expr",
"expression : literal",
"expression : function_call",
"expression : list_construct_expression",
"expression : map_construct_expression",
"expression : quantified_formula",
"expression : set_expr",
"expression : number_expr",
"expression : symbol_expr",
"literal : STRING_LITERAL",
"literal : CHAR_LITERAL",
"literal : INT_LITERAL",
"literal : DOUBLE_LITERAL",
"literal : BOOLEAN_LITERAL",
"literal : NULLITY",
"operation_expr : expression PLUS_ expression",
"operation_expr : expression MINUS_ expression",
"operation_expr : expression MULT_ expression",
"operation_expr : expression DIV_ expression",
"operation_expr : expression MOD_ expression",
"operation_expr : expression POWER_ expression",
"operation_expr : expression LT_ expression",
"operation_expr : expression GT_ expression",
"operation_expr : expression LEQ_ expression",
"operation_expr : expression GEQ_ expression",
"operation_expr : expression EQEQ_ expression",
"operation_expr : expression NEQ_ expression",
"operation_expr : expression AND_ expression",
"operation_expr : expression OR_ expression",
"operation_expr : expression DOUBLERIGHTARROW expression",
"operation_expr : expression LBRACKET expression RBRACKET",
"operation_expr : unary_operation_expr",
"unary_operation_expr : MINUS_ expression",
"unary_operation_expr : NOT_ expression",
"unary_operation_expr : AT_ expression",
"unary_operation_expr : LPAREN expression RPAREN",
"quantified_formula : FORALL_ type ID expression",
"quantified_formula : EXISTS_ type ID expression",
"function_call : class_name LPAREN opt_expression_list RPAREN",
"symbol_expr : ID",
"distribution_expr : DISTRIB class_name LPAREN opt_expression_list RPAREN",
"opt_expression_list : expression_list",
"opt_expression_list :",
"expression_list : expression_list COMMA expression",
"expression_list : expression",
"list_construct_expression : LBRACKET opt_expression_list RBRACKET",
"list_construct_expression : LBRACKET semi_colon_separated_expression_list RBRACKET",
"semi_colon_separated_expression_list : expression_list SEMI semi_colon_separated_expression_list",
"semi_colon_separated_expression_list : expression_list SEMI expression_list",
"map_construct_expression : LBRACE expression_pair_list RBRACE",
"expression_pair_list : expression_pair_list COMMA expression RIGHTARROW expression",
"expression_pair_list : expression RIGHTARROW expression",
"number_expr : NUMSIGN set_expr",
"number_expr : NUMSIGN type",
"origin_func_decl : ORIGIN type ID LPAREN type RPAREN SEMI",
"set_expr : explicit_set",
"set_expr : implicit_set",
"explicit_set : LBRACE opt_expression_list RBRACE",
"implicit_set : LBRACE type ID COLON expression RBRACE",
"implicit_set : LBRACE type ID RBRACE",
"tuple_set : LBRACE expression_list FOR type_var_lst COLON expression RBRACE",
"tuple_set : LBRACE expression_list FOR type_var_lst RBRACE",
"evidence_stmt : OBS evidence SEMI",
"evidence : symbol_evidence",
"evidence : value_evidence",
"value_evidence : expression EQ_ expression",
"symbol_evidence : implicit_set EQ_ explicit_set",
"query_stmt : QUERY query SEMI",
"query : expression",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 699 "blog.yacc"



void yyerror(const char *s) {
  cout << "Parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}
#line 800 "parser.cpp"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 4:
#line 206 "blog.yacc"
	{
    if(yystack.l_mark[0].stmt != NULL){
      blog->add(yystack.l_mark[0].stmt);
    }
  }
break;
case 5:
#line 211 "blog.yacc"
	{ blog->add(yystack.l_mark[0].stmt); }
break;
case 6:
#line 215 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 7:
#line 216 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 8:
#line 217 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 9:
#line 222 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 10:
#line 223 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].funcdec; }
break;
case 11:
#line 224 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].funcdec; }
break;
case 12:
#line 225 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].origdec; }
break;
case 13:
#line 226 "blog.yacc"
	{yyval.stmt = yystack.l_mark[0].numstdec; }
break;
case 14:
#line 227 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].distdec; }
break;
case 15:
#line 228 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 16:
#line 229 "blog.yacc"
	{ yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 17:
#line 234 "blog.yacc"
	{ yyval.stmt = new TypDecl(curr_line, curr_col, Symbol(yystack.l_mark[-1].sval->getValue())); }
break;
case 18:
#line 238 "blog.yacc"
	{ yyval.typ = yystack.l_mark[0].typ; }
break;
case 19:
#line 239 "blog.yacc"
	{ yyval.typ = yystack.l_mark[0].typ; }
break;
case 20:
#line 240 "blog.yacc"
	{ yyval.typ = yystack.l_mark[0].typ; }
break;
case 21:
#line 244 "blog.yacc"
	{ yyval.typ = new Ty(curr_line, curr_col, Symbol(yystack.l_mark[0].sval->getValue())); }
break;
case 22:
#line 249 "blog.yacc"
	{ yyval.typ = new Ty(curr_line, curr_col, Symbol(yystack.l_mark[-1].sval->getValue())); }
break;
case 23:
#line 254 "blog.yacc"
	{ yyval.typ = new Ty(curr_line, curr_col, Symbol(yystack.l_mark[-1].sval->getValue())); }
break;
case 24:
#line 258 "blog.yacc"
	{ yyval.i = 1; }
break;
case 25:
#line 259 "blog.yacc"
	{ yyval.i = yystack.l_mark[0].i + 1; }
break;
case 26:
#line 264 "blog.yacc"
	{ yyval.typ = yystack.l_mark[-3].typ; }
break;
case 27:
#line 268 "blog.yacc"
	{ yyval.varlist = NULL; }
break;
case 28:
#line 269 "blog.yacc"
	{yyval.varlist = NULL; }
break;
case 29:
#line 270 "blog.yacc"
	{ yyval.varlist = yystack.l_mark[-1].varlist; }
break;
case 30:
#line 274 "blog.yacc"
	{ 
    yyval.vardec = new VarDecl(curr_line, curr_col, *yystack.l_mark[-1].typ, Symbol(yystack.l_mark[0].sval->getValue())); 
  }
break;
case 31:
#line 280 "blog.yacc"
	{ 
      yyval.varlist = yystack.l_mark[-2].varlist; 
      yyval.varlist->push_back(*yystack.l_mark[0].vardec);
      delete(yystack.l_mark[0].vardec);
      /*$$ = $1; */
      /*$$->add((Expr*)(new VarDecl(curr_line, curr_col, *$3, Symbol($4->getValue())))); */
    }
break;
case 32:
#line 287 "blog.yacc"
	{ 
      yyval.varlist = new vector<VarDecl>();
      yyval.varlist->push_back(*yystack.l_mark[0].vardec);
      delete(yystack.l_mark[0].vardec);
      /*$$ = new VarDecl(curr_line, curr_col, *$1, Symbol($2->getValue())); */
    }
break;
case 33:
#line 297 "blog.yacc"
	{ 
      yyval.funcdec = new FuncDecl(curr_line, curr_col, false, *(yystack.l_mark[-5].typ), Symbol(yystack.l_mark[-4].sval->getValue()), yystack.l_mark[-1].exp);
      if(yystack.l_mark[-3].varlist != NULL){
        for(size_t i = 0; i < yystack.l_mark[-3].varlist->size(); i++){
          yyval.funcdec->addArg((*yystack.l_mark[-3].varlist)[i]);
        }
        delete(yystack.l_mark[-3].varlist);
      }
      /*if ($4 != NULL) $$->addArg(*$4);*/
    }
break;
case 34:
#line 311 "blog.yacc"
	{ 
      yyval.funcdec = new FuncDecl(curr_line, curr_col, true, *(yystack.l_mark[-4].typ), Symbol(yystack.l_mark[-3].sval->getValue()), yystack.l_mark[-1].exp);
      if(yystack.l_mark[-2].varlist != NULL){
        for(size_t i = 0; i < yystack.l_mark[-2].varlist->size(); i++){
          yyval.funcdec->addArg((*yystack.l_mark[-2].varlist)[i]);
        }
        delete(yystack.l_mark[-2].varlist);
      }
      /*if ($4 != NULL) $$->addArg(*$4);*/
    }
break;
case 35:
#line 325 "blog.yacc"
	{
      yyval.numstdec = new NumStDecl(curr_line, curr_col, yystack.l_mark[-3].typ->getTyp(), yystack.l_mark[-1].exp);
      if(yystack.l_mark[-2].varlst != NULL){
        for(size_t i = 0; i < yystack.l_mark[-2].varlst->size(); i++){
          yyval.numstdec->add(get<0>((*yystack.l_mark[-2].varlst)[i]), get<1>((*yystack.l_mark[-2].varlst)[i]));
        }
        delete(yystack.l_mark[-2].varlst);
      }
      /*$$->add(Symbol($4->getValue()), Symbol($6->getValue()));*/
    }
break;
case 36:
#line 338 "blog.yacc"
	{yyval.varlst = yystack.l_mark[-1].varlst; }
break;
case 37:
#line 339 "blog.yacc"
	{yyval.varlst = NULL; }
break;
case 38:
#line 345 "blog.yacc"
	{
    yyval.varlst = yystack.l_mark[-4].varlst;
    yyval.varlst->push_back(make_tuple(Symbol(yystack.l_mark[-2].sval->getValue()), Symbol(yystack.l_mark[0].sval->getValue())));
  }
break;
case 39:
#line 350 "blog.yacc"
	{ 
    yyval.varlst = new vector<tuple<Symbol, Symbol>>();
    yyval.varlst->push_back(make_tuple(Symbol(yystack.l_mark[-2].sval->getValue()), Symbol(yystack.l_mark[0].sval->getValue())));
  }
break;
case 40:
#line 359 "blog.yacc"
	{ }
break;
case 41:
#line 364 "blog.yacc"
	{
      yyval.distdec = yystack.l_mark[-1].distdec;
    }
break;
case 42:
#line 371 "blog.yacc"
	{
        yyval.distdec = new DistinctDecl(curr_line, curr_col, yystack.l_mark[-1].typ->getTyp());
        yyval.distdec->add(Symbol(yystack.l_mark[0].sval->getValue()), 1);
      }
break;
case 43:
#line 376 "blog.yacc"
	{
        yyval.distdec = new DistinctDecl(curr_line, curr_col, yystack.l_mark[-4].typ->getTyp());
        yyval.distdec->add(Symbol(yystack.l_mark[-3].sval->getValue()), yystack.l_mark[-1].ival->getValue());
      }
break;
case 44:
#line 381 "blog.yacc"
	{ 
        yyval.distdec = yystack.l_mark[-2].distdec;
        yyval.distdec->add(Symbol(yystack.l_mark[0].sval->getValue()), 1);
      }
break;
case 45:
#line 386 "blog.yacc"
	{ 
        yyval.distdec = yystack.l_mark[-5].distdec;
        yyval.distdec->add(Symbol(yystack.l_mark[-3].sval->getValue()), yystack.l_mark[-1].ival->getValue());
      }
break;
case 46:
#line 394 "blog.yacc"
	{ 
        auto idint = make_tuple(yystack.l_mark[0].sval->getValue(), 1);
        yyval.symbintpair = &(idint); 
       }
break;
case 47:
#line 399 "blog.yacc"
	{ 
      auto idint = make_tuple(yystack.l_mark[-3].sval->getValue(), yystack.l_mark[-1].ival->getValue());
      yyval.symbintpair = &(idint); 
    }
break;
case 48:
#line 406 "blog.yacc"
	{ 
      yyval.sval = new BLOGSymbol<string>(curr_line, curr_col, yystack.l_mark[0].sval->getValue());
    }
break;
case 49:
#line 409 "blog.yacc"
	{
      yyval.sval = new BLOGSymbol<string>(curr_line, curr_col, yystack.l_mark[-2].sval->getValue() + "." + yystack.l_mark[0].sval->getValue());
    }
break;
case 50:
#line 415 "blog.yacc"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 51:
#line 416 "blog.yacc"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 52:
#line 418 "blog.yacc"
	{ yyval.exp = new IfExpr(curr_line, curr_col, yystack.l_mark[-3].exp, yystack.l_mark[-1].exp, yystack.l_mark[0].exp); }
break;
case 53:
#line 420 "blog.yacc"
	{ yyval.exp = yystack.l_mark[-1].exp; }
break;
case 54:
#line 424 "blog.yacc"
	{yyval.exp = yystack.l_mark[0].exp; }
break;
case 55:
#line 425 "blog.yacc"
	{yyval.exp = NULL; }
break;
case 56:
#line 430 "blog.yacc"
	{ }
break;
case 57:
#line 431 "blog.yacc"
	{ }
break;
case 58:
#line 435 "blog.yacc"
	{yyval.exp = yystack.l_mark[0].exp;}
break;
case 59:
#line 436 "blog.yacc"
	{yyval.exp = yystack.l_mark[0].exp;}
break;
case 60:
#line 437 "blog.yacc"
	{yyval.exp = yystack.l_mark[0].exp;}
break;
case 61:
#line 438 "blog.yacc"
	{yyval.exp = yystack.l_mark[0].exp;}
break;
case 62:
#line 439 "blog.yacc"
	{yyval.exp = yystack.l_mark[0].exp;}
break;
case 63:
#line 440 "blog.yacc"
	{yyval.exp = yystack.l_mark[0].mapexp;}
break;
case 64:
#line 441 "blog.yacc"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 65:
#line 442 "blog.yacc"
	{ yyval.exp = yystack.l_mark[0].setexp; }
break;
case 66:
#line 443 "blog.yacc"
	{ yyval.exp = yystack.l_mark[0].numref; }
break;
case 67:
#line 444 "blog.yacc"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 68:
#line 449 "blog.yacc"
	{yyval.exp = new StringLiteral(curr_line, curr_col, yystack.l_mark[0].sval->getValue()); }
break;
case 69:
#line 451 "blog.yacc"
	{string charstr(1, yystack.l_mark[0].chrval->getValue()); yyval.exp = new StringLiteral(curr_line, curr_col, charstr); }
break;
case 70:
#line 453 "blog.yacc"
	{yyval.exp = new IntLiteral(curr_line, curr_col, yystack.l_mark[0].ival->getValue()); }
break;
case 71:
#line 455 "blog.yacc"
	{yyval.exp = new DoubleLiteral(curr_line, curr_col, yystack.l_mark[0].dblval->getValue()); }
break;
case 72:
#line 457 "blog.yacc"
	{yyval.exp = new BoolLiteral(curr_line, curr_col, yystack.l_mark[0].boolval->getValue()); }
break;
case 73:
#line 459 "blog.yacc"
	{yyval.exp = new NullLiteral(curr_line, curr_col); }
break;
case 74:
#line 464 "blog.yacc"
	{ 
      yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::PLUS, yystack.l_mark[-2].exp, yystack.l_mark[0].exp);   
    }
break;
case 75:
#line 468 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::MINUS, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 76:
#line 470 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::MUL, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 77:
#line 472 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::DIV, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 78:
#line 474 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::MOD, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 79:
#line 476 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::POWER, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 80:
#line 478 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::LT, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 81:
#line 480 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::GT, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 82:
#line 482 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::LE, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 83:
#line 484 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::GE, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 84:
#line 486 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::EQ, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 85:
#line 488 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::NEQ, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 86:
#line 490 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::AND, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 87:
#line 492 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::OR, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 88:
#line 494 "blog.yacc"
	{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::IMPLY, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); }
break;
case 89:
#line 496 "blog.yacc"
	{yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, yystack.l_mark[-3].exp, yystack.l_mark[-1].exp); }
break;
case 90:
#line 497 "blog.yacc"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 91:
#line 502 "blog.yacc"
	{yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, new IntLiteral(curr_line, curr_col, 0), yystack.l_mark[0].exp); }
break;
case 92:
#line 504 "blog.yacc"
	{yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::NOT, NULL, yystack.l_mark[0].exp); }
break;
case 93:
#line 506 "blog.yacc"
	{yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::AT, NULL, yystack.l_mark[0].exp); }
break;
case 94:
#line 507 "blog.yacc"
	{yyval.exp = yystack.l_mark[-1].exp; }
break;
case 95:
#line 512 "blog.yacc"
	{yyval.exp = new QuantExpr(curr_line, curr_col, AbsynConstant::FORALL, *(new VarDecl(curr_line, curr_col, *yystack.l_mark[-2].typ, Symbol(yystack.l_mark[-1].sval->getValue()))), yystack.l_mark[0].exp); }
break;
case 96:
#line 514 "blog.yacc"
	{yyval.exp = new QuantExpr(curr_line, curr_col, AbsynConstant::EXISTS, *(new VarDecl(curr_line, curr_col, *yystack.l_mark[-2].typ, Symbol(yystack.l_mark[-1].sval->getValue()))), yystack.l_mark[0].exp); }
break;
case 97:
#line 519 "blog.yacc"
	{ 
    yyval.exp = new FuncApp(curr_line, curr_col, Symbol(yystack.l_mark[-3].sval->getValue())); 
    if (yystack.l_mark[-1].explst != NULL){
      for(size_t i = 0; i < yystack.l_mark[-1].explst->size(); i++){
        yyval.exp->add((*yystack.l_mark[-1].explst)[i]);
      }
      delete(yystack.l_mark[-1].explst);
    }
  }
break;
case 98:
#line 532 "blog.yacc"
	{ yyval.exp = new VarRef(curr_line, curr_col, Symbol(yystack.l_mark[0].sval->getValue())); }
break;
case 99:
#line 537 "blog.yacc"
	{
      yyval.exp = new DistrExpr(curr_line, curr_col, Symbol(yystack.l_mark[-3].sval->getValue()));
      if(yystack.l_mark[-1].explst != NULL){
        for(size_t i = 0; i < yystack.l_mark[-1].explst->size(); i++){
          yyval.exp->add((*yystack.l_mark[-1].explst)[i]);
        }
        delete(yystack.l_mark[-1].explst);
      }
      /*$$->add($4);*/
      /*for(size_t i = 0; i < $4->size(); i++){*/
      /*  $$->add($4->get(i));*/
      /*} */
    }
break;
case 100:
#line 553 "blog.yacc"
	{yyval.explst = yystack.l_mark[0].explst;}
break;
case 101:
#line 554 "blog.yacc"
	{yyval.explst = NULL; }
break;
case 102:
#line 559 "blog.yacc"
	{ yyval.explst = yystack.l_mark[-2].explst;
      yyval.explst->push_back(yystack.l_mark[0].exp);
    }
break;
case 103:
#line 563 "blog.yacc"
	{ 
      yyval.explst = new vector<Expr*>();
      yyval.explst->push_back(yystack.l_mark[0].exp);
    }
break;
case 104:
#line 571 "blog.yacc"
	{ }
break;
case 105:
#line 572 "blog.yacc"
	{ }
break;
case 106:
#line 577 "blog.yacc"
	{ }
break;
case 107:
#line 578 "blog.yacc"
	{ }
break;
case 108:
#line 582 "blog.yacc"
	{ 
    /*$$ = $2; */
    yyval.mapexp = new MapExpr(curr_line, curr_col);
    for (size_t i = 0; i < yystack.l_mark[-1].exptuplst->size(); i++){
      yyval.mapexp->addMap(get<0>((*yystack.l_mark[-1].exptuplst)[i]), get<1>((*yystack.l_mark[-1].exptuplst)[i]));
    }
    delete(yystack.l_mark[-1].exptuplst);
    
  }
break;
case 109:
#line 596 "blog.yacc"
	{ 
      yyval.exptuplst = yystack.l_mark[-4].exptuplst;
      yyval.exptuplst->push_back(make_tuple(yystack.l_mark[-2].exp, yystack.l_mark[0].exp));
      /*$$ = $1;*/
      /*$$->addMap($3, $5);*/
    }
break;
case 110:
#line 603 "blog.yacc"
	{ 
      yyval.exptuplst = new vector<tuple<Expr*, Expr*>>();
      yyval.exptuplst->push_back(make_tuple(yystack.l_mark[-2].exp, yystack.l_mark[0].exp));
      /*$$ = new MapExpr(curr_line, curr_col);*/
      /*$$->addMap($1, $3);*/
    }
break;
case 111:
#line 613 "blog.yacc"
	{yyval.numref = new NumStRef(curr_line, curr_col, (Expr*)yystack.l_mark[0].setexp); }
break;
case 112:
#line 614 "blog.yacc"
	{ 
      VarDecl* var = new VarDecl(curr_line, curr_col, *yystack.l_mark[0].typ, Symbol("a"));
      yyval.numref = new NumStRef(curr_line, curr_col, new CondSet(curr_line, curr_col, *var, new BoolLiteral(curr_line, curr_col, true)));
  }
break;
case 113:
#line 621 "blog.yacc"
	{ yyval.origdec = new OriginDecl(curr_line, curr_col, yystack.l_mark[-5].typ->getTyp(), Symbol(yystack.l_mark[-4].sval->getValue()), yystack.l_mark[-2].typ->getTyp());  }
break;
case 114:
#line 625 "blog.yacc"
	{yyval.setexp = yystack.l_mark[0].setexp; }
break;
case 115:
#line 626 "blog.yacc"
	{yyval.setexp = yystack.l_mark[0].setexp; }
break;
case 116:
#line 632 "blog.yacc"
	{
      yyval.setexp = new ListSet(curr_line, curr_col);
      for(size_t i = 0; i < yystack.l_mark[-1].explst->size(); i++){
        yyval.setexp->add((*yystack.l_mark[-1].explst)[i]);
      }
      delete(yystack.l_mark[-1].explst);
      /*$$ = new SetExpr(curr_line, curr_col); */
      /*$$->add($2);*/
    }
break;
case 117:
#line 646 "blog.yacc"
	{ 
      yyval.setexp = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *yystack.l_mark[-4].typ, Symbol(yystack.l_mark[-3].sval->getValue())), yystack.l_mark[-1].exp);
      /*$$ = new CondSet(curr_line, curr_col, NULL);*/
      /*$$->add($5);*/
    }
break;
case 118:
#line 652 "blog.yacc"
	{ 
      yyval.setexp = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *yystack.l_mark[-2].typ, Symbol(yystack.l_mark[-1].sval->getValue())));
    }
break;
case 119:
#line 661 "blog.yacc"
	{ }
break;
case 120:
#line 663 "blog.yacc"
	{ }
break;
case 121:
#line 669 "blog.yacc"
	{yyval.stmt = yystack.l_mark[-1].stmt; }
break;
case 122:
#line 672 "blog.yacc"
	{yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 123:
#line 673 "blog.yacc"
	{yyval.stmt = yystack.l_mark[0].stmt; }
break;
case 124:
#line 679 "blog.yacc"
	{
    yyval.stmt = new Evidence(curr_line, curr_col, yystack.l_mark[-2].exp, yystack.l_mark[0].exp); 
  }
break;
case 125:
#line 687 "blog.yacc"
	{ yyval.stmt = new Evidence(curr_line, curr_col, yystack.l_mark[-2].setexp, yystack.l_mark[0].setexp); }
break;
case 126:
#line 691 "blog.yacc"
	{yyval.stmt = yystack.l_mark[-1].stmt; }
break;
case 127:
#line 695 "blog.yacc"
	{ yyval.stmt = new Query(curr_line, curr_col, yystack.l_mark[0].exp); }
break;
#line 1640 "parser.cpp"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
