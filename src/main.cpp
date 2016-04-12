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
#include "codegen/MHTranslator.h"
#include "codegen/GibbsTranslator.h"
#include "util/Configuration.h"

extern swift::absyn::BlogProgram* parse(const char* inp);

int main(int argc, char** argv) {

  if (argc < 3) {
    std::cout << "Help: " << argc << std::endl;
    std::cout
        << "\t[main] [-v] -i <input filename>... -o <output filename> " << std::endl
        << "\t            [-n <number of samples, default = 10^6>]" << std::endl
        << "\t            [-e LWSampler |" << std::endl
        << "\t                ParticleFilter [--particle <ParticleNumber>] |" << std::endl
        << "\t                MHSampler [--burn-in <number of burn-in samples>] |" << std::endl
        << "\t                GibbsSampler [--burn-in <number of burn-in samples>] ]" << std::endl
        << "\t            [--ir <filename for printing ir>]" << std::endl
        << "\t            [--hist-buckets <number of buckets>]" << std::endl
        << "\t            [--model-output <model output filename> ]" << std::endl
        << "\t            [--include <filenames for external source code>]" << std::endl
        << "\t            [--log true|false (whether using log-likelihood, default = true) ]" << std::endl;
    exit(0);
  }

  swift::Configuration* config = swift::Configuration::getConfiguration();
  std::vector<const char*> inp;
  std::vector<std::string> extraHeaders;
  const char* out = "";
  const char* model_out = nullptr;
  const char* irfile = nullptr;
  bool verbose = false;
  std::string engine_type = "LWSampler";
  int particle_N = 0, iter_N = 0, burn_in_N = 0, bucket_N = 0;

  for (int i = 1; i < argc; i++) {

    if (strcmp(argv[i], "-v") == 0) {
      verbose = true;
    }
    if (strcmp(argv[i], "-i") == 0) {
      if(i + 1 < argc && argv[i+1] && argv[i+1][0] != '-') {
        for(++i; i < argc && argv[i] && argv[i][0] != '-'; ++ i)
          inp.push_back(argv[i]);
        -- i;
      }
    }
    if (strcmp(argv[i], "-o") == 0) {
      out = argv[++i];
    }
    if (strcmp(argv[i], "-e") == 0) {
      engine_type = std::string(argv[++i]);
    }
    if (strcmp(argv[i], "--ir") == 0) {
      irfile = argv[++i];
      if (i >= argc || (irfile && irfile[0] == '-')) {
        irfile = "";
        i--;
      }
    }
    if (strcmp(argv[i], "--include") == 0) {
      if(i + 1 < argc && argv[i+1] && argv[i+1][0] != '-') {
        for(++i; i < argc && argv[i] && argv[i][0] != '-'; ++ i)
          extraHeaders.push_back(argv[i]);
        -- i;
      }
    }
    if (strcmp(argv[i], "--particle") == 0 && i + 1 < argc && argv[i+1]) {
      int part;
      if(sscanf(argv[i + 1], "%d", &part) == 1 && part > 0) {
        particle_N = part;
        ++ i;
      }
      config->setValue("N_PF_PARTICLES", particle_N);
    }
    if (strcmp(argv[i], "--burn-in") == 0 && i + 1 < argc && argv[i+1]) {
      int burn_in;
      if(sscanf(argv[i + 1], "%d", &burn_in) == 1 && burn_in > 0) {
        burn_in_N = burn_in;
        ++ i;
      }
      config->setValue("N_BURN_IN_SAMPLES", burn_in_N);
    }
    if (strcmp(argv[i], "--hist-buckets") == 0 && i + 1 < argc && argv[i+1]) {
      int bckts;
      if(sscanf(argv[i + 1], "%d", &bckts) == 1 && bckts > 0) {
        bucket_N = bckts;
        ++ i;
      }
      config->setValue("N_HIST_BUCKETS", bucket_N);
    }
    if (strcmp(argv[i]), "--model-output") == 0 && i + 1 < argc && argv[i+1]) {
      model_out = argv[++i];
      config->setValue("MODEL_OUT_FILENAME", model_out);
    }
    if (strcmp(argv[i], "-n") == 0 && i + 1 < argc && argv[i+1]) {
      int iter;
      if(sscanf(argv[i + 1], "%d", &iter) == 1 && iter > 0) {
        iter_N = iter;
        ++ i;
      }
      config->setValue("N_SAMPLES", iter_N);
    }

    // Checking for log likelihood flag on command line. Usage: "--log [true|false]"
    if (strcmp(argv[i], "--log") == 0 && i + 1 < argc && argv[i+1]) {
      bool loglik;
      strcmp(argv[i + 1], "false") == 0 ? loglik = false : loglik = true;
      swift::Configuration::getConfiguration()->setValue("COMPUTE_LIKELIHOOD_IN_LOG", loglik);
      ++ i;
    }
  }

  swift::absyn::BlogProgram* blog_absyn = NULL;
  if(inp.size() == 0) {
    fprintf(stderr, "No Input File Specified!\n");
    return 1;
  } else {
    for(size_t i = 0; i < inp.size(); ++ i) {
      // parse the input file to get abstract syntax
      swift::absyn::BlogProgram* sub_absyn = parse(inp[i]);
      if (sub_absyn == NULL) {
        fprintf(stderr, "Error in parsing input %s!", inp[i]);
        // TODO print the error message!
        return 1;
      }
      if(blog_absyn == NULL)
        blog_absyn = sub_absyn;
      else {
        blog_absyn->add(sub_absyn->getAll());
        sub_absyn->clear();
        delete sub_absyn;
      }
    }
  }

  if (verbose) {
    blog_absyn->print(stdout, 0);
  }

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
    fprintf(stderr, "Error in semantic checking!");
    delete blog_absyn;
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
    auto PF_trans = new swift::codegen::PFTranslator();
    if(particle_N>0)
      PF_trans->setParticleNum(particle_N);
    trans = PF_trans;
  } else if (engine_type == "MHSampler") {
    auto MH_trans = new swift::codegen::MHTranslator();
    if(iter_N>0)
      MH_trans->setIterationNum(iter_N);
    trans = MH_trans;
  } else if (engine_type == "GibbsSampler") {
    auto gibbs_trans = new swift::codegen::GibbsTranslator();
    if(iter_N>0)
      gibbs_trans->setIterationNum(iter_N);
    trans = gibbs_trans;
  } else {
    printf("<%s> engine not found", engine_type.c_str());
  }

  if (trans != nullptr) {
    trans->translate(model);
    swift::code::Code* program = trans->getResult();

    if (program == NULL) {
      fprintf(stderr, "Error in algorithm-specific program translating!");
      delete trans;
      delete blog_absyn;
      return 1;
    }

    // print code
    swift::printer::Printer * prt = new swift::printer::CPPPrinter(std::string(out));

    for(size_t i = 0; i < extraHeaders.size(); ++ i)
      prt->addHeader(extraHeaders[i]);

    program->print(prt);

    printf("correctly translated model file");
    if(inp.size() == 1)
      printf(" <%s>!\n", inp[0]);
    else {
      printf("s!");
      for(size_t i = 0; i < inp.size(); ++ i)
        printf(" <%s>", inp[i]);
      printf("\n");
   }
    delete program;
    delete prt;
  }

  delete trans;
  delete blog_absyn;
  return 0;
}
