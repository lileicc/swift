#pragma once

// PreDecl Conjugate Prior Checkers

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "ConjugatePrior.h"

namespace swift {
namespace analyzer {
namespace conjugate {

class ConjugatePriorList {
public:
  ConjugatePriorList();
  ~ConjugatePriorList();

  // PreDecl Conjugate Priors
  
  // Conjugate Priors using Builtin ConjugatePrior Interface
  static std::map<std::string, std::vector<std::shared_ptr<ConjugatePrior>>> priorStore; // used to store builtin conjugate priors
  
private:
  static std::map<std::string, std::vector<std::shared_ptr<ConjugatePrior>>> initPriorStore();
};

}
}
}
