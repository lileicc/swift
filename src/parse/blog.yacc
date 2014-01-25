%{
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
%}

%union {
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
  vector<VarDecl>* varlist;
  vector<tuple<Expr*, Expr*>>* exptuplst;
  vector<Expr*>* explst;
  vector<tuple<Symbol, Symbol>>* varlst;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token ELSE IF THEN
%token TYPE RANDOM FIXED ORIGIN DISTINCT QUERY OBS PARAM LIST MAP DISTRIBUTION
%token EXISTS_ FORALL_
%token FOR
%token NULLITY
%token <ival> INT_LITERAL 
%token <dblval> DOUBLE_LITERAL
%token <boolval> BOOLEAN_LITERAL
%token <chrval> CHAR_LITERAL
%token <sval> STRING_LITERAL
%token <sval> ID
%token PARFACTOR FACTOR
%token ERROR ELSEIF
%token AT_
%token PLUS_ MULT_ DIV_ MOD_ POWER_ MINUS_
%token LST LT_ GT_ LEQ_ GEQ_
%token EQEQ_ NEQ_
%token EQ_
%token DISTRIB
%token NOT_ AND_ OR_ DOUBLERIGHTARROW
%token COMMA SEMI COLON DOT NUMSIGN RIGHTARROW
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

%type <stmt> statement, declaration_stmt, type_decl, distribution_decl, parameter_decl,
  evidence_stmt, query_stmt;
%type <numstdec> number_stmt;
%type <origdec> origin_func_decl;
%type <funcdec> fixed_func_decl, rand_func_decl;
%type <distdec> distinct_decl;
%type <stmt> evidence, value_evidence, symbol_evidence, query;
%type <exp> expression, literal, operation_expr, unary_operation_expr,
  quantified_formula, distribution_expr,
  function_call, list_construct_expression, symbol_expr,
  elseif_list;
%type <cardexp> number_expr;
%type <mapexp> map_construct_expression;
%type <exp> dependency_statement_body;
%type <setexp> set_expr;
%type <setexp> explicit_set;
%type <setexp> implicit_set;
%type <setexp> tuple_set;
%type <explst> semi_colon_separated_expression_list,
  opt_expression_list, expression_list;
%type <exptuplst> expression_pair_list;
%type <typ> type, array_type, list_type, map_type, name_type;
//%type <ast> opt_parenthesized_type_lst, type_lst // Not Used
%type <varlist> type_var_lst;
%type <varlist> opt_parenthesized_type_var_lst;
%type <varlst> opt_parenthesized_origin_var_list,
  origin_var_list;
%type <symbintpair> id_or_subid;
%type <distdec> id_or_subid_list;
%type <vardec> var_decl;
%type <sval> class_name;
%type <i> dims;

%left ELSE
%nonassoc EQ_ DISTRIB
%right RIGHTARROW
%left DOUBLERIGHTARROW
%left AND_ OR_
%left NOT_
%nonassoc LT_ GT_ LEQ_ GEQ_ EQEQ_ NEQ_
%left PLUS_ MINUS_
%left MULT_ DIV_ MOD_ POWER_
%left LBRACKET

%%
program:
  opt_statement_lst
  ;
  
opt_statement_lst:
    //Nothing
  | statement_lst
  ;

statement_lst:
  statement_lst statement 
  {
    if($2 != NULL){
      blog->add($2);
    }
  }
  | statement { blog->add($1); }
  ;

statement:
    declaration_stmt { $$ = $1; }
  | evidence_stmt { $$ = $1; }
  | query_stmt { $$ = $1; }
  ;


declaration_stmt:
    type_decl { $$ = $1; }
  | fixed_func_decl { $$ = $1; }
  | rand_func_decl { $$ = $1; }
  | origin_func_decl { $$ = $1; }
  | number_stmt {$$ = $1; }
  | distinct_decl  { $$ = $1; }
  | parameter_decl { $$ = $1; }
  | distribution_decl { $$ = $1; }
  ;
  
type_decl:
  TYPE ID SEMI
  { $$ = new TypDecl(curr_line, curr_col, Symbol($2->getValue())); }
  ;

type:
    name_type { $$ = $1; }
  | list_type { $$ = $1; }
  | map_type { $$ = $1; }
  ;

name_type:
  ID { $$ = new Ty(curr_line, curr_col, Symbol($1->getValue())); }
  ;

//TODO: Not sure what type this should be
list_type:
  LIST LT_ ID GT_{ $$ = new Ty(curr_line, curr_col, Symbol($3->getValue())); }
  ;

//TODO: Not sure what type this should be
array_type:
  ID dims { $$ = new Ty(curr_line, curr_col, Symbol($1->getValue())); }
  ;

dims:
    LBRACKET RBRACKET { $$ = 1; }
  | LBRACKET RBRACKET dims { $$ = $3 + 1; }
  ;
  
//TODO: Not sure what type this should be
map_type:
  MAP LT_ type COMMA type GT_ { $$ = $3; }
  ;

opt_parenthesized_type_var_lst:
    { $$ = NULL; }
  | LPAREN RPAREN {$$ = NULL; }
  | LPAREN type_var_lst RPAREN { $$ = $2; }
  ;

var_decl:
  type ID{ 
    $$ = new VarDecl(curr_line, curr_col, *$1, Symbol($2->getValue())); 
  }
  ;
  
type_var_lst:
    type_var_lst COMMA var_decl{ 
      $$ = $1; 
      $$->push_back(*$3);
      delete($3);
      //$$ = $1; 
      //$$->add((Expr*)(new VarDecl(curr_line, curr_col, *$3, Symbol($4->getValue())))); 
    }
  | var_decl { 
      $$ = new vector<VarDecl>();
      $$->push_back(*$1);
      delete($1);
      //$$ = new VarDecl(curr_line, curr_col, *$1, Symbol($2->getValue())); 
    }
  ;

fixed_func_decl:
    FIXED type ID opt_parenthesized_type_var_lst EQ_ expression SEMI
    { 
      $$ = new FuncDecl(curr_line, curr_col, false, *($2), Symbol($3->getValue()), $6);
      if($4 != NULL){
        for(size_t i = 0; i < $4->size(); i++){
          $$->addArg((*$4)[i]);
        }
        delete($4);
      }
      //if ($4 != NULL) $$->addArg(*$4);
    }
    ;

rand_func_decl:
    RANDOM type ID opt_parenthesized_type_var_lst dependency_statement_body SEMI
    { 
      $$ = new FuncDecl(curr_line, curr_col, true, *($2), Symbol($3->getValue()), $5);
      if($4 != NULL){
        for(size_t i = 0; i < $4->size(); i++){
          $$->addArg((*$4)[i]);
        }
        delete($4);
      }
      //if ($4 != NULL) $$->addArg(*$4);
    }
    ;
    
number_stmt:
    NUMSIGN name_type opt_parenthesized_origin_var_list dependency_statement_body SEMI
    {
      $$ = new NumStDecl(curr_line, curr_col, $2->getTyp(), $4);
      if($3 != NULL){
        for(size_t i = 0; i < $3->size(); i++){
          $$->add(get<0>((*$3)[i]), get<1>((*$3)[i]));
        }
        delete($3);
      }
      //$$->add(Symbol($4->getValue()), Symbol($6->getValue()));
    }
    ;
    
opt_parenthesized_origin_var_list:
    LPAREN origin_var_list RPAREN {$$ = $2; }
  | {$$ = NULL; }
  ;

//TODO: memory management 
origin_var_list:
  origin_var_list COMMA ID EQ_ ID
  {
    $$ = $1;
    $$->push_back(make_tuple(Symbol($3->getValue()), Symbol($5->getValue())));
  }
  | ID EQ_ ID
  { 
    $$ = new vector<tuple<Symbol, Symbol>>();
    $$->push_back(make_tuple(Symbol($1->getValue()), Symbol($3->getValue())));
  }
  ;

//TODO: DistributionDec/ClassName
distribution_decl:
    DISTRIBUTION ID EQ_ class_name LPAREN opt_expression_list RPAREN SEMI
    { }
    ;
    
distinct_decl:
    DISTINCT id_or_subid_list SEMI
    {
      $$ = $2;
    }
    ;

id_or_subid_list:
    name_type ID
      {
        $$ = new DistinctDecl(curr_line, curr_col, $1->getTyp());
        $$->add(Symbol($2->getValue()), 1);
      }
  | name_type ID LBRACKET INT_LITERAL RBRACKET
      {
        $$ = new DistinctDecl(curr_line, curr_col, $1->getTyp());
        $$->add(Symbol($2->getValue()), $4->getValue());
      }
  | id_or_subid_list COMMA ID
      { 
        $$ = $1;
        $$->add(Symbol($3->getValue()), 1);
      }
  | id_or_subid_list COMMA ID LBRACKET INT_LITERAL RBRACKET
      { 
        $$ = $1;
        $$->add(Symbol($3->getValue()), $5->getValue());
      }
  ;

    
id_or_subid:
    ID { 
        auto idint = make_tuple($1->getValue(), 1);
        $$ = &(idint); 
       }
  | ID LBRACKET INT_LITERAL RBRACKET
    { 
      auto idint = make_tuple($1->getValue(), $3->getValue());
      $$ = &(idint); 
    }
  ;      
  
class_name:
    ID { 
      $$ = new BLOGSymbol<string>(curr_line, curr_col, $1->getValue());
    }
  | ID DOT class_name {
      $$ = new BLOGSymbol<string>(curr_line, curr_col, $1->getValue() + "." + $3->getValue());
    }
  ;
  
dependency_statement_body:
    EQ_ expression { $$ = $2; }
  | distribution_expr { $$ = $1; }
  | IF expression THEN dependency_statement_body elseif_list
  { $$ = new IfExpr(curr_line, curr_col, $2, $4, $5); }
  | LBRACE dependency_statement_body RBRACE
  { $$ = $2; }
  ;
  
elseif_list:
    ELSE dependency_statement_body {$$ = $2; }
  | {$$ = NULL; }
  ;
  
//TODO: ParameterDec
parameter_decl:
    PARAM type ID SEMI { }
  | PARAM type ID COLON expression SEMI { }
  ;
  
expression:
    operation_expr {$$ = $1;}
  | distribution_expr {$$ = $1;}
  | literal {$$ = $1;}
  | function_call {$$ = $1;}
  | list_construct_expression {$$ = $1;}
  | map_construct_expression {$$ = $1;}
  | quantified_formula { $$ = $1; }
  | set_expr { $$ = $1; }
  | number_expr { $$ = $1; }
  | symbol_expr { $$ = $1; }
  ;
  
literal:
    STRING_LITERAL 
    {$$ = new StringLiteral(curr_line, curr_col, $1->getValue()); }
  | CHAR_LITERAL
    {string charstr(1, $1->getValue()); $$ = new StringLiteral(curr_line, curr_col, charstr); }
  | INT_LITERAL
    {$$ = new IntLiteral(curr_line, curr_col, $1->getValue()); }
  | DOUBLE_LITERAL
    {$$ = new DoubleLiteral(curr_line, curr_col, $1->getValue()); }
  | BOOLEAN_LITERAL
    {$$ = new BoolLiteral(curr_line, curr_col, $1->getValue()); }
  | NULLITY
    {$$ = new NullLiteral(curr_line, curr_col); }
  ;
  
operation_expr:
    expression PLUS_ expression
    { 
      $$ = new OpExpr(curr_line, curr_col, AbsynConstant::PLUS, $1, $3);   
    }
  | expression MINUS_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::MINUS, $1, $3); }
  | expression MULT_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::MUL, $1, $3); }
  | expression DIV_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::DIV, $1, $3); }
  | expression MOD_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::MOD, $1, $3); }
  | expression POWER_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::POWER, $1, $3); }
  | expression LT_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::LT, $1, $3); }
  | expression GT_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::GT, $1, $3); }
  | expression LEQ_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::LE, $1, $3); }
  | expression GEQ_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::GE, $1, $3); }
  | expression EQEQ_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::EQ, $1, $3); }
  | expression NEQ_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::NEQ, $1, $3); }
  | expression AND_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::AND, $1, $3); }
  | expression OR_ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::OR, $1, $3); }
  | expression DOUBLERIGHTARROW expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::IMPLY, $1, $3); }
  | expression LBRACKET expression RBRACKET
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, $1, $3); }
  | unary_operation_expr { $$ = $1; }
  ;
  
