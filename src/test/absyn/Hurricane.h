#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class Hurricane {
  swift::absyn::Absyn* root;
public:
  Hurricane();
  ~Hurricane();
  void test(FILE *file);
  void build();
  swift::absyn::Absyn* getRoot();
};

}