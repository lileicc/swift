MAIN=swift

CXX=g++
CXX_CFLAGS=-std=c++11 -Wall
EXEC=$(MAIN)
SRC=src/absyn/*.cpp \
  src/analyzer/*.cpp \
  src/ir/*.cpp \
  src/fabrica/*.cpp \
  src/msg/*.cpp \
  src/predecl/*.cpp \
  src/code/*.cpp \
  src/codegen/*.cpp \
  src/semant/*.cpp \
  src/random/*.cpp \
  src/printer/*.cpp \
  src/preprocess/*.cpp \
  src/util/*.cpp \
  src/main.cpp \
  src/parse/parser.cpp \
  src/parse/lexer.cpp

compile: $(SRC)
	$(CXX) $(CXX_CFLAGS) $(SRC) -o $(EXEC)
	
genparser:
	cd src/parse; flex -olexer.cpp blog.flex; yacc -d -o parser.cpp blog.yacc

