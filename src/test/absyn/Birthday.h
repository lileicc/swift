#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class Birthday {
  swift::absyn::BlogProgram* root;
public:
  Birthday();
  ~Birthday();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}
