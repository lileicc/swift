cd src
cd parse
yacc -d blog.yacc
flex blog.flex
cd ..
cd ..
g++ -std=gnu++11 src\absyn\*.cpp src\ir\*.cpp src\fabrica\*.cpp src\msg\*.cpp src\predecl\*.cpp src\code\*.cpp src\codegen\CPPTranslator.cpp src\semant\Semant.cpp src\main.cpp src\parse\y.tab.c src\parse\lex.yy.c -o parseex
