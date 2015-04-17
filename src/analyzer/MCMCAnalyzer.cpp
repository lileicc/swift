/*
 * MCMCAnalyzer.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: yiwu
 */

#include "MCMCAnalyzer.h"

#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>

#include "../ir/IRHeader.h"

namespace swift {
namespace analyzer {

MCMCAnalyzer::MCMCAnalyzer(ir::BlogModel* _model)
  : Analyzer(_model) {
}

// Number Variable related
bool MCMCAnalyzer::isOpenType(std::shared_ptr<ir::TypeDomain> ty) {
  return prop_size.count(ty) > 0;
}

int MCMCAnalyzer::getPropSize(std::shared_ptr<ir::TypeDomain> ty) {
  return prop_size[ty];
}

std::vector<std::shared_ptr<ir::FuncDefn>>& MCMCAnalyzer::getDependFunc(std::shared_ptr<ir::TypeDomain> ty) {
  return depend_func[ty];
}

bool MCMCAnalyzer::process() {

  // We do not support temporal model
  if (model->isTemporal()) {
    errMsg.error(-1, -1,
      "[MCMC Analyzer] : [Temporal Model] is not supported now.");
    return false;
  }

  ///////////////////////////////////////////////
  // Check Number Variable Related
  ///////////////////////////////////////////////
  prop_size.clear();
  depend_func.clear();

  // Only one number statement per type allowed
  //      when with number statement, no distinct vars are allowed
  auto types = model->getTypes();
  for (auto& t : types) {
    if (t->getAllOrigin().size() > 0) { // has origin function
      errMsg.error(-1, -1,
        "[MCMC Analyzer] on TypeDomain<" + t->getName() + ">: [Origin Function] is not supported now.");
    }
    if (t->getAllNumberStmt().size() > 0) { // has number statement
      if (t->getAllNumberStmt().size() > 1) {
        errMsg.error(-1, -1,
          "[MCMC Analyzer] on TypeDomain<" + t->getName() + ">: [Multiple Number-Statement] is not supported now.");
      }
      if (t->getInstNames().size() > 0) {
        errMsg.error(-1, -1,
          "[MCMC Analyzer] on TypeDomain<" + t->getName() + ">: [Distinct Instance with Number Statement] is not supported now.");
      }
    }
  }

  // For each random variable, it can contain <= 1 open type in its indices
  auto rndfuncs = model->getRandFuncs();
  for (auto&f : rndfuncs) {
    auto args = f->getArgs();
    std::shared_ptr<ir::TypeDomain> refer = nullptr;
    int arg_dim = 1;

    for (auto&var : args) {
      const ir::Ty* ty = var->getTyp();
      if (dynamic_cast<const ir::NameTy*>(ty) != NULL) {
        auto t_ref = (dynamic_cast<const ir::NameTy*>(ty))->getRefer();
        if (t_ref->getAllNumberStmt().size() > 0) { // open-type
          if (refer != nullptr) {
            errMsg.error(-1, -1,
              "[MCMC Analyzer] on Random Function <" + f->getName() + ">: [Multiple Arguments with Open-Type] is not supported now.");
          }
          else {
            refer = t_ref;
          }
        }
        else { // close-type
          arg_dim *= t_ref->getInstNames().size();
        }
      }
      else {
        errMsg.error(-1, -1,
          "[MCMC Analyzer] on Random Function <" + f->getName() + ">: [General Type Arguments] is not supported now. Currently we only allow [NameTy] in the argument list.");
      }
    }

    if (refer != nullptr) {
      prop_size[refer] += arg_dim;
      depend_func[refer].push_back(f);
    }
  }

  if (!errMsg.Okay()) {
    prop_size.clear();
    depend_func.clear();
    return false;
  }

  return true;
}

}
} /* namespace swift */
