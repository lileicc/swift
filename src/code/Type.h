/*
 * QualType.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>

namespace swift {
namespace code {

class Type {
public:
  Type(std::string name, bool refTag=false);
  ~Type();

  std::string getName();
  bool isRef();

private:
  std::string name;
  bool refTag;
};

} /* namespace code */
} /* namespace swift */
