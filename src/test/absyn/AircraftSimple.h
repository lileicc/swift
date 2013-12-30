#pragma once

#include "../../absyn/BlogProgram.h"

namespace test_absyn {

class AircraftSimple {
  swift::absyn::BlogProgram* root;
public:
  AircraftSimple();
  ~AircraftSimple();
  void test(FILE *file);
  void build();
  swift::absyn::BlogProgram* getRoot();
};

}
