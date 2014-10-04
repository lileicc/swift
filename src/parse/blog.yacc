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
  void *compexp[3];
  void *pair[2];
  vector<VarDecl>* varlist;
  vector<tuple<Expr*, Expr*>>* exptuplst;
  vector<Expr*>* explst;
  vector<tuple<Symbol, Symbol>>* varlst;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token ELSE IF THEN
%token TYPE RANDOM FIXED ORIGIN DISTINCT QUERY OBS PARAM LIST MAP DISTRIBUTION CASE IN
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
%token PLUS_ MULT_ DIV_ MOD_ POWER_ MINUS_ UMINUS
%token LST LT_ GT_ LEQ_ GEQ_
%token EQEQ_ NEQ_
%token EQ_
%token DISTRIB
%token NOT_ AND_ OR_ DOUBLERIGHTARROW
%token COMMA SEMI COLON DOT NUMSIGN RIGHTARROW
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

%type <stmt> statement declaration_stmt type_decl distribution_decl parameter_decl
  evidence_stmt query_stmt;
%type <numstdec> number_stmt;
%type <origdec> origin_func_decl;
%type <funcdec> fixed_func_decl rand_func_decl;
%type <distdec> distinct_decl;
%type <stmt> evidence value_evidence;
%type <exp> expression literal operation_expr unary_operation_expr
  quantified_formula function_call list_expr
  if_expr case_expr;
%type <compexp> comprehension_expr;
%type <cardexp> number_expr;
%type <mapexp> map_construct_expression;
%type <exp> dependency_statement_body;
%type <setexp> set_expr;
%type <setexp> explicit_set;
%type <setexp> tuple_set;
%type <explst> semi_colon_separated_expression_list
  opt_expression_list expression_list;
%type <exptuplst> expression_pair_list;
%type <typ> type, array_type;
//%type <ast> opt_parenthesized_type_lst, type_lst // Not Used
%type <varlist> type_var_lst;
%type <varlist> opt_parenthesized_type_var_lst;
%type <varlst> opt_parenthesized_origin_var_list
  origin_var_list;
%type <symbintpair> id_or_subid;
%type <symbintvect> id_or_subid_list;
%type <vardec> var_decl;
%type <sval> refer_name, array_type_or_sub;

%left THEN EXISTS_ FORALL_
%nonassoc EQ_ DISTRIB
%left SEMI
%left ELSE
%left DOUBLERIGHTARROW
%left AND_ OR_
%nonassoc LT_ GT_ LEQ_ GEQ_ EQEQ_ NEQ_
%left PLUS_ MINUS_
%left MULT_ DIV_ MOD_ POWER_
%left UMINUS
%left NOT_ AT_
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
  statement_lst statement SEMI
  {
    if($2 != NULL){
      blog->add($2);
    }
  }
  | statement SEMI { blog->add($1); }
  | statement_lst statement
  {
    yyerror("missing ; after statement");
  }
  | statement {
    yyerror("missing ; after statement");
  }
  ;

statement:
    declaration_stmt { $$ = $1; }
  | evidence_stmt { $$ = $1; }
  | query_stmt { $$ = $1; }
  | error{
    yyerror("incorrect statement");
  }
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
  TYPE ID
  { $$ = new TypDecl(curr_line, curr_col, Symbol($2->getValue())); }
  | TYPE error
  {
    yyerror("invalid type declaration");
  }
  ;

type:
    refer_name { $$ = new Ty(curr_line, curr_col, Symbol($1->getValue())); }
  | array_type { $$ = $1; }
  ;

array_type_or_sub : refer_name LBRACKET
    { $$ = $1; }
;

array_type : array_type_or_sub RBRACKET
    { $$ = new Ty(curr_line, curr_col, Symbol($1->getValue()), 1); }
  | array_type LBRACKET RBRACKET
    { $1->setDim($1->getDim() + 1);
      $$ = $1; }
  ;

opt_parenthesized_type_var_lst:
    { $$ = NULL; }
  | LPAREN RPAREN {$$ = NULL; }
  | LPAREN type_var_lst RPAREN { $$ = $2; }
  | type_var_lst {
    yyerror("missing parentheses");
  }
  ;

