#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class DirichletSimpleTest2 {
  swift::absyn::BlogProgram* root;
public:
  DirichletSimpleTest2();
  ~DirichletSimpleTest2();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}