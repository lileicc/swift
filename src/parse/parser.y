%{
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

// stuff from flex that bison needs to know about: 
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int yylineno;
extern "C" int curr_line;
extern "C" int curr_col;
 
void yyerror(const char *s);
BlogProgram *blog = new BlogProgram(0,0);

int main() {
  // open a file handle to a particular file:
  FILE *myfile = fopen("input.in", "r");
  // make sure it is valid:
  if (!myfile) {
    cout << "I can't open input.in" << endl;
    return -1;
  }
  // set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  // parse through the input until there is no more:
  do {
    yyparse();
  } while (!feof(yyin));
  FILE *output = fopen("output.out", "w");
  //cout << blog->size() << endl;
  //NumStDecl* st = (NumStDecl*)(blog->get(0));
  //Symbol o = st->getArgOrigin(0);
  //cout << "current val: " << o.getValue() << endl;
  //Evidence* t = (Evidence*)(blog->get(0));
  //cout << "assigned" << endl;
  //NumStRef* left = (NumStRef*)(t->getLeft());
  //cout << "expression extracted" << endl;
  
  blog->print(output, 0);
  return 0;
  
  
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
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token ELSE IF THEN
%token TYPE RANDOM FIXED ORIGIN DISTINCT QUERY OBS PARAM LIST MAP DISTRIBUTION
%token EXISTS FORALL
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
%token AT
%token PLUS MULT DIV MOD POWER MINUS
%token LST LT GT LEQ GEQ
%token EQEQ NEQ
%token EQ
%token DISTRIB
%token NOT AND OR DOUBLERIGHTARROW
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
%type <numref> number_expr;
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
%nonassoc EQ DISTRIB
%right RIGHTARROW
%left DOUBLERIGHTARROW
%left AND OR
%left NOT
%nonassoc LT GT LEQ GEQ EQEQ NEQ
%left PLUS MINUS
%left MULT DIV MOD POWER
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
  | array_type { $$ = $1; }
  | map_type { $$ = $1; }
  ;

name_type:
  ID { $$ = new Ty(curr_line, curr_col, Symbol($1->getValue())); }
  ;

//TODO: Not sure what type this should be
list_type:
  LIST LT ID GT{ $$ = new Ty(curr_line, curr_col, Symbol($3->getValue())); }
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
  MAP LT type COMMA type GT { $$ = $3; }
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
    FIXED type ID opt_parenthesized_type_var_lst EQ expression SEMI
    { 
      $$ = new FuncDecl(curr_line, curr_col, false, $2->getTyp(), Symbol($3->getValue()), $6);
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
      $$ = new FuncDecl(curr_line, curr_col, true, $2->getTyp(), Symbol($3->getValue()), $5);
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
  origin_var_list COMMA ID EQ ID
  {
    $$ = $1;
    $$->push_back(make_tuple(Symbol($3->getValue()), Symbol($5->getValue())));
  }
  | ID EQ ID
  { 
    $$ = new vector<tuple<Symbol, Symbol>>();
    $$->push_back(make_tuple(Symbol($1->getValue()), Symbol($3->getValue())));
  }
  ;

//TODO: DistributionDec/ClassName
distribution_decl:
    DISTRIBUTION ID EQ class_name LPAREN opt_expression_list RPAREN SEMI
    { }
    ;
    
distinct_decl:
    id_or_subid_list SEMI
    {
      $$ = $1;
      //cout << " found distinct dec " << endl;
      //$$ = new DistinctDecl(curr_line, curr_col, $2->getTyp());
      //for(size_t i = 0; i < $3->size(); i++){
      //  cout << "adding tuple" << endl;
      //  auto strint = (*$3)[i];
      //  $$->add(Symbol(get<0>(strint)), get<1>(strint));
      //  cout << "added tuple" << endl;
      //}
    }
    ;

id_or_subid_list:
    DISTINCT name_type ID
      {
        $$ = new DistinctDecl(curr_line, curr_col, $2->getTyp());
        $$->add(Symbol($3->getValue()), 1);
      }
  | DISTINCT name_type ID LBRACKET INT_LITERAL RBRACKET
      {
        $$ = new DistinctDecl(curr_line, curr_col, $2->getTyp());
        $$->add(Symbol($3->getValue()), $5->getValue());
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
        cout << "creating first tuple" << endl;
        auto idint = make_tuple($1->getValue(), 1);
        $$ = &(idint); 
        cout << "created first tuple" << endl;
       }
  | ID LBRACKET INT_LITERAL RBRACKET
    { 
      cout << "creating tuple" << endl;
      auto idint = make_tuple($1->getValue(), $3->getValue());
      $$ = &(idint); 
      cout << "created tuple" << endl;
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
    EQ expression { $$ = $2; }
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
    expression PLUS expression
    { 
      $$ = new OpExpr(curr_line, curr_col, AbsynConstant::PLUS_, $1, $3);   
    }
  | expression MINUS expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::MINUS_, $1, $3); }
  | expression MULT expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::MUL_, $1, $3); }
  | expression DIV expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::DIV_, $1, $3); }
  | expression MOD expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::MOD_, $1, $3); }
  | expression POWER expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::POWER_, $1, $3); }
  | expression LT expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::LT_, $1, $3); }
  | expression GT expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::GT_, $1, $3); }
  | expression LEQ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::LE_, $1, $3); }
  | expression GEQ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::GE_, $1, $3); }
  | expression EQEQ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::EQ_, $1, $3); }
  | expression NEQ expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::NEQ_, $1, $3); }
  | expression AND expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::AND_, $1, $3); }
  | expression OR expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::OR_, $1, $3); }
  | expression DOUBLERIGHTARROW expression
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::IMPLY_, $1, $3); }
  | expression LBRACKET expression RBRACKET
    { $$ = new OpExpr(curr_line, curr_col, AbsynConstant::SUB_, $1, $3); }
  | unary_operation_expr { $$ = $1; }
  ;
  
unary_operation_expr:
    MINUS expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::NOT_, new IntLiteral(curr_line, curr_col, 0), $2); }
  | NOT expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::NOT_, NULL, $2); } 
  | AT expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::AT_, NULL, $2); } 
  | LPAREN expression RPAREN {$$ = $2; }
  ;
  
quantified_formula:
    FORALL type ID expression
    {$$ = new QuantExpr(curr_line, curr_col, AbsynConstant::FORALL_, *(new VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue()))), $4); }
  | EXISTS type ID expression
    {$$ = new QuantExpr(curr_line, curr_col, AbsynConstant::EXISTS_, *(new VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue()))), $4); }
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
  
//TODO: NumberExpr  
number_expr:
    NUMSIGN set_expr {$$ = new NumStRef(curr_line, curr_col, (Expr*)$2); }
  | NUMSIGN type { 
      VarDecl* var = new VarDecl(curr_line, curr_col, *$2, Symbol("a"));
      $$ = new NumStRef(curr_line, curr_col, new CondSet(curr_line, curr_col, *var, new BoolLiteral(curr_line, curr_col, true)));
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
  expression EQ expression
  {
    $$ = new Evidence(curr_line, curr_col, $1, $3); 
  }
  ;

//TODO: No SymbolEvidence?  
symbol_evidence:
  implicit_set EQ explicit_set
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