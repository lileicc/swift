
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 226 "parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


