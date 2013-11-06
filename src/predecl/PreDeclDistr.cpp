#include "PreDeclDistr.h"

namespace swift { namespace predecl {

PreDeclDistr::PreDeclDistr(const std::string& name)
  :name(name) {
}

PreDeclDistr::~PreDeclDistr() {
}

const std::string& PreDeclDistr::getName() const {
  return name;
}

}
}