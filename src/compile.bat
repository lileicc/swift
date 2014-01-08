cd parse
yacc -d blog.yacc
flex blog.flex
cd ..
g++ -std=gnu++11 absyn\*.cpp ir\*.cpp fabrica\*.cpp msg\*.cpp predecl\*.cpp semant\Semant.cpp main.cpp parse\y.tab.c parse\lex.yy.c -o parseex