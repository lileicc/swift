#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include "absyn/BlogProgram.h"
#include "semant/Semant.h"
#include "codegen/CPPTranslator.h"
#include "ir/BlogModel.h"
#include "printer/CPPPrinter.h"

extern swift::absyn::BlogProgram* parse(const char*);
int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Help: " << argc << std::endl;
    std::cout << "\t[main] -i <input filename> -o <output filename>"
        << std::endl;
    exit(0);
  }
  const char* inp = "";
  const char* out = "";
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0)
      inp = argv[++i];
    if (strcmp(argv[i], "-o") == 0)
      out = argv[++i];
  }

  // parse the input file to get abstract syntax
  swift::absyn::BlogProgram* blog_absyn = parse(inp);

  // semantic checking and translating to ir
  swift::semant::Semant sem;
  sem.process(blog_absyn);
  swift::ir::BlogModel* model = sem.getModel();

  // translate ir to code representation
  swift::codegen::CPPTranslator trans;
  trans.translate(model);
  swift::code::Code* program = trans.getResult();

  // print code
  swift::printer::Printer * prt = new swift::printer::CPPPrinter(
      std::string(out));
  program->print(prt);
  return 0;
}
