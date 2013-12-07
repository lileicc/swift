cd parse
yacc -d parser.y
flex scanner.l
cd ..
g++ -std=gnu++11 absyn\*.cpp code\*.cpp ir\*.cpp fabrica\*.cpp msg\*.cpp predecl\*.cpp semant\Semant.cpp codegen\CPPTranslator.cpp main.cc parse\y.tab.c parse\lex.yy.c -o parseex