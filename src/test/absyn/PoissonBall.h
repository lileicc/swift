#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class PoissonBall {
  swift::absyn::BlogProgram* root;
public:
  PoissonBall();
  ~PoissonBall();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}
