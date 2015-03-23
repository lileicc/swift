#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class MatrixTest {
  swift::absyn::BlogProgram* root;
public:
  MatrixTest();
  ~MatrixTest();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}