unary_operation_expr:
    MINUS_ expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::SUB, new IntLiteral(curr_line, curr_col, 0), $2); }
  | NOT_ expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::NOT, NULL, $2); } 
  | AT_ expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::AT, NULL, $2); } 
  | LPAREN expression RPAREN {$$ = $2; }
  ;
  
quantified_formula:
    FORALL_ type ID expression
    {$$ = new QuantExpr(curr_line, curr_col, AbsynConstant::FORALL, *(new VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue()))), $4); }
  | EXISTS_ type ID expression
    {$$ = new QuantExpr(curr_line, curr_col, AbsynConstant::EXISTS, *(new VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue()))), $4); }
  ;
  
function_call:
  class_name LPAREN opt_expression_list RPAREN 
  { 
    $$ = new FuncApp(curr_line, curr_col, Symbol($1->getValue())); 
    if ($3 != NULL){
      for(size_t i = 0; i < $3->size(); i++){
        $$->add((*$3)[i]);
      }
      delete($3);
    }
  }
  ;
  
//TODO: SymbolExpr
symbol_expr:
  ID { $$ = new VarRef(curr_line, curr_col, Symbol($1->getValue())); }
  ;
  
distribution_expr:
    DISTRIB class_name LPAREN opt_expression_list RPAREN
    {
      $$ = new DistrExpr(curr_line, curr_col, Symbol($2->getValue()));
      if($4 != NULL){
        for(size_t i = 0; i < $4->size(); i++){
          $$->add((*$4)[i]);
        }
        delete($4);
      }
      //$$->add($4);
      //for(size_t i = 0; i < $4->size(); i++){
      //  $$->add($4->get(i));
      //} 
    }
  ;
  
