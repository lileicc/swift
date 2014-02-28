yacc -d parser.y
flex scanner.l
g++ -std=gnu++0x -I C:\Users\tejas\swift\src\absyn -enable-auto-import C:\Users\tejas\swift\src\absyn\*.cpp main.cc y.tab.c lex.yy.c -o snazzle