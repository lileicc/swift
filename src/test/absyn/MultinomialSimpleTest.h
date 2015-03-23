#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class MultinomialSimpleTest {
  swift::absyn::BlogProgram* root;
public:
  MultinomialSimpleTest();
  ~MultinomialSimpleTest();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}