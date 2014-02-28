#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "parser.y"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "BLOGSymbol.h"
#include "Absyn.h"
#include "ArrayExpr.h"
#include "BoolLiteral.h"
#include "BlogProgram.h"
#include "CondSet.h"
#include "Decl.h"
#include "DistinctDecl.h"
#include "DistrExpr.h"
#include "DoubleLiteral.h"
#include "Evidence.h"
#include "Expr.h"
#include "FuncApp.h"
#include "FuncDecl.h"
#include "IfExpr.h"
#include "IntLiteral.h"
#include "Literal.h"
#include "ListSet.h"
#include "MapExpr.h"
#include "NullLiteral.h"
#include "NumStDecl.h"
#include "NumStRef.h"
#include "OpExpr.h"
#include "OriginDecl.h"
#include "QuantExpr.h"
#include "Query.h"
#include "SetExpr.h"
#include "Stmt.h"
#include "StringLiteral.h"
#include "Symbol.h"
#include "TimeStampLiteral.h"
#include "Ty.h"
#include "TypDecl.h"
#include "VarDecl.h"
#include "VarRef.h"
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
BlogProgram *blog = new BlogProgram(0,0);

BlogProgram* parse(const char* inp) {
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
  /*return blog;*/
  /*FILE *output = fopen("output.out", "w");*/
  /*cout << blog->size() << endl;*/
  /*NumStDecl* st = (NumStDecl*)(blog->get(0));*/
  /*Symbol o = st->getArgOrigin(0);*/
  /*cout << "current val: " << o.getValue() << endl;*/
  /*Evidence* t = (Evidence*)(blog->get(0));*/
  /*cout << "assigned" << endl;*/
  /*NumStRef* left = (NumStRef*)(t->getLeft());*/
  /*cout << "expression extracted" << endl;*/
  return blog;
  /*blog->print(output, 0);*/
  /*return 0;*/
  
  
}
#line 90 "parser.y"
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
#line 147 "y.tab.c"
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
#define EXISTS 271
#define FORALL 272
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
#define AT 285
#define PLUS 286
#define MULT 287
#define DIV 288
#define MOD 289
#define POWER 290
#define MINUS 291
#define LST 292
#define LT 293
#define GT 294
#define LEQ 295
#define GEQ 296
#define EQEQ 297
#define NEQ 298
#define EQ 299
#define DISTRIB 300
#define NOT 301
#define AND 302
#define OR 303
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
short yylhs[] = {                                        -1,
    0,   52,   52,   53,   53,    1,    1,    1,    2,    2,
    2,    2,    2,    2,    2,    2,    3,   38,   38,   38,
   38,   42,   40,   39,   51,   51,   41,   44,   44,   44,
   49,   43,   43,   10,   11,    8,   45,   45,   46,   46,
    4,   12,   48,   48,   48,   48,   47,   47,   50,   50,
   29,   29,   29,   29,   26,   26,    5,    5,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   17,   18,   18,
   18,   18,   18,   18,   19,   19,   19,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,   19,   19,   19,
   19,   20,   20,   20,   20,   21,   21,   23,   25,   22,
   35,   35,   36,   36,   24,   24,   34,   34,   28,   37,
   37,   27,   27,    9,   30,   30,   31,   32,   32,   33,
   33,    6,   13,   13,   14,   15,    7,   16,
};
short yylen[] = {                                         2,
    1,    0,    1,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    3,    1,    1,    1,
    1,    1,    4,    2,    2,    3,    6,    0,    2,    3,
    2,    3,    1,    7,    6,    5,    3,    0,    5,    3,
    8,    2,    3,    6,    3,    6,    1,    4,    1,    3,
    2,    1,    5,    3,    2,    0,    4,    6,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    4,
    1,    2,    2,    2,    3,    4,    4,    4,    1,    5,
    1,    0,    3,    1,    3,    3,    3,    3,    3,    5,
    3,    2,    2,    7,    1,    1,    3,    6,    4,    7,
    5,    3,    1,    1,    3,    3,    3,    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    5,    6,    9,   16,   15,    7,    8,   13,   12,
   10,   11,   14,    0,    1,    0,    0,    0,    0,    0,
    0,   20,   19,   21,   18,    0,    0,   22,    0,    0,
    0,   74,   71,   72,   73,   70,   69,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   61,   59,
   91,   65,   60,   62,   63,   68,   67,   64,   66,  115,
  116,    0,    0,  124,  123,    0,    0,    0,    0,    0,
    0,   42,    4,   17,    0,    0,    0,   24,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  112,  113,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  127,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  122,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   50,    0,   95,    0,  117,    0,    0,  109,    0,  106,
  105,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  126,   57,    0,    0,    0,    0,    0,    0,    0,
   52,    0,    0,   23,    0,   26,   29,    0,    0,   33,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  119,  107,    0,   90,   98,    0,    0,    0,    0,
   37,    0,    0,    0,   36,    0,    0,   31,    0,   30,
   35,    0,    0,   44,  100,    0,    0,   58,    0,   40,
    0,    0,   54,   46,   27,   32,   34,  114,    0,  118,
    0,    0,    0,   41,   39,    0,   53,   55,
};
short yydgoto[] = {                                      11,
   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
   22,   23,   73,   74,   75,   57,  111,   59,   60,   61,
   62,   63,   64,   65,   66,  257,   67,   68,  192,   69,
   70,   71,    0,  112,  107,  108,  109,  110,   32,   33,
   34,   35,  199,  145,  139,  187,    0,   24,  200,   72,
   88,   25,   26,
};
short yysindex[] = {                                   -229,
 -273, -260, -260, -260, -255,  523,  523, -260, -241, -255,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -238,    0, -229, -201, -239, -228, -222,
 -185,    0,    0,    0,    0, -173, -150,    0, -126, -260,
 -260,    0,    0,    0,    0,    0,    0, -152,  523,  523,
 -107,  523, -258,  523,  478,  523, -131,  802,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -134, -120,    0,    0,  613, -119,  -79,  -96, -104,
  -66,    0,    0,    0,  -58, -260,  -93,    0,  -76,  -76,
  -72,  -74,  -38,  -37, -107,  802, -231, -152,  -67,  871,
  478,    0,    0,  636, -303,  666,  -69,  -59, -287,  -33,
  802,  -65,  -63, -167,    0,  523,  523,  523,  523,  523,
  523,  523,  523,  523,  523,  523,  523,  523,  523,  523,
  523,  523,    0,  523,  -64, -138, -107,  -26, -237,  -60,
  -30,  -49, -222, -252, -237,  -42, -260,   -3,  523,  523,
    0,  523,    0,  523,    0,  523,  523,    0, -206,    0,
    0,  523, -231,  -35,  -35,  -35,  -35, -231, -155, -155,
 -155, -155, -155, -155,  871,  871,  848,  582,  -39,  802,
  523,    0,    0,  523,  -24,  -16, -209,  523,  523, -237,
    0,  -21,   14,    0, -260,    0,    0,   12, -163,    0,
  -15,  523,  -13,  -12,  802,  802,    2,  802,  802,  696,
  523,    0,    0, -167,    0,    0,  726,  523,   26,   42,
    0,  436,  802,    9,    0,   17,   36,    0, -260,    0,
    0,  749,   29,    0,    0,  523,  772,    0,   25,    0,
   40, -237,    0,    0,    0,    0,    0,    0,  802,    0,
   35,   62,   92,    0,    0, -237,    0,    0,
};
short yyrindex[] = {                                    352,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  354,    0,    0,    0,  -28,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -78,    0,    0,
    0,    0,    0,    0,   50,   56,    0,   67,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  825,    0,    0, -213,
    0,    0,    0,    0,    0,    0,    0,    0, -211,   57,
    0, -135,    0,    0,    0, -153,  272,   69,    0, -233,
   50,    0,    0,    0,  553, -223,    0, -272,    0,    0,
 -140,    0,    0,   71,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   73,    0,    0,    0,    0,    0,    0,    0, -121,
    0,    0,   22,    0,    0,    0,    0,    0,    0,    0,
    0,   73,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  303,   72,  122,  172,  222,  334, -112,   -9,
   41,   91,  141,  191,  241,  353,  367,    0,    0,   77,
   50,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  386,  405,    0, -220, -117,    0,
    0,    0,    0,   75,    0,    0,    0,   73,    0,    0,
    0,    0, -253,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -215,    0,
    0,    0, -177,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
  363,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   -6,    0,    0,    0,
    0, -116,    0,    0,    0,    0,    0,    0, -115,  339,
  264,  395,    0,  242,  -54,  -53,    0,   11,    0,    0,
    0,  157,    0,  316,    0,    0,    0,    0,  185,  -45,
  279,    0,    0,
};
#define YYTABLESIZE 1186
short yytable[] = {                                      58,
   76,  113,  114,   51,   95,   99,   27,   28,   29,   28,
   29,   87,   31,   36,   37,   28,   29,  157,   78,   30,
  188,   30,  191,   93,   38,   93,  158,   30,  191,  201,
    1,    2,    3,    4,    5,    6,    7,    8,   79,  101,
    9,  101,   96,   97,   38,  100,   28,  104,  106,  151,
   93,   94,   51,   85,  101,  117,  118,  119,  120,  197,
   51,  189,   51,  103,   86,   93,   81,   82,   93,   93,
   93,   93,   93,  191,  224,  190,   93,  179,   93,   10,
   93,  104,   93,  131,  111,   38,   38,   28,   28,  110,
  104,  185,   87,  111,   89,  220,  142,  207,  110,   38,
  211,   28,  221,   94,   84,   94,   90,  212,  214,  163,
  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,
  174,  175,  176,  177,  178,  191,  253,  180,   56,   91,
  116,  117,  118,  119,  120,  121,   56,  156,  162,  191,
  258,  229,  205,  206,   81,   94,   81,  208,  230,  209,
  210,   94,   94,   92,  198,   95,   94,  203,   94,  131,
   94,   39,   94,  239,  104,  104,   80,  183,  184,   43,
   43,  104,   98,  104,  115,  104,  132,  217,   99,  135,
   99,  222,  223,   45,   45,  133,   81,  103,  103,   81,
   81,   81,   81,   81,  103,  232,  103,   81,  103,   81,
  136,   81,  137,   81,  237,  227,  138,   99,   99,   99,
   99,   99,   99,  140,   99,   99,   99,   99,   99,   99,
   99,  141,  143,   99,   99,   99,   99,   99,   22,  249,
   22,   99,   49,   99,  144,   99,   99,   99,  147,  198,
  148,  149,  150,  152,  155,  156,  159,   82,  181,   82,
  160,   22,  161,  186,  193,  195,  202,   22,   22,   22,
   22,   22,   22,  194,   22,   22,   22,   22,   22,   22,
   22,  204,  216,   22,   22,   22,   22,   22,   25,  131,
   25,   22,  219,   22,  225,   22,  218,   22,  226,   82,
  231,  228,   82,   82,   82,   82,   82,   83,  233,   83,
   82,   25,   82,  234,   82,  240,   82,   25,   25,   25,
   25,   25,   25,  235,   25,   25,   25,   25,   25,   25,
   25,  241,  243,   25,   25,   25,   25,   25,   77,  245,
   77,   25,  244,   25,  248,   25,  251,   25,  252,   83,
  254,  255,   83,   83,   83,   83,   83,   84,  256,   84,
   83,    2,   83,    3,   83,   28,   83,   77,   77,   77,
   77,   77,   77,  102,   77,   77,   77,   77,   77,   77,
   77,  102,  128,   77,   77,   77,   77,   77,   78,   49,
   78,   77,  125,   77,  102,   77,  101,   77,   83,   84,
  108,  102,   84,   84,   84,   84,   84,   85,  182,   85,
   84,   77,   84,  213,   84,  146,   84,   78,   78,   78,
   78,   78,   78,  246,   78,   78,   78,   78,   78,   78,
   78,  196,    0,   78,   78,   78,   78,   78,   79,    0,
   79,   78,    0,   78,    0,   78,    0,   78,    0,   85,
    0,    0,   85,   85,   85,   85,   85,   86,    0,   86,
   85,    0,   85,    0,   85,    0,   85,   79,   79,   79,
   79,   79,   79,    0,   79,   79,   79,   79,   79,   79,
   79,    0,    0,   79,   79,   79,   79,   79,   80,    0,
   80,   79,    0,   79,    0,   79,    0,   79,    0,   86,
    0,    0,   86,   86,   86,   86,   86,   87,    0,   87,
   86,    0,   86,    0,   86,    0,   86,   80,   80,   80,
   80,   80,   80,    0,   80,   80,   80,   80,   80,   80,
   80,    0,    0,   80,   80,   80,   80,   80,   92,    0,
   92,   80,    0,   80,    0,   80,    0,   80,    0,   87,
    0,    0,   87,   87,   87,   87,   87,    0,    0,    0,
   87,    0,   87,    0,   87,    0,   87,   92,    0,   75,
    0,   75,   92,    0,   92,   92,   92,   92,   92,   92,
   92,    0,    0,   92,   92,   92,   92,   92,    0,    0,
    0,   92,    0,   92,    0,   92,    0,   92,   75,    0,
   76,    0,   76,   75,    0,   75,   75,   75,   75,   75,
   75,   75,    0,    0,   75,   75,   75,   75,   75,   88,
    0,   88,   75,    0,   75,    0,   75,    0,   75,   76,
    0,    0,    0,   89,   76,   89,   76,   76,   76,   76,
   76,   76,   76,    0,    0,   76,   76,   76,   76,   76,
    0,    0,   97,   76,   97,   76,    0,   76,    0,   76,
    0,   88,    0,    0,   88,   88,   88,   88,   88,    0,
    0,   96,   88,   96,   88,   89,   88,    0,   88,    0,
   89,   89,   89,    0,    0,    0,   89,    0,   89,    0,
   89,    0,   89,    0,   97,    0,    0,    0,    0,    0,
   97,   97,    0,    0,  242,   97,    0,   97,    0,   97,
    0,   97,    0,   96,    0,    0,    0,    0,    0,   96,
   96,    0,    0,    0,   96,    0,   96,    0,   96,    0,
   96,  116,  117,  118,  119,  120,  121,    0,  122,  123,
  124,  125,  126,  127,    0,    0,    0,  128,  129,  130,
    0,    0,    0,    0,    0,   28,   29,    0,   40,   41,
  131,   42,   43,   44,   45,   46,   47,  105,    0,    0,
    0,    0,   49,    0,    0,    0,    0,    0,   50,    0,
    0,    0,    0,    0,    0,    0,    0,   51,   52,    0,
    0,    0,    0,    0,    0,    0,   53,    0,   54,    0,
   55,    0,   56,   40,   41,    0,   42,   43,   44,   45,
   46,   47,   48,    0,    0,    0,    0,   49,    0,    0,
    0,    0,    0,   50,    0,    0,    0,    0,    0,    0,
    0,    0,   51,   52,    0,    0,    0,    0,    0,    0,
    0,   53,   22,   54,    0,   55,    0,   56,   99,   99,
   99,   99,   99,   99,    0,   99,   99,   99,   99,   99,
   99,    0,    0,    0,   99,   99,   99,   99,    0,    0,
    0,    0,   99,   49,    0,    0,   99,  116,  117,  118,
  119,  120,  121,    0,  122,  123,  124,  125,  126,  127,
    0,    0,    0,  128,  129,  130,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  131,  215,  116,  117,
  118,  119,  120,  121,    0,  122,  123,  124,  125,  126,
  127,  134,    0,    0,  128,  129,  130,    0,    0,    0,
    0,  116,  117,  118,  119,  120,  121,  131,  122,  123,
  124,  125,  126,  127,    0,    0,    0,  128,  129,  130,
    0,    0,    0,    0,    0,    0,    0,  153,    0,    0,
  131,  116,  117,  118,  119,  120,  121,    0,  122,  123,
  124,  125,  126,  127,    0,    0,    0,  128,  129,  130,
    0,    0,    0,    0,    0,  154,    0,    0,    0,    0,
  131,  116,  117,  118,  119,  120,  121,    0,  122,  123,
  124,  125,  126,  127,    0,    0,    0,  128,  129,  130,
    0,    0,    0,    0,    0,  236,    0,    0,    0,    0,
  131,  116,  117,  118,  119,  120,  121,    0,  122,  123,
  124,  125,  126,  127,    0,    0,    0,  128,  129,  130,
    0,  238,    0,    0,  116,  117,  118,  119,  120,  121,
  131,  122,  123,  124,  125,  126,  127,    0,    0,    0,
  128,  129,  130,    0,  247,    0,    0,  116,  117,  118,
  119,  120,  121,  131,  122,  123,  124,  125,  126,  127,
    0,    0,    0,  128,  129,  130,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  250,  131,  116,  117,  118,
  119,  120,  121,    0,  122,  123,  124,  125,  126,  127,
    0,    0,    0,  128,  129,  130,    0,    0,    0,    0,
  116,  116,  116,  116,  116,  116,  131,  116,  116,  116,
  116,  116,  116,    0,    0,    0,  116,  116,  116,    0,
    0,    0,    0,  116,  117,  118,  119,  120,  121,  116,
  122,  123,  124,  125,  126,  127,    0,    0,    0,  128,
  129,    0,    0,    0,    0,    0,  116,  117,  118,  119,
  120,  121,  131,  122,  123,  124,  125,  126,  127,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  131,
};
short yycheck[] = {                                       6,
    7,   56,   56,  257,  308,   51,  280,  268,  269,  268,
  269,  315,    2,    3,    4,  268,  269,  305,    8,  280,
  258,  280,  139,  257,  280,  259,  314,  280,  145,  145,
  260,  261,  262,  263,  264,  265,  266,  267,  280,  312,
  270,  314,   49,   50,  258,   52,  258,   54,   55,   95,
   40,   41,  306,  293,  313,  287,  288,  289,  290,  312,
  314,  299,  300,   53,  293,  299,  305,  306,  302,  303,
  304,  305,  306,  190,  190,  313,  310,  132,  312,  309,
  314,  305,  316,  315,  305,  299,  300,  299,  300,  305,
  314,  137,  315,  314,  280,  305,   86,  152,  314,  313,
  307,  313,  312,  257,  306,  259,  280,  314,  162,  116,
  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
  127,  128,  129,  130,  131,  242,  242,  134,  306,  280,
  286,  287,  288,  289,  290,  291,  314,  305,  306,  256,
  256,  305,  149,  150,  257,  299,  259,  154,  312,  156,
  157,  305,  306,  280,  144,  308,  310,  147,  312,  315,
  314,    5,  316,  218,  305,  306,   10,  306,  307,  305,
  306,  312,  280,  314,  306,  316,  311,  184,  257,  299,
  259,  188,  189,  305,  306,  306,  299,  305,  306,  302,
  303,  304,  305,  306,  312,  202,  314,  310,  316,  312,
  280,  314,  299,  316,  211,  195,  311,  286,  287,  288,
  289,  290,  291,  280,  293,  294,  295,  296,  297,  298,
  299,  280,  316,  302,  303,  304,  305,  306,  257,  236,
  259,  310,  311,  312,  311,  314,  315,  316,  311,  229,
  315,  280,  280,  311,  314,  305,  280,  257,  313,  259,
  316,  280,  316,  280,  315,  305,  299,  286,  287,  288,
  289,  290,  291,  294,  293,  294,  295,  296,  297,  298,
  299,  275,  312,  302,  303,  304,  305,  306,  257,  315,
  259,  310,  299,  312,  306,  314,  311,  316,  275,  299,
  306,  280,  302,  303,  304,  305,  306,  257,  312,  259,
  310,  280,  312,  316,  314,  280,  316,  286,  287,  288,
  289,  290,  291,  312,  293,  294,  295,  296,  297,  298,
  299,  280,  314,  302,  303,  304,  305,  306,  257,  294,
  259,  310,  316,  312,  306,  314,  312,  316,  299,  299,
  306,  280,  302,  303,  304,  305,  306,  257,  257,  259,
  310,    0,  312,    0,  314,  299,  316,  286,  287,  288,
  289,  290,  291,  314,  293,  294,  295,  296,  297,  298,
  299,  316,  306,  302,  303,  304,  305,  306,  257,  311,
  259,  310,  306,  312,  312,  314,  316,  316,   26,  299,
  316,   53,  302,  303,  304,  305,  306,  257,  135,  259,
  310,    7,  312,  162,  314,   90,  316,  286,  287,  288,
  289,  290,  291,  229,  293,  294,  295,  296,  297,  298,
  299,  143,   -1,  302,  303,  304,  305,  306,  257,   -1,
  259,  310,   -1,  312,   -1,  314,   -1,  316,   -1,  299,
   -1,   -1,  302,  303,  304,  305,  306,  257,   -1,  259,
  310,   -1,  312,   -1,  314,   -1,  316,  286,  287,  288,
  289,  290,  291,   -1,  293,  294,  295,  296,  297,  298,
  299,   -1,   -1,  302,  303,  304,  305,  306,  257,   -1,
  259,  310,   -1,  312,   -1,  314,   -1,  316,   -1,  299,
   -1,   -1,  302,  303,  304,  305,  306,  257,   -1,  259,
  310,   -1,  312,   -1,  314,   -1,  316,  286,  287,  288,
  289,  290,  291,   -1,  293,  294,  295,  296,  297,  298,
  299,   -1,   -1,  302,  303,  304,  305,  306,  257,   -1,
  259,  310,   -1,  312,   -1,  314,   -1,  316,   -1,  299,
   -1,   -1,  302,  303,  304,  305,  306,   -1,   -1,   -1,
  310,   -1,  312,   -1,  314,   -1,  316,  286,   -1,  257,
   -1,  259,  291,   -1,  293,  294,  295,  296,  297,  298,
  299,   -1,   -1,  302,  303,  304,  305,  306,   -1,   -1,
   -1,  310,   -1,  312,   -1,  314,   -1,  316,  286,   -1,
  257,   -1,  259,  291,   -1,  293,  294,  295,  296,  297,
  298,  299,   -1,   -1,  302,  303,  304,  305,  306,  257,
   -1,  259,  310,   -1,  312,   -1,  314,   -1,  316,  286,
   -1,   -1,   -1,  257,  291,  259,  293,  294,  295,  296,
  297,  298,  299,   -1,   -1,  302,  303,  304,  305,  306,
   -1,   -1,  257,  310,  259,  312,   -1,  314,   -1,  316,
   -1,  299,   -1,   -1,  302,  303,  304,  305,  306,   -1,
   -1,  257,  310,  259,  312,  299,  314,   -1,  316,   -1,
  304,  305,  306,   -1,   -1,   -1,  310,   -1,  312,   -1,
  314,   -1,  316,   -1,  299,   -1,   -1,   -1,   -1,   -1,
  305,  306,   -1,   -1,  259,  310,   -1,  312,   -1,  314,
   -1,  316,   -1,  299,   -1,   -1,   -1,   -1,   -1,  305,
  306,   -1,   -1,   -1,  310,   -1,  312,   -1,  314,   -1,
  316,  286,  287,  288,  289,  290,  291,   -1,  293,  294,
  295,  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,
   -1,   -1,   -1,   -1,   -1,  268,  269,   -1,  271,  272,
  315,  274,  275,  276,  277,  278,  279,  280,   -1,   -1,
   -1,   -1,  285,   -1,   -1,   -1,   -1,   -1,  291,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  300,  301,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  309,   -1,  311,   -1,
  313,   -1,  315,  271,  272,   -1,  274,  275,  276,  277,
  278,  279,  280,   -1,   -1,   -1,   -1,  285,   -1,   -1,
   -1,   -1,   -1,  291,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  300,  301,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  309,  280,  311,   -1,  313,   -1,  315,  286,  287,
  288,  289,  290,  291,   -1,  293,  294,  295,  296,  297,
  298,   -1,   -1,   -1,  302,  303,  304,  305,   -1,   -1,
   -1,   -1,  310,  311,   -1,   -1,  314,  286,  287,  288,
  289,  290,  291,   -1,  293,  294,  295,  296,  297,  298,
   -1,   -1,   -1,  302,  303,  304,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  315,  316,  286,  287,
  288,  289,  290,  291,   -1,  293,  294,  295,  296,  297,
  298,  299,   -1,   -1,  302,  303,  304,   -1,   -1,   -1,
   -1,  286,  287,  288,  289,  290,  291,  315,  293,  294,
  295,  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  312,   -1,   -1,
  315,  286,  287,  288,  289,  290,  291,   -1,  293,  294,
  295,  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,
   -1,   -1,   -1,   -1,   -1,  310,   -1,   -1,   -1,   -1,
  315,  286,  287,  288,  289,  290,  291,   -1,  293,  294,
  295,  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,
   -1,   -1,   -1,   -1,   -1,  310,   -1,   -1,   -1,   -1,
  315,  286,  287,  288,  289,  290,  291,   -1,  293,  294,
  295,  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,
   -1,  306,   -1,   -1,  286,  287,  288,  289,  290,  291,
  315,  293,  294,  295,  296,  297,  298,   -1,   -1,   -1,
  302,  303,  304,   -1,  306,   -1,   -1,  286,  287,  288,
  289,  290,  291,  315,  293,  294,  295,  296,  297,  298,
   -1,   -1,   -1,  302,  303,  304,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  314,  315,  286,  287,  288,
  289,  290,  291,   -1,  293,  294,  295,  296,  297,  298,
   -1,   -1,   -1,  302,  303,  304,   -1,   -1,   -1,   -1,
  286,  287,  288,  289,  290,  291,  315,  293,  294,  295,
  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,   -1,
   -1,   -1,   -1,  286,  287,  288,  289,  290,  291,  315,
  293,  294,  295,  296,  297,  298,   -1,   -1,   -1,  302,
  303,   -1,   -1,   -1,   -1,   -1,  286,  287,  288,  289,
  290,  291,  315,  293,  294,  295,  296,  297,  298,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  315,
};
#define YYFINAL 11
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 316
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ELSE","IF","THEN","TYPE",
"RANDOM","FIXED","ORIGIN","DISTINCT","QUERY","OBS","PARAM","LIST","MAP",
"DISTRIBUTION","EXISTS","FORALL","FOR","NULLITY","INT_LITERAL","DOUBLE_LITERAL",
"BOOLEAN_LITERAL","CHAR_LITERAL","STRING_LITERAL","ID","PARFACTOR","FACTOR",
"ERROR","ELSEIF","AT","PLUS","MULT","DIV","MOD","POWER","MINUS","LST","LT","GT",
"LEQ","GEQ","EQEQ","NEQ","EQ","DISTRIB","NOT","AND","OR","DOUBLERIGHTARROW",
"COMMA","SEMI","COLON","DOT","NUMSIGN","RIGHTARROW","LPAREN","RPAREN","LBRACE",
"RBRACE","LBRACKET","RBRACKET",
};
char *yyrule[] = {
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
"type : array_type",
"type : map_type",
"name_type : ID",
"list_type : LIST LT ID GT",
"array_type : ID dims",
"dims : LBRACKET RBRACKET",
"dims : LBRACKET RBRACKET dims",
"map_type : MAP LT type COMMA type GT",
"opt_parenthesized_type_var_lst :",
"opt_parenthesized_type_var_lst : LPAREN RPAREN",
"opt_parenthesized_type_var_lst : LPAREN type_var_lst RPAREN",
"var_decl : type ID",
"type_var_lst : type_var_lst COMMA var_decl",
"type_var_lst : var_decl",
"fixed_func_decl : FIXED type ID opt_parenthesized_type_var_lst EQ expression SEMI",
"rand_func_decl : RANDOM type ID opt_parenthesized_type_var_lst dependency_statement_body SEMI",
"number_stmt : NUMSIGN name_type opt_parenthesized_origin_var_list dependency_statement_body SEMI",
"opt_parenthesized_origin_var_list : LPAREN origin_var_list RPAREN",
"opt_parenthesized_origin_var_list :",
"origin_var_list : origin_var_list COMMA ID EQ ID",
"origin_var_list : ID EQ ID",
"distribution_decl : DISTRIBUTION ID EQ class_name LPAREN opt_expression_list RPAREN SEMI",
"distinct_decl : id_or_subid_list SEMI",
"id_or_subid_list : DISTINCT name_type ID",
"id_or_subid_list : DISTINCT name_type ID LBRACKET INT_LITERAL RBRACKET",
"id_or_subid_list : id_or_subid_list COMMA ID",
"id_or_subid_list : id_or_subid_list COMMA ID LBRACKET INT_LITERAL RBRACKET",
"id_or_subid : ID",
"id_or_subid : ID LBRACKET INT_LITERAL RBRACKET",
"class_name : ID",
"class_name : ID DOT class_name",
"dependency_statement_body : EQ expression",
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
"operation_expr : expression PLUS expression",
"operation_expr : expression MINUS expression",
"operation_expr : expression MULT expression",
"operation_expr : expression DIV expression",
"operation_expr : expression MOD expression",
"operation_expr : expression POWER expression",
"operation_expr : expression LT expression",
"operation_expr : expression GT expression",
"operation_expr : expression LEQ expression",
"operation_expr : expression GEQ expression",
"operation_expr : expression EQEQ expression",
"operation_expr : expression NEQ expression",
"operation_expr : expression AND expression",
"operation_expr : expression OR expression",
"operation_expr : expression DOUBLERIGHTARROW expression",
"operation_expr : expression LBRACKET expression RBRACKET",
"operation_expr : unary_operation_expr",
"unary_operation_expr : MINUS expression",
"unary_operation_expr : NOT expression",
"unary_operation_expr : AT expression",
"unary_operation_expr : LPAREN expression RPAREN",
"quantified_formula : FORALL type ID expression",
"quantified_formula : EXISTS type ID expression",
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
"value_evidence : expression EQ expression",
"symbol_evidence : implicit_set EQ explicit_set",
"query_stmt : QUERY query SEMI",
"query : expression",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 725 "parser.y"



void yyerror(const char *s) {
  cout << "Parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}
#line 767 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
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
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
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
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
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
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 4:
#line 219 "parser.y"
{
    if(yyvsp[0].stmt != NULL){
      blog->add(yyvsp[0].stmt);
    }
  }
break;
case 5:
#line 224 "parser.y"
{ blog->add(yyvsp[0].stmt); }
break;
case 6:
#line 228 "parser.y"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 7:
#line 229 "parser.y"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 8:
#line 230 "parser.y"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 9:
#line 235 "parser.y"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 10:
#line 236 "parser.y"
{ yyval.stmt = yyvsp[0].funcdec; }
break;
case 11:
#line 237 "parser.y"
{ yyval.stmt = yyvsp[0].funcdec; }
break;
case 12:
#line 238 "parser.y"
{ yyval.stmt = yyvsp[0].origdec; }
break;
case 13:
#line 239 "parser.y"
{yyval.stmt = yyvsp[0].numstdec; }
break;
case 14:
#line 240 "parser.y"
{ yyval.stmt = yyvsp[0].distdec; }
break;
case 15:
#line 241 "parser.y"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 16:
#line 242 "parser.y"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 17:
#line 247 "parser.y"
{ yyval.stmt = new TypDecl(curr_line, curr_col, Symbol(yyvsp[-1].sval->getValue())); }
break;
case 18:
#line 251 "parser.y"
{ yyval.typ = yyvsp[0].typ; }
break;
case 19:
#line 252 "parser.y"
{ yyval.typ = yyvsp[0].typ; }
break;
case 20:
#line 253 "parser.y"
{ yyval.typ = yyvsp[0].typ; }
break;
case 21:
#line 254 "parser.y"
{ yyval.typ = yyvsp[0].typ; }
break;
case 22:
#line 258 "parser.y"
{ yyval.typ = new Ty(curr_line, curr_col, Symbol(yyvsp[0].sval->getValue())); }
break;
case 23:
#line 263 "parser.y"
{ yyval.typ = new Ty(curr_line, curr_col, Symbol(yyvsp[-1].sval->getValue())); }
break;
case 24:
#line 268 "parser.y"
{ yyval.typ = new Ty(curr_line, curr_col, Symbol(yyvsp[-1].sval->getValue())); }
break;
case 25:
#line 272 "parser.y"
{ yyval.i = 1; }
break;
case 26:
#line 273 "parser.y"
{ yyval.i = yyvsp[0].i + 1; }
break;
case 27:
#line 278 "parser.y"
{ yyval.typ = yyvsp[-3].typ; }
break;
case 28:
#line 282 "parser.y"
{ yyval.varlist = NULL; }
break;
case 29:
#line 283 "parser.y"
{yyval.varlist = NULL; }
break;
case 30:
#line 284 "parser.y"
{ yyval.varlist = yyvsp[-1].varlist; }
break;
case 31:
#line 288 "parser.y"
{ 
    yyval.vardec = new VarDecl(curr_line, curr_col, *yyvsp[-1].typ, Symbol(yyvsp[0].sval->getValue())); 
  }
break;
case 32:
#line 294 "parser.y"
{ 
      yyval.varlist = yyvsp[-2].varlist; 
      yyval.varlist->push_back(*yyvsp[0].vardec);
      delete(yyvsp[0].vardec);
      /*$$ = $1; */
      /*$$->add((Expr*)(new VarDecl(curr_line, curr_col, *$3, Symbol($4->getValue())))); */
    }
break;
case 33:
#line 301 "parser.y"
{ 
      yyval.varlist = new vector<VarDecl>();
      yyval.varlist->push_back(*yyvsp[0].vardec);
      delete(yyvsp[0].vardec);
      /*$$ = new VarDecl(curr_line, curr_col, *$1, Symbol($2->getValue())); */
    }
break;
case 34:
#line 311 "parser.y"
{ 
      yyval.funcdec = new FuncDecl(curr_line, curr_col, false, yyvsp[-5].typ->getTyp(), Symbol(yyvsp[-4].sval->getValue()), yyvsp[-1].exp);
      if(yyvsp[-3].varlist != NULL){
        for(size_t i = 0; i < yyvsp[-3].varlist->size(); i++){
          yyval.funcdec->addArg((*yyvsp[-3].varlist)[i]);
        }
        delete(yyvsp[-3].varlist);
      }
      /*if ($4 != NULL) $$->addArg(*$4);*/
    }
break;
case 35:
#line 325 "parser.y"
{ 
      yyval.funcdec = new FuncDecl(curr_line, curr_col, true, yyvsp[-4].typ->getTyp(), Symbol(yyvsp[-3].sval->getValue()), yyvsp[-1].exp);
      if(yyvsp[-2].varlist != NULL){
        for(size_t i = 0; i < yyvsp[-2].varlist->size(); i++){
          yyval.funcdec->addArg((*yyvsp[-2].varlist)[i]);
        }
        delete(yyvsp[-2].varlist);
      }
      /*if ($4 != NULL) $$->addArg(*$4);*/
    }
break;
case 36:
#line 339 "parser.y"
{
      yyval.numstdec = new NumStDecl(curr_line, curr_col, yyvsp[-3].typ->getTyp(), yyvsp[-1].exp);
      if(yyvsp[-2].varlst != NULL){
        for(size_t i = 0; i < yyvsp[-2].varlst->size(); i++){
          yyval.numstdec->add(get<0>((*yyvsp[-2].varlst)[i]), get<1>((*yyvsp[-2].varlst)[i]));
        }
        delete(yyvsp[-2].varlst);
      }
      /*$$->add(Symbol($4->getValue()), Symbol($6->getValue()));*/
    }
break;
case 37:
#line 352 "parser.y"
{yyval.varlst = yyvsp[-1].varlst; }
break;
case 38:
#line 353 "parser.y"
{yyval.varlst = NULL; }
break;
case 39:
#line 359 "parser.y"
{
    yyval.varlst = yyvsp[-4].varlst;
    yyval.varlst->push_back(make_tuple(Symbol(yyvsp[-2].sval->getValue()), Symbol(yyvsp[0].sval->getValue())));
  }
break;
case 40:
#line 364 "parser.y"
{ 
    yyval.varlst = new vector<tuple<Symbol, Symbol>>();
    yyval.varlst->push_back(make_tuple(Symbol(yyvsp[-2].sval->getValue()), Symbol(yyvsp[0].sval->getValue())));
  }
break;
case 41:
#line 373 "parser.y"
{ }
break;
case 42:
#line 378 "parser.y"
{
      yyval.distdec = yyvsp[-1].distdec;
      /*cout << " found distinct dec " << endl;*/
      /*$$ = new DistinctDecl(curr_line, curr_col, $2->getTyp());*/
      /*for(size_t i = 0; i < $3->size(); i++){*/
      /*  cout << "adding tuple" << endl;*/
      /*  auto strint = (*$3)[i];*/
      /*  $$->add(Symbol(get<0>(strint)), get<1>(strint));*/
      /*  cout << "added tuple" << endl;*/
      /*}*/
    }
break;
case 43:
#line 393 "parser.y"
{
        yyval.distdec = new DistinctDecl(curr_line, curr_col, yyvsp[-1].typ->getTyp());
        yyval.distdec->add(Symbol(yyvsp[0].sval->getValue()), 1);
      }
break;
case 44:
#line 398 "parser.y"
{
        yyval.distdec = new DistinctDecl(curr_line, curr_col, yyvsp[-4].typ->getTyp());
        yyval.distdec->add(Symbol(yyvsp[-3].sval->getValue()), yyvsp[-1].ival->getValue());
      }
break;
case 45:
#line 403 "parser.y"
{ 
        yyval.distdec = yyvsp[-2].distdec;
        yyval.distdec->add(Symbol(yyvsp[0].sval->getValue()), 1);
      }
break;
case 46:
#line 408 "parser.y"
{ 
        yyval.distdec = yyvsp[-5].distdec;
        yyval.distdec->add(Symbol(yyvsp[-3].sval->getValue()), yyvsp[-1].ival->getValue());
      }
break;
case 47:
#line 416 "parser.y"
{ 
        cout << "creating first tuple" << endl;
        auto idint = make_tuple(yyvsp[0].sval->getValue(), 1);
        yyval.symbintpair = &(idint); 
        cout << "created first tuple" << endl;
       }
break;
case 48:
#line 423 "parser.y"
{ 
      cout << "creating tuple" << endl;
      auto idint = make_tuple(yyvsp[-3].sval->getValue(), yyvsp[-1].ival->getValue());
      yyval.symbintpair = &(idint); 
      cout << "created tuple" << endl;
    }
break;
case 49:
#line 432 "parser.y"
{ 
      yyval.sval = new BLOGSymbol<string>(curr_line, curr_col, yyvsp[0].sval->getValue());
    }
break;
case 50:
#line 435 "parser.y"
{
      yyval.sval = new BLOGSymbol<string>(curr_line, curr_col, yyvsp[-2].sval->getValue() + "." + yyvsp[0].sval->getValue());
    }
break;
case 51:
#line 441 "parser.y"
{ yyval.exp = yyvsp[0].exp; }
break;
case 52:
#line 442 "parser.y"
{ yyval.exp = yyvsp[0].exp; }
break;
case 53:
#line 444 "parser.y"
{ yyval.exp = new IfExpr(curr_line, curr_col, yyvsp[-3].exp, yyvsp[-1].exp, yyvsp[0].exp); }
break;
case 54:
#line 446 "parser.y"
{ yyval.exp = yyvsp[-1].exp; }
break;
case 55:
#line 450 "parser.y"
{yyval.exp = yyvsp[0].exp; }
break;
case 56:
#line 451 "parser.y"
{yyval.exp = NULL; }
break;
case 57:
#line 456 "parser.y"
{ }
break;
case 58:
#line 457 "parser.y"
{ }
break;
case 59:
#line 461 "parser.y"
{yyval.exp = yyvsp[0].exp;}
break;
case 60:
#line 462 "parser.y"
{yyval.exp = yyvsp[0].exp;}
break;
case 61:
#line 463 "parser.y"
{yyval.exp = yyvsp[0].exp;}
break;
case 62:
#line 464 "parser.y"
{yyval.exp = yyvsp[0].exp;}
break;
case 63:
#line 465 "parser.y"
{yyval.exp = yyvsp[0].exp;}
break;
case 64:
#line 466 "parser.y"
{yyval.exp = yyvsp[0].mapexp;}
break;
case 65:
#line 467 "parser.y"
{ yyval.exp = yyvsp[0].exp; }
break;
case 66:
#line 468 "parser.y"
{ yyval.exp = yyvsp[0].setexp; }
break;
case 67:
#line 469 "parser.y"
{ yyval.exp = yyvsp[0].numref; }
break;
case 68:
#line 470 "parser.y"
{ yyval.exp = yyvsp[0].exp; }
break;
case 69:
#line 475 "parser.y"
{yyval.exp = new StringLiteral(curr_line, curr_col, yyvsp[0].sval->getValue()); }
break;
case 70:
#line 477 "parser.y"
{string charstr(1, yyvsp[0].chrval->getValue()); yyval.exp = new StringLiteral(curr_line, curr_col, charstr); }
break;
case 71:
#line 479 "parser.y"
{yyval.exp = new IntLiteral(curr_line, curr_col, yyvsp[0].ival->getValue()); }
break;
case 72:
#line 481 "parser.y"
{yyval.exp = new DoubleLiteral(curr_line, curr_col, yyvsp[0].dblval->getValue()); }
break;
case 73:
#line 483 "parser.y"
{yyval.exp = new BoolLiteral(curr_line, curr_col, yyvsp[0].boolval->getValue()); }
break;
case 74:
#line 485 "parser.y"
{yyval.exp = new NullLiteral(curr_line, curr_col); }
break;
case 75:
#line 490 "parser.y"
{ 
      yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::PLUS_, yyvsp[-2].exp, yyvsp[0].exp);   
    }
break;
case 76:
#line 494 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::MINUS_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 77:
#line 496 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::MUL_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 78:
#line 498 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::DIV_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 79:
#line 500 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::MOD_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 80:
#line 502 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::POWER_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 81:
#line 504 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::LT_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 82:
#line 506 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::GT_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 83:
#line 508 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::LE_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 84:
#line 510 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::GE_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 85:
#line 512 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::EQ_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 86:
#line 514 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::NEQ_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 87:
#line 516 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::AND_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 88:
#line 518 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::OR_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 89:
#line 520 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::IMPLY_, yyvsp[-2].exp, yyvsp[0].exp); }
break;
case 90:
#line 522 "parser.y"
{ yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::SUB_, yyvsp[-3].exp, yyvsp[-1].exp); }
break;
case 91:
#line 523 "parser.y"
{ yyval.exp = yyvsp[0].exp; }
break;
case 92:
#line 528 "parser.y"
{yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::NOT_, new IntLiteral(curr_line, curr_col, 0), yyvsp[0].exp); }
break;
case 93:
#line 530 "parser.y"
{yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::NOT_, NULL, yyvsp[0].exp); }
break;
case 94:
#line 532 "parser.y"
{yyval.exp = new OpExpr(curr_line, curr_col, AbsynConstant::AT_, NULL, yyvsp[0].exp); }
break;
case 95:
#line 533 "parser.y"
{yyval.exp = yyvsp[-1].exp; }
break;
case 96:
#line 538 "parser.y"
{yyval.exp = new QuantExpr(curr_line, curr_col, AbsynConstant::FORALL_, *(new VarDecl(curr_line, curr_col, *yyvsp[-2].typ, Symbol(yyvsp[-1].sval->getValue()))), yyvsp[0].exp); }
break;
case 97:
#line 540 "parser.y"
{yyval.exp = new QuantExpr(curr_line, curr_col, AbsynConstant::EXISTS_, *(new VarDecl(curr_line, curr_col, *yyvsp[-2].typ, Symbol(yyvsp[-1].sval->getValue()))), yyvsp[0].exp); }
break;
case 98:
#line 545 "parser.y"
{ 
    yyval.exp = new FuncApp(curr_line, curr_col, Symbol(yyvsp[-3].sval->getValue())); 
    if (yyvsp[-1].explst != NULL){
      for(size_t i = 0; i < yyvsp[-1].explst->size(); i++){
        yyval.exp->add((*yyvsp[-1].explst)[i]);
      }
      delete(yyvsp[-1].explst);
    }
  }