var_decl:
  type ID{ 
    $$ = new VarDecl(curr_line, curr_col, *$1, Symbol($2->getValue())); 
  }
  ;

extra_commas:
  COMMA COMMA
| extra_commas COMMA
  
type_var_lst:
    type_var_lst COMMA var_decl{ 
      $$ = $1; 
      $$->push_back(*$3);
      delete($3);
    }
  | var_decl { 
      $$ = new vector<VarDecl>();
      $$->push_back(*$1);
      delete($1);
    }
  | type_var_lst extra_commas var_decl {
    yyerror("extra commas in type variable list");
  }
  | type_var_lst var_decl {
    yyerror("missing commas");
  }
  | type_var_lst COMMA error
  {
    yyerror("incorrect variable declaration");
  }
  ;

fixed_func_decl:
    FIXED type ID opt_parenthesized_type_var_lst EQ_ expression
    { 
      $$ = new FuncDecl(curr_line, curr_col, false, *($2), Symbol($3->getValue()), $6);
      if($4 != NULL){
        for(size_t i = 0; i < $4->size(); i++){
          $$->addArg((*$4)[i]);
        }
        delete($4);
      }
    }
  | FIXED error
  {
    yyerror("error in fixed function declaration");
  }
    ;

rand_func_decl:
    RANDOM type ID opt_parenthesized_type_var_lst dependency_statement_body
    { 
      $$ = new FuncDecl(curr_line, curr_col, true, *($2), Symbol($3->getValue()), $5);
      if($4 != NULL){
        for(size_t i = 0; i < $4->size(); i++){
          $$->addArg((*$4)[i]);
        }
        delete($4);
      }
    }
    | RANDOM error dependency_statement_body
    {
      yyerror("incorrect function header, return type, or function name");
    }
    | RANDOM error
    {
      yyerror("error in random function declaration");
    }
    ;
    
number_stmt:
    NUMSIGN refer_name opt_parenthesized_origin_var_list dependency_statement_body
    {
      $$ = new NumStDecl(curr_line, curr_col, Symbol($2->getValue()), $4);
      if($3 != NULL){
        for(size_t i = 0; i < $3->size(); i++){
          $$->add(get<0>((*$3)[i]), get<1>((*$3)[i]));
        }
        delete($3);
      }
      //$$->add(Symbol($4->getValue()), Symbol($6->getValue()));
    }
  | NUMSIGN opt_parenthesized_origin_var_list dependency_statement_body
  {
    yyerror("missing type name in number statement");
  }
  | NUMSIGN refer_name opt_parenthesized_origin_var_list DISTRIB error
  {
    yyerror("missing body in number statement");
  }
  | NUMSIGN refer_name error
  {
    yyerror("missing body in number statement");
  }
  | NUMSIGN error
  {
    yyerror("error in number statement");
  }
    ;
    
opt_parenthesized_origin_var_list:
    LPAREN origin_var_list RPAREN {$$ = $2; }
  | {$$ = NULL; }
  ;

origin_var_list:
  origin_var_list COMMA ID EQ_ ID
  {
    $$ = $1;
    $$->push_back(make_tuple(Symbol($3->getValue()), Symbol($5->getValue())));
  }
  | origin_var_list extra_commas ID EQ_ ID
  {
    yyerror("extra commas");
  }
  | origin_var_list COMMA ID EQ_ error
  {
    yyerror("missing origin variable name");
  }
  | origin_var_list ID EQ_ ID
  {
    yyerror("missing comma");
  }
  | ID EQ_ ID
  { 
    $$ = new vector<tuple<Symbol, Symbol>>();
    $$->push_back(make_tuple(Symbol($1->getValue()), Symbol($3->getValue())));
  }
  | ID ID
  {
    yyerror("missing =");
  }
  ;
  
origin_func_decl:
  ORIGIN type ID LPAREN type RPAREN
  { $$ = new OriginDecl(curr_line, curr_col, $2->getTyp(), Symbol($3->getValue()), $5->getTyp());  }
| ORIGIN type ID LPAREN error RPAREN
  { yyerror("syntax error in type argument of origin function"); }
