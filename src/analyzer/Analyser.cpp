/*
 * Analyzer.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: leili
 */

#include "Analyser.h"

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
}

}
} /* namespace swift */
