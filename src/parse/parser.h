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
#define EXTERN 271
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
