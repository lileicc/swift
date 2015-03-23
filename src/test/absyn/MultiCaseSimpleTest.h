#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class MultiCaseSimpleTest {
  swift::absyn::BlogProgram* root;
public:
  MultiCaseSimpleTest();
  ~MultiCaseSimpleTest();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}