MAIN=swift

CXX=g++
CXX_CFLAGS=-std=c++11 -Wall
EXEC=$(MAIN)
YACCDIR=lib/byacc-20130925

compile:
	$(CXX) $(CXX_CFLAGS) src/absyn/*.cpp src/ir/*.cpp src/fabrica/*.cpp src/msg/*.cpp src/predecl/*.cpp src/code/*.cpp src/codegen/*.cpp src/semant/*.cpp src/random/*.cpp src/printer/*.cpp src/util/*.cpp src/main.cpp src/parse/parser.cpp src/parse/lexer.cpp -o $(EXEC)
	
genparser: byacc
	cd src/parse; flex -olexer.cpp blog.flex; ../../$(YACCDIR)/yacc -v -d -o parser.cpp blog.yacc

byacc:
	cd $(YACCDIR); make
