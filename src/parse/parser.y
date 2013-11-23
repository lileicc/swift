%{
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "BLOGSymbol.h"
using namespace std;

// stuff from flex that bison needs to know about: 
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int yylineno;
extern "C" int first_column;
extern "C" int last_column;
 
void yyerror(const char *s);
%}

%union {
  class BLOGSymbol<int> ival;
  class BLOGSymbol<double> dblval;
  class BLOGSymbol<char> chrval;
  class BLOGSymbol<int> boolval;
  class BLOGSymbol<char*> sval;
  class BLOGSymbol<int> keyword;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <keyword> ELSE IF THEN
%token <keyword> TYPE RANDOM FIXED ORIGIN DISTINCT QUERY OBS PARAM LIST MAP DISTRIBUTION
%token <keyword> EXISTS FORALL
%token <keyword> FOR
%token <keyword> NULLITY
%token <ival> INT_LITERAL 
%token <dblval> DOUBLE_LITERAL
%token <boolval> BOOLEAN_LITERAL
%token <chrval> CHAR_LITERAL
%token <sval> STRING_LITERAL
%token <sval> ID
%token <keyword> PARFACTOR FACTOR
%token <keyword> ERROR ELSEIF
%token <keyword> AT
%token <keyword> PLUS MULT DIV MOD POWER MINUS
%token <keyword> LST LT GT LEQ GEQ
%token <keyword> EQEQ NEQ
%token <keyword> EQ
%token <keyword> DISTRIB
%token <keyword> NOT AND OR DOUBLERIGHTARROW
%token <keyword> COMMA SEMI COLON DOT NUMSIGN RIGHTARROW
%token <keyword> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

%%
// this is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:
token:
    TYPE ID token {
              cout << "The type " << $2.getValue() << " was initialized at line " << $1.getLine() << " and column " << $1.getColumn() << endl;
            }
  | INT_LITERAL token    { 
                          cout << "bison found an int: " << $1.getValue() << endl;
                          cout << "the line number is: " << $1.getLine() << endl;
                          cout << "the column number is: " << $1.getColumn() << endl;
                          }
  | DOUBLE_LITERAL token  { cout << "bison found a double: " << $1.getValue() << endl; }
  | BOOLEAN_LITERAL token { cout << "bison found a boolean: " << $1.getValue() << endl; }
  | ID token { cout << "bison found a ID: " << $1.getValue() << endl; }
  | STRING_LITERAL token { cout << "bison found a string: " << $1.getValue() << endl; }
  | CHAR_LITERAL token { cout << "bison found a char: " << $1.getValue() << endl; }
  | {  }
  ;
%%

main() {
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
  
}

void yyerror(const char *s) {
  cout << "Parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}