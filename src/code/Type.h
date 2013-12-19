/*
 * QualType.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>

#include "../printer/Printer.h"

namespace swift {
namespace code {

class Type {
public:
  Type(std::string name, bool refTag=false);
  ~Type();

  const std::string& getName();
  bool isRef();

  // For Printer
  void print(printer::Printer* prt);
private:
  std::string name;
  bool refTag;
};

} /* namespace code */
} /* namespace swift */
