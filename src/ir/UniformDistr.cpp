#include "UniformDistr.h"

#include <string>

namespace swift { namespace ir {

UniformDistr::UniformDistr()
  :Distribution(std::string("Uniform")) {
}

UniformDistr::~UniformDistr() {
}

}
}