opt_expression_list:
    expression_list {$$ = $1;}
  | {$$ = NULL; }
  ;

expression_list:
    expression_list COMMA expression
    { $$ = $1;
      $$->push_back($3);
    }
  | expression 
    { 
      $$ = new vector<Expr*>();
      $$->push_back($1);
    }
  ;
  
//TODO: ExprList  
list_construct_expression:
    LBRACKET opt_expression_list RBRACKET { }
  | LBRACKET semi_colon_separated_expression_list RBRACKET { }
  ;
  
//TODO: ExprList  
semi_colon_separated_expression_list:
    expression_list SEMI semi_colon_separated_expression_list { }
  | expression_list SEMI expression_list { }
  ;
  
map_construct_expression:
  LBRACE expression_pair_list RBRACE { 
    //$$ = $2; 
    $$ = new MapExpr(curr_line, curr_col);
    for (size_t i = 0; i < $2->size(); i++){
      $$->addMap(get<0>((*$2)[i]), get<1>((*$2)[i]));
    }
    delete($2);
    
  }
  ;
  
//TODO: ExprTupleList  
expression_pair_list:
    expression_pair_list COMMA expression RIGHTARROW expression
    { 
      $$ = $1;
      $$->push_back(make_tuple($3, $5));
      //$$ = $1;
      //$$->addMap($3, $5);
    }
  | expression RIGHTARROW expression 
    { 
      $$ = new vector<tuple<Expr*, Expr*>>();
      $$->push_back(make_tuple($1, $3));
      //$$ = new MapExpr(curr_line, curr_col);
      //$$->addMap($1, $3);
    }
  ;