break;
case 99:
#line 558 "parser.y"
{ yyval.exp = new VarRef(curr_line, curr_col, Symbol(yyvsp[0].sval->getValue())); }
break;
case 100:
#line 563 "parser.y"
{
      yyval.exp = new DistrExpr(curr_line, curr_col, Symbol(yyvsp[-3].sval->getValue()));
      if(yyvsp[-1].explst != NULL){
        for(size_t i = 0; i < yyvsp[-1].explst->size(); i++){
          yyval.exp->add((*yyvsp[-1].explst)[i]);
        }
        delete(yyvsp[-1].explst);
      }
      /*$$->add($4);*/
      /*for(size_t i = 0; i < $4->size(); i++){*/
      /*  $$->add($4->get(i));*/
      /*} */
    }
break;
case 101:
#line 579 "parser.y"
{yyval.explst = yyvsp[0].explst;}
break;
case 102:
#line 580 "parser.y"
{yyval.explst = NULL; }
break;
case 103:
#line 585 "parser.y"
{ yyval.explst = yyvsp[-2].explst;
      yyval.explst->push_back(yyvsp[0].exp);
    }
break;
case 104:
#line 589 "parser.y"
{ 
      yyval.explst = new vector<Expr*>();
      yyval.explst->push_back(yyvsp[0].exp);
    }
