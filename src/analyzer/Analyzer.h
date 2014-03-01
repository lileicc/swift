/*
 * Analyzer.h
 *
 *  Created on: Feb 13, 2014
 *      Author: yiwu
 */

#pragma once

#include <memory>
#include "../ir/BlogModel.h"

namespace swift {
namespace analyzer {

class Analyzer {
public:
  Analyzer();
  ~Analyzer();
 
  void process(ir::BlogModel* model);

private:
  // Process Temporal Information
  //   i.e. Markov Order
  void processTemporal(ir::BlogModel* model);
};

}
} /* namespace swift */