number_expr:
    NUMSIGN set_expr {$$ = new CardinalityExpr(curr_line, curr_col, (Expr*)$2); }
  | NUMSIGN type { 
      VarDecl* var = new VarDecl(curr_line, curr_col, *$2, Symbol("a"));
      $$ = new CardinalityExpr(curr_line, curr_col, new CondSet(curr_line, curr_col, *var, new BoolLiteral(curr_line, curr_col, true)));
  }
  
origin_func_decl:
  ORIGIN type ID LPAREN type RPAREN SEMI
  { $$ = new OriginDecl(curr_line, curr_col, $2->getTyp(), Symbol($3->getValue()), $5->getTyp());  }
  ;

set_expr:
    explicit_set {$$ = $1; }
  | implicit_set {$$ = $1; }
  ;
 
//TODO: ExplicitSetExpr
explicit_set:
    LBRACE opt_expression_list RBRACE
    {
      $$ = new ListSet(curr_line, curr_col);
      for(size_t i = 0; i < $2->size(); i++){
        $$->add((*$2)[i]);
      }
      delete($2);
      //$$ = new SetExpr(curr_line, curr_col); 
      //$$->add($2);
    }
    ;
    
//TODO: ImplicitSetExpr  
implicit_set:
    LBRACE type ID COLON expression RBRACE
    { 
      $$ = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue())), $5);
      //$$ = new CondSet(curr_line, curr_col, NULL);
      //$$->add($5);
    }
    | LBRACE type ID RBRACE
    { 
      $$ = new CondSet(curr_line, curr_col, VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue())));
    }
    ;
  
  
//TODO: TupleSetExpr
tuple_set:
    LBRACE expression_list FOR type_var_lst COLON expression RBRACE
  { }
  | LBRACE expression_list FOR type_var_lst RBRACE
  { }
  ;
  
  
  
evidence_stmt:
  OBS evidence SEMI {$$ = $2; }
  
evidence:
    symbol_evidence {$$ = $1; }
  | value_evidence {$$ = $1; }
  ;
  
//TODO: No ValueEvidence?  
value_evidence:
  expression EQ_ expression
  {
    $$ = new Evidence(curr_line, curr_col, $1, $3); 
  }
  ;

//TODO: No SymbolEvidence?  
symbol_evidence:
  implicit_set EQ_ explicit_set
  { $$ = new Evidence(curr_line, curr_col, $1, $3); }
  ;

query_stmt:
  QUERY query SEMI {$$ = $2; }
  ; 
  
query:
  expression { $$ = new Query(curr_line, curr_col, $1); }
  ;
  
%%



void yyerror(const char *s) {
  cout << "Parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}