/*
 * MCMCAnalyzer.h
 *
 *  Created on: Apr 16, 2015
 *      Author: yiwu
 */

#pragma once

#include <memory>
#include "Analyzer.h"

namespace swift {
namespace analyzer {

class MCMCAnalyzer: public Analyzer{
public:
  MCMCAnalyzer(ir::BlogModel* _model = NULL);
 
  virtual void process();
};

}
} /* namespace swift */