| ORIGIN type LPAREN type RPAREN
  {
    yyerror("missing type or origin function name");
  }
| ORIGIN type ID type RPAREN
  {
    yyerror("missing ( in origin function");
  }
| ORIGIN error
  {
    yyerror("error in origin function definition");
  }
  ;
    
distinct_decl:
    DISTINCT refer_name id_or_subid_list
    {
      $$ = new DistinctDecl(curr_line, curr_col, Symbol($2->getValue()));
      if ($3 != NULL){
        for(size_t i = 0; i < $3->size(); i++){
          $$->add(get<0>((*$3)[i]), get<1>((*$3)[i]));
        }
        delete($3);
      }
    }
    ;

id_or_subid_list:
    id_or_subid
    {
      $$ = new vector<tuple<string, int>>();
      $$->push_back(*$1);
      delete($1);
    }
  | id_or_subid_list COMMA id_or_subid
    {
      $$ = $1;
      $$->push_back(*$3);
      delete($3);
    }
  | id_or_subid_list id_or_subid
    {
      yyerror("missing comma");
    }
  | id_or_subid_list extra_commas id_or_subid
    {
      yyerror("missing comma");
    }

  ;

    
id_or_subid:
    ID { 
        //tuple<string, int> idint = make_tuple($1->getValue(), 1);
        $$ = new tuple<string, int>($1->getValue(), 1);
       }
  | ID LBRACKET INT_LITERAL RBRACKET
    { 
      //tuple<string, int> idint2 = make_tuple($1->getValue(), $3->getValue());
      $$ = new tuple<string, int>($1->getValue(), $3->getValue());
    }
  ;      
  
//TODO: DistributionDec/ClassName
distribution_decl:
    DISTRIBUTION ID EQ_ refer_name LPAREN opt_expression_list RPAREN
    { }
    ;

refer_name:
    ID { 
      $$ = new BLOGSymbol<string>(curr_line, curr_col, $1->getValue());
    }
  | ID DOT refer_name {
      $$ = new BLOGSymbol<string>(curr_line, curr_col, $1->getValue() + "." + $3->getValue());
    }
  ;
  
dependency_statement_body:
  DISTRIB expression
  { $$ = $2; }
  ;
  
  
//TODO: ParameterDec
parameter_decl:
    PARAM type ID { }
  | PARAM type ID COLON expression { }
  ;
  
expression:
    operation_expr {$$ = $1;}
  | literal {$$ = $1;}
  | function_call {$$ = $1;}
  | list_expr {$$ = $1;}
  | map_construct_expression {$$ = $1;}
  | quantified_formula { $$ = $1; }
  | set_expr { $$ = $1; }
  | number_expr { $$ = $1; }
  | if_expr { $$ = $1; }
  | case_expr { $$ = $1; }
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
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::MINUS, nullptr, $2); } %prec UMINUS
  | NOT_ expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::NOT, NULL, $2); } 
  | AT_ expression
    {$$ = new OpExpr(curr_line, curr_col, AbsynConstant::AT, NULL, $2); } 
  | LPAREN expression RPAREN {$$ = $2; }
  ;
  
quantified_formula:
    FORALL_ type ID expression %prec FORALL_
    {$$ = new QuantExpr(curr_line, curr_col, AbsynConstant::FORALL, *(new VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue()))), $4); }
  | EXISTS_ type ID expression %prec EXISTS_
    {$$ = new QuantExpr(curr_line, curr_col, AbsynConstant::EXISTS, *(new VarDecl(curr_line, curr_col, *$2, Symbol($3->getValue()))), $4); }
  ;
  
function_call:
  refer_name LPAREN opt_expression_list RPAREN 
  { 
    $$ = new FuncApp(curr_line, curr_col, Symbol($1->getValue())); 
    if ($3 != NULL){
      for(size_t i = 0; i < $3->size(); i++){
        $$->add((*$3)[i]);
      }
      delete($3);
    }
  }
  | refer_name
  {
    $$ = new FuncApp(curr_line, curr_col, Symbol($1->getValue()));
  }
  | refer_name LPAREN error
  {
    yyerror("error in body of function call");
  }
  ;

