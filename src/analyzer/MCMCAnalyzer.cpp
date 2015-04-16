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

namespace swift {
namespace analyzer {

MCMCAnalyzer::MCMCAnalyzer(ir::BlogModel* _model)
  : Analyzer(_model) {
}

void MCMCAnalyzer::process() {
}

}
} /* namespace swift */
