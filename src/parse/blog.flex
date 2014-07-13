%{
#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <vector>
#include <tuple>
using namespace std;
#define YY_DECL extern "C" int yylex()
#include "BLOGSymbol.h"
#include "parser.h"  // to get the token types that we return

char string_buf[100000];
int buf_len;
char *string_buf_ptr;

int curr_line = 1;
int curr_col = 1;
int first_column;
int last_column;

//int symbol(int token){
//  yylval.keyword.symbol(curr_line, curr_col-yyleng);
//  return token;
//}

static void update_column(){
  first_column = curr_col;
  {char * s; for(s = yytext; *s != '\0'; s++){
    if(*s == '\n'){
      curr_line++;
      curr_col = 1;
    }else{
      curr_col++;
    }
  }}
  last_column = curr_col;
}

#define YY_USER_ACTION update_column();

%}
%option noyywrap

%x STR_LIT
%x CHAR_LIT

Alpha            [A-Za-z]

Digit            [0-9]

Identifier       {Alpha}({Alpha}|{Digit}|_)*

IntegerLiteral   {Digit}+

FLit1            {Digit}+\.{Digit}* 
FLit2            \.{Digit}+ 
FLit3            {Digit}+ 
Exponent         [eE][+-]?{Digit}+
DoubleLiteral    ({FLit1}|{FLit2}|{FLit3}){Exponent}?

LineTerminator   [\n\r\r\n]

InputCharacter   [^\r\n]

Whitespace       [ \f\t\n\r]

OCTAL_DIGIT      [01234567]

ZERO_TO_THREE    [0123]

HEX_DIGIT        [0123456789abcdefABCDEF]

/* comments */
TraditionalComment      "/*"([^*]|\*+[^*/])*\*+"/"
EndOfLineComment        "//"{InputCharacter}*{LineTerminator}?
DocumentationComment    "/*""*"+[^/*]~"*/"
Comment                 {TraditionalComment}|{EndOfLineComment}|{DocumentationComment}


%%
\" { 
    string_buf_ptr = string_buf;
    buf_len = 0;
    BEGIN(STR_LIT); 
   }
\' { 
    string_buf_ptr = string_buf;
    buf_len = 0;
    BEGIN(CHAR_LIT); 
   }

[Ii][Nn] { return IN; }
[Cc][Aa][Ss][Ee] { return CASE; }
[Tt][Yy][Pp][Ee] { return TYPE; }
[Rr][Aa][Nn][Dd][Oo][Mm] { return RANDOM; }
[Nn][Oo][Nn][Rr][Aa][Nn][Dd][Oo][Mm] { return FIXED; }
[Ff][Ii][Xx][Ee][Dd] { return FIXED; }			   
[Gg][Ee][Nn][Ee][Rr][Aa][Tt][Ii][Nn][Gg] { return ORIGIN; }
[Oo][Rr][Ii][Gg][Ii][Nn] { return ORIGIN; }
[Gg][Uu][Aa][Rr][Aa][Nn][Tt][Ee][Ee][Dd] { return DISTINCT; }
[Dd][Ii][Ss][Tt][Ii][Nn][Cc][Tt] { return DISTINCT; }
[Ff][Aa][Cc][Tt][Oo][Rr] { return FACTOR; }
[Pp][Aa][Rr][Ff][Aa][Cc][Tt][Oo][Rr] { return PARFACTOR; }
[Tt][Hh][Ee][Nn]     { return THEN; }
[Ee][Ll][Ss][Ee]  	{ return ELSE; }
[Ff][Oo][Rr]         { return FOR; }
[Ee][Ll][Ss][Ee][Ii][Ff]  { return ELSEIF; }
[Ii][Ff]  		{ return IF; }
[Qq][Uu][Ee][Rr][Yy]	{ return QUERY;}
[Oo][Bb][Ss]         { return OBS;}
[Pp][Aa][Rr][Aa][Mm] { return PARAM;}
[Ee][Xx][Ii][Ss][Tt][Ss] { return EXISTS_; }
[Ff][Oo][Rr][Aa][Ll][Ll] { return FORALL_; }
[Ll][Ii][Ss][Tt] { return LIST; }
[Mm][Aa][Pp] { return MAP; }
[Dd][Ii][Tt][Rr][Ii][Bb][Uu][Tt][Ii][Oo][Nn] { return DISTRIBUTION; }