if_expr:
  IF expression THEN expression ELSE expression
  { $$ = new IfExpr(curr_line, curr_col, $2, $4, $6); }
| IF expression THEN expression
  { $$ = new IfExpr(curr_line, curr_col, $2, $4); }
;

case_expr:
  CASE expression IN map_construct_expression
  {
    if ($2 != NULL && $4 != NULL){
      $$ = new CaseExpr(curr_line, curr_col, $2, $4);
    }
    else{
      yyerror("error in case expression");
    }
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
  | expression_list extra_commas expression
  {
    yyerror("extra commas in expression list");
  }
  | expression 
    { 
      $$ = new vector<Expr*>();
      $$->push_back($1);
    }
  ;
  
list_expr:
    LBRACKET opt_expression_list RBRACKET
    { $$ = new ArrayExpr(curr_line, curr_col);
      for (size_t i = 0; i < $2->size(); i++ ) {
         $$->add((*$2)[i]);
      }
    }
| LBRACKET semi_colon_separated_expression_list RBRACKET { yyerror("semi colon separated list init expression not supported yet"); }
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
  
expression_pair_list:
    expression_pair_list COMMA expression RIGHTARROW expression
    { 
      $$ = $1;
      $$->push_back(make_tuple($3, $5));
    }
  | expression RIGHTARROW expression 
    { 
      $$ = new vector<tuple<Expr*, Expr*>>();
      $$->push_back(make_tuple($1, $3));
    }
  ;

number_expr:
    NUMSIGN set_expr 
    { $$ = new CardinalityExpr(curr_line, curr_col, (Expr*)$2); }
  | NUMSIGN type 
  { 
      VarDecl var(curr_line, curr_col, *$2);
      $$ = new CardinalityExpr(curr_line, curr_col, new CondSet(curr_line, curr_col, var));
  }
  | NUMSIGN error
  {
    yyerror("expecting number expression here.");
  }
  ;


set_expr:
    explicit_set {$$ = $1; }
  | tuple_set {$$ = $1; }
  ;

explicit_set:
    LBRACE opt_expression_list RBRACE
    {
      $$ = new ListSet(curr_line, curr_col);
      for(size_t i = 0; i < $2->size(); i++){
        $$->add((*$2)[i]);
      }
      delete($2);
    }
    ;

comprehension_expr:
    expression_list FOR type_var_lst COLON expression
    {
      $$[0] = $1; $$[1] = $3; $$[2] = $5;
    }
  | expression_list FOR type_var_lst
    {
      $$[0] = $1; $$[1] = $3; $$[2] = NULL;
    }
  ;
  
  
//TODO: TupleSetExpr
tuple_set:
    LBRACE comprehension_expr RBRACE
  { 
    if ($2 != NULL){
      $$ = new TupleSetExpr(curr_line, curr_col, *((vector<Expr*>*)$2[0]), *((vector<VarDecl>*)$2[1]), (Expr*)$2[2]); 
      delete((vector<Expr*>*)$2[0]);
      delete((vector<VarDecl>*)$2[1]);
    }
    else{
      yyerror("invalid tupleset");
    }
  }
  ;
  
evidence_stmt:
  OBS evidence {$$ = $2; }
  | OBS error
  {
    yyerror("incorrect obs statement");
  }
  ;
  
evidence:
  value_evidence {$$ = $1; }
  ;
    
value_evidence:
  expression EQ_ expression
  {
    $$ = new Evidence(curr_line, curr_col, $1, $3); 
  }
  | error EQ_ expression
  {
    yyerror("incorrect lefthand expression in evidence");
  }
  | expression EQ_ error
  {
    yyerror("incorrect righthand expression in evidence");
  }
  ;

query_stmt:
  QUERY expression 
  { $$ = new Query(curr_line, curr_col, $2); }
| QUERY error
  {
    yyerror("invalid query");
  }
  ; 
  
%%



void yyerror(const char *s) {
  cout << "Parse error at line number: " << curr_line << " and column number: " << curr_col << "!  Message: " << s << endl;
  // might as well halt now:
  //exit(-1);
}