break;
case 105:
#line 597 "parser.y"
{ }
break;
case 106:
#line 598 "parser.y"
{ }
break;
case 107:
#line 603 "parser.y"
{ }
break;
case 108:
#line 604 "parser.y"
{ }
break;
case 109:
#line 608 "parser.y"
{ 
    /*$$ = $2; */
    yyval.mapexp = new MapExpr(curr_line, curr_col);
    for (size_t i = 0; i < yyvsp[-1].exptuplst->size(); i++){
      yyval.mapexp->addMap(get<0>((*yyvsp[-1].exptuplst)[i]), get<1>((*yyvsp[-1].exptuplst)[i]));
    }
    delete(yyvsp[-1].exptuplst);
    
  }
break;
case 110:
#line 622 "parser.y"
{ 
      yyval.exptuplst = yyvsp[-4].exptuplst;
      yyval.exptuplst->push_back(make_tuple(yyvsp[-2].exp, yyvsp[0].exp));
      /*$$ = $1;*/
      /*$$->addMap($3, $5);*/
    }
break;
case 111:
#line 629 "parser.y"
{ 
      yyval.exptuplst = new vector<tuple<Expr*, Expr*>>();
      yyval.exptuplst->push_back(make_tuple(yyvsp[-2].exp, yyvsp[0].exp));
      /*$$ = new MapExpr(curr_line, curr_col);*/
      /*$$->addMap($1, $3);*/
    }
