#include "CategoricalDistrDecl.h"

namespace swift { namespace predecl {
CategoricalDistrDecl::CategoricalDistrDecl()
  :PreDeclDistr(std::string("Categorical")){
}

CategoricalDistrDecl::~CategoricalDistrDecl() {
}

}
}