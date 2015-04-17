/*
 * Analyzer.h
 *
 *  Created on: Apr 16, 2015
 *      Author: yiwu
 */

#pragma once

#include <memory>
#include "../ir/BlogModel.h"
#include "../msg/ErrorMsg.h"

namespace swift {
namespace analyzer {

class Analyzer {
public:
  Analyzer(ir::BlogModel* _model = NULL);
  virtual ~Analyzer();
 
  virtual bool process() = 0;
  
  virtual void setModel(ir::BlogModel* _model);

protected:
  ir::BlogModel* model;
  msg::ErrorMsg errMsg;
};

}
} /* namespace swift */
