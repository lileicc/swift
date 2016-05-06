#include "ConjugatePriorList.h"

namespace swift {
namespace analyzer {
namespace conjugate {

// PreDecl Conjugate Priors

std::map<std::string, std::vector<std::shared_ptr<ConjugatePrior>>> 
ConjugatePriorList::initPriorStore() {
  std::map<std::string, std::vector<std::shared_ptr<ConjugatePrior>>> ret;
  return ret;
}

std::map<std::string, std::vector<std::shared_ptr<ConjugatePrior>>> 
ConjugatePriorList::priorStore = ConjugatePriorList::initPriorStore();

ConjugatePriorList::ConjugatePriorList() {
}

ConjugatePriorList::~ConjugatePriorList() {
}

}
}
}
