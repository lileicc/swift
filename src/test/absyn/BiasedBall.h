#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class BiasedBall {
  swift::absyn::BlogProgram* root;
public:
  BiasedBall();
  ~BiasedBall();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}
