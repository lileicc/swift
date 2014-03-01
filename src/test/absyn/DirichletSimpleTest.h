#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class DirichletSimpleTest {
  swift::absyn::BlogProgram* root;
public:
  DirichletSimpleTest();
  ~DirichletSimpleTest();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}