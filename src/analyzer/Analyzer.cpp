/*
 * Analyzer.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: leili
 */

#include "Analyzer.h"

#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>
#include "../ir/IRHeader.h"

namespace swift {
namespace analyzer {

Analyzer::Analyzer() {
}

Analyzer::~Analyzer() {
}

void Analyzer::process(ir::BlogModel* model) {
  //TODO: To perform optimization here!
  processTemporal(model);
}

void Analyzer::processTemporal(ir::BlogModel* model) {
  // If there is a funcDefn is temporal, then the model is temporal
  for (auto& func : model->getFixFuncs())
    if (func->isTemporal())
      model->setMarkovOrder(0);
  for (auto& func : model->getRandFuncs())
    if (func->isTemporal())
      model->setMarkovOrder(0);

  // TODO: To add Visitor Pattern to resolve this!!!!
  // If there is a Prev(t, x), the max{x} is the markov order

  // Current: hacking implementation, assuming the model is markov
  if (model->isTemporal())
    model->setMarkovOrder(1);
}

}
} /* namespace swift */
