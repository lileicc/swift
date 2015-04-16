/*
 * Analyzer.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: yiwu
 */

#include "Analyzer.h"

#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <algorithm>

namespace swift {
namespace analyzer {

Analyzer::Analyzer(ir::BlogModel* _model)
  : model(_model) {
}

Analyzer::~Analyzer() {
}

void Analyzer::setModel(ir::BlogModel* _model) {
  model = _model;
}

}
} /* namespace swift */
