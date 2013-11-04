/*
 * ErrorMsg.h
 *
 *  Created on: Nov 3, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <cstdio>

namespace swift {
namespace msg {

class ErrorMsg {
public:
  ErrorMsg(FILE* file);
  ~ErrorMsg();
  void error(int line, int col, std::string info);
private:
  FILE* file;
  int numError;
};

} /* namespace msg */
} /* namespace swift */
