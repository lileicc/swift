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
  numWarn = 0;
}

ErrorMsg::~ErrorMsg() {
  // TODO Auto-generated destructor stub
}

void ErrorMsg::error(int line, int col, const std::string & info) {
  fprintf(file, "Error: line=%d, col=%d: %s\n", line, col, info.c_str());
  numError++;
}

void ErrorMsg::warning(int line, int col, const std::string & info) {
  fprintf(file, "Warning: line=%d, col=%d: %s\n", line, col, info.c_str());
  numWarn++;
}

bool ErrorMsg::Okay() {
  return numError == 0;
}

} /* namespace msg */
} /* namespace swift */
