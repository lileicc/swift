#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include "absyn/BlogProgram.h"
#include "preprocess/Preprocessor.h"
#include "semant/Semant.h"
#include "codegen/Translator.h"
#include "ir/BlogModel.h"
#include "printer/CPPPrinter.h"
#include "codegen/PFTranslator.h"

extern swift::absyn::BlogProgram* parse(const char* inp);
int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Help: " << argc << std::endl;
    std::cout
        << "\t[main] -v [-e ParticleFilter] -i <input filename> -o <output filename> --ir <filename for printing ir>"
        << std::endl;
    exit(0);
  }
  const char* inp = "";
  const char* out = "";
  const char* irfile = nullptr;
  bool verbose = false;
  std::string engine_type = "LWSampler";
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0)
      verbose = true;
    if (strcmp(argv[i], "-i") == 0)
      inp = argv[++i];
    if (strcmp(argv[i], "-o") == 0)
      out = argv[++i];
    if (strcmp(argv[i], "-e") == 0)
      engine_type = std::string(argv[++i]);
    if (strcmp(argv[i], "--ir") == 0) {
      irfile = argv[++i];
      if (i >= argc || (irfile && irfile[0] == '-')) {
        irfile = "";
        i--;
      }
    }
  }

  // parse the input file to get abstract syntax
  swift::absyn::BlogProgram* blog_absyn = parse(inp);

  if (blog_absyn == NULL) {
    fprintf(stderr, "Error in parsing input %s!", inp);
    // TODO print the error message!
    return 1;
  }
  
  if (verbose)
    blog_absyn->print(stdout, 0);
  
  // preprocess of input blog program
  swift::preprocess::Preprocessor preproc;
  preproc.process(blog_absyn);
  if (!preproc.Okay()) {
    fprintf(stderr, "Error in Preprocessing Phase! Please remove unsupported hacks in the program!");
    // TODO print the error message!
    return 1;
  }
  blog_absyn = preproc.getProg();

  // semantic checking and translating to ir
  swift::semant::Semant sem;
  sem.process(blog_absyn);
  std::shared_ptr<swift::ir::BlogModel> model = sem.getModel();

  if (!sem.Okay()) {
    fprintf(stderr, "Error in semantic checking input %s!", inp);
    // TODO print the error message!
    return 1;
  }

  if (irfile) {
    model->print(irfile);
  }

  // translate ir to code representation
  swift::codegen::Translator* trans = nullptr;
  if (engine_type == "LWSampler") {
    trans = new swift::codegen::Translator();
  } else if (engine_type == "ParticleFilter") {
    trans = new swift::codegen::PFTranslator();
  } else {
    printf("%s engine not found", engine_type.c_str());
  }
  
  if (trans != nullptr) {
    trans->translate(model);
    swift::code::Code* program = trans->getResult();
    
    // print code
    swift::printer::Printer * prt = new swift::printer::CPPPrinter(
                                                                   std::string(out));
    program->print(prt);
    
    printf("correctly translated %s!\n", inp);
    delete program;
    delete prt;
  }

  delete blog_absyn;
  return 0;
}