break;
case 112:
#line 639 "parser.y"
{yyval.numref = new NumStRef(curr_line, curr_col, (Expr*)yyvsp[0].setexp); }
break;
case 113:
#line 640 "parser.y"
{ 
      VarDecl* var = new VarDecl(curr_line, curr_col, *yyvsp[0].typ, Symbol("a"));
      yyval.numref = new NumStRef(curr_line, curr_col, new CondSet(curr_line, curr_col, *var, new BoolLiteral(curr_line, curr_col, true)));
  }
break;
case 114:
#line 647 "parser.y"
{ yyval.origdec = new OriginDecl(curr_line, curr_col, yyvsp[-5].typ->getTyp(), Symbol(yyvsp[-4].sval->getValue()), yyvsp[-2].typ->getTyp());  }
break;
case 115:
#line 651 "parser.y"
{yyval.setexp = yyvsp[0].setexp; }
break;
case 116:
#line 652 "parser.y"
{yyval.setexp = yyvsp[0].setexp; }
break;
case 117:
#line 658 "parser.y"
{
      yyval.setexp = new ListSet(curr_line, curr_col);
      for(size_t i = 0; i < yyvsp[-1].explst->size(); i++){
        yyval.setexp->add((*yyvsp[-1].explst)[i]);
      }
      delete(yyvsp[-1].explst);
      /*$$ = new SetExpr(curr_line, curr_col); */
      /*$$->add($2);*/
    }
