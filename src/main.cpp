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
using namespace std;
using namespace swift;

extern absyn::BlogProgram* parse(const char*);
int main(int argc, char** argv) {
  if (argc != 5){
    cout << "Incorrect number of arguments: " << argc << endl;
    exit(0);
  }
  const char* inp;
  const char* out;
  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-i") == 0) inp = argv[i+1];
    if(strcmp(argv[i], "-o") == 0) out = argv[i+1];
  }

  absyn::BlogProgram* test = parse(inp);

  //semant::Semant* sem = new semant::Semant();
  //sem->process(test);
  //ir::BlogModel* model = sem->getModel();
  
  /*codegen is unfinished so this is commented */
  //codegen::CPPTranslator* trans = new codegen::CPPTranslator();
  //trans->translate(model);
  //code::Code* program = trans->getResult();
  
  FILE *output = fopen(out, "w");
  test->print(output, 0);
  return 0;
}
