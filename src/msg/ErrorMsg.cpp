/*
 * ErrorMsg.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: leili
 */

#include "ErrorMsg.h"

namespace swift {
namespace msg {

ErrorMsg::ErrorMsg(FILE* file) {
  this->file = file;
  numError = 0;
}

ErrorMsg::~ErrorMsg() {
  // TODO Auto-generated destructor stub
}

void ErrorMsg::error(int line, int col, std::string info) {
  fprintf(file, "Error: line=%d, col=%d: %s\n", line, col, info.c_str());
  numError++;
}

} /* namespace msg */
} /* namespace swift */
