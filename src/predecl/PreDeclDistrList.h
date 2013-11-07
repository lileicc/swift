#pragma once

#include "CategoricalDistrDecl.h"

namespace swift { namespace predecl {

class PreDeclDistrList {
public:
  PreDeclDistrList();
  ~PreDeclDistrList();

  static const CategoricalDistrDecl categoricalDistr;
};

}
}