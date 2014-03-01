#include "PreDecl.h"

namespace swift {
namespace predecl {

PreDecl::PreDecl(const std::string& name) :
    name(name) {
}

PreDecl::~PreDecl() {
}

const std::string& PreDecl::getName() const {
  return name;
}

}
}
