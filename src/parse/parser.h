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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#include "BLOGSymbol.h"
#include <vector>
#include <string>
#include <tuple>
using namespace std;
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
extern YYSTYPE yylval;
