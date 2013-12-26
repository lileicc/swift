#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include <tclap/CmdLine.h>
#include "absyn\BlogProgram.h"
#include "semant\Semant.h"
#include "codegen\CPPTranslator.h"
#include "ir\BlogModel.h"
using namespace std;
using namespace swift;

extern absyn::BlogProgram* parse(const char*);
main(int argc, char** argv) {
  // open a file handle to a particular file:
  TCLAP::CmdLine cmd("BLOG compiler", ' ', "0.6");
  /**
    *ValueArg constructor takes 6 arguments which are as follows
    *flagname, flag name, flag description, whether this flag is necessary, default value
    *human readable description of type name 
    */    
  TCLAP::ValueArg<string> inputArg("i","input","BLOG input file",false,"input.in","string");
  TCLAP::ValueArg<string> outputArg("o","output","BLOG output file",false,"output.out","string");
  cmd.add(inputArg);
  cmd.add(outputArg);
  cmd.parse(argc, argv);  
  
  const char* inp = inputArg.getValue().c_str();
  const char* out = outputArg.getValue().c_str();

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
}