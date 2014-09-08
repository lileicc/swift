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
#define CASE 271
#define IN 272
#define EXISTS_ 273
#define FORALL_ 274
#define FOR 275
#define NULLITY 276
#define INT_LITERAL 277
#define DOUBLE_LITERAL 278
#define BOOLEAN_LITERAL 279
#define CHAR_LITERAL 280
#define STRING_LITERAL 281
#define ID 282
#define PARFACTOR 283
#define FACTOR 284
#define ERROR 285
#define ELSEIF 286
#define AT_ 287
#define PLUS_ 288
#define MULT_ 289
#define DIV_ 290
#define MOD_ 291
#define POWER_ 292
#define MINUS_ 293
#define UMINUS 294
#define LST 295
#define LT_ 296
#define GT_ 297
#define LEQ_ 298
#define GEQ_ 299
#define EQEQ_ 300
#define NEQ_ 301
#define EQ_ 302
#define DISTRIB 303
#define NOT_ 304
#define AND_ 305
#define OR_ 306
#define DOUBLERIGHTARROW 307
#define COMMA 308
#define SEMI 309
#define COLON 310
#define DOT 311
#define NUMSIGN 312
#define RIGHTARROW 313
#define LPAREN 314
#define RPAREN 315
#define LBRACE 316
#define RBRACE 317
#define LBRACKET 318
#define RBRACKET 319
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
