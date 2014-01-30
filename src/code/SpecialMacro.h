/*
 * SpecialMacro.h
 *
 *  Created on: Nov 24, 2013
 *      Author: leili
 */

#pragma once

/*
 Special Statement can be any single statement in the source code.

 Note that: ';' (if applicable) must be included!

 For example:
 using namespace std;
 #include <iostream>
 #define LL long long
 etc.
 -- Yi Wu
 */

#include <string>
#include "../printer/Printer.h"

namespace swift {
namespace code {

class SpecialMacro {
public:
  SpecialMacro(std::string stmt = std::string(""));
  ~SpecialMacro();

  const std::string& getMacro() const;

  // For Printer
  void print(printer::Printer* prt);

private:
  std::string stmt;
};

} /* namespace code */
} /* namespace swift */
