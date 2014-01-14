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
  void error(int line, int col, const std::string & info);
  void warning(int line, int col, const std::string & info);

  bool Okay();
private:
  FILE* file;
  int numError;
  int numWarn;
};

} /* namespace msg */
} /* namespace swift */