break;
case 118:
#line 672 "parser.y"
{ 
      yyval.setexp = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *yyvsp[-4].typ, Symbol(yyvsp[-3].sval->getValue())), yyvsp[-1].exp);
      /*$$ = new CondSet(curr_line, curr_col, NULL);*/
      /*$$->add($5);*/
    }
break;
case 119:
#line 678 "parser.y"
{ 
      yyval.setexp = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *yyvsp[-2].typ, Symbol(yyvsp[-1].sval->getValue())));
    }
break;
case 120:
#line 687 "parser.y"
{ }
break;
case 121:
#line 689 "parser.y"
{ }
break;
case 122:
#line 695 "parser.y"
{yyval.stmt = yyvsp[-1].stmt; }
break;
case 123:
#line 698 "parser.y"
{yyval.stmt = yyvsp[0].stmt; }
break;
case 124:
#line 699 "parser.y"
{yyval.stmt = yyvsp[0].stmt; }
break;
case 125:
#line 705 "parser.y"
{
    yyval.stmt = new Evidence(curr_line, curr_col, yyvsp[-2].exp, yyvsp[0].exp); 
  }
break;
case 126:
#line 713 "parser.y"
{ yyval.stmt = new Evidence(curr_line, curr_col, yyvsp[-2].setexp, yyvsp[0].setexp); }
break;
case 127:
#line 717 "parser.y"
{yyval.stmt = yyvsp[-1].stmt; }
break;
case 128:
#line 721 "parser.y"
{ yyval.stmt = new Query(curr_line, curr_col, yyvsp[0].exp); }
break;
#line 1558 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
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
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
