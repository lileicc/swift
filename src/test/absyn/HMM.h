#pragma once
// Test Class for Particle Filtering Algorithm
#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class HMM {
  swift::absyn::BlogProgram* root;
public:
  HMM();
  ~HMM();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}
