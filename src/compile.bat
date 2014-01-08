cd parse
yacc -d parser.y
flex scanner.l
cd ..
g++ -std=gnu++0x -I absyn -enable-auto-import absyn\*.cpp main.cc parse\y.tab.c parse\lex.yy.c -o parseex