"true"	{ 
            yylval.boolval = new BLOGSymbol<bool>(curr_line, curr_col, true);
            return BOOLEAN_LITERAL; 
        }
"false" { 
            yylval.boolval = new BLOGSymbol<bool>(curr_line, curr_col, false);
            return BOOLEAN_LITERAL;
        }
"null" {return NULLITY; }
{IntegerLiteral}  {yylval.ival = new BLOGSymbol<int>(curr_line, curr_col, atoi( yytext )); return INT_LITERAL;}
{DoubleLiteral}   {yylval.dblval = new BLOGSymbol<double>(curr_line, curr_col, atof( yytext )); return DOUBLE_LITERAL;}

"+"     { return PLUS_; }
"-"     { return MINUS_; }
"*"     { return MULT_; }
"/"     { return DIV_; }
"%"     { return MOD_; }
"^"     { return POWER_; }
"<"     { return LT_; }
">"     { return GT_; }
"<="    { return LEQ_; }
">="    { return GEQ_; }
"=="    { return EQEQ_; }
"!="    { return NEQ_; }
"&"	    { return AND_; }
"|"     { return OR_; }
"!"	    { return NOT_; }
"@"     { return AT_; }
"->"	{ return RIGHTARROW; }
"=>"    { return DOUBLERIGHTARROW; }

"("		{ return LPAREN; }
")"		{ return RPAREN; }
"}"		{ return RBRACE; }
"{"		{ return LBRACE; }
"["		{ return LBRACKET; }
"]"		{ return RBRACKET; }
";"		{ return SEMI; }
":"		{ return COLON;}
"."     { return DOT; }
","		{ return COMMA;}
"="		{ return EQ_; }
"~"		{ return DISTRIB; }
"#"     { return NUMSIGN; }

{Comment} { /* ignore */ }

{Whitespace} { /* Do nothing */}
     
{Identifier} { 
  string s(yytext);
  yylval.sval = new BLOGSymbol<string>(curr_line, curr_col, s);
  return ID;
} 

<STR_LIT>\" {
            *string_buf_ptr = '\0';
            //char * s = (char *) malloc (buf_len + 1);
            //strcpy(s, string_buf);
            string s(string_buf);
            yylval.sval = new BLOGSymbol<string>(curr_line, curr_col, s);
            BEGIN(INITIAL);
            return STRING_LITERAL;
            } 
<CHAR_LIT>\' {
            *string_buf_ptr = '\0';
            if (buf_len == 1){
                yylval.chrval = new BLOGSymbol<char>(curr_line, curr_col, *string_buf);
            }
            else{
                cout << "A character must be of length 1" << endl;
                exit(1);
            }
            BEGIN(INITIAL);
            return CHAR_LITERAL;
            } 
<STR_LIT,CHAR_LIT>\\b  { *string_buf_ptr++ = '\b'; buf_len++; }
<STR_LIT,CHAR_LIT>\\t  { *string_buf_ptr++ = '\t'; buf_len++; }
<STR_LIT,CHAR_LIT>\\n  { *string_buf_ptr++ = '\n'; buf_len++; }
<STR_LIT,CHAR_LIT>\\f  { *string_buf_ptr++ = '\f'; buf_len++;}
<STR_LIT,CHAR_LIT>\\r  { *string_buf_ptr++ = '\r'; buf_len++; }
<STR_LIT,CHAR_LIT>\\\" { *string_buf_ptr++ = '\"'; buf_len++; }
<STR_LIT,CHAR_LIT>\\\' { *string_buf_ptr++ = '\''; buf_len++; }
<STR_LIT,CHAR_LIT>\\\\ { *string_buf_ptr++ = '\\'; buf_len++; }
<CHAR_LIT,STR_LIT>. {
            char *yptr = yytext;
            while(*yptr){
                *string_buf_ptr++ = *yptr++;
            }
            buf_len += yyleng;
           }

.                ;
%%