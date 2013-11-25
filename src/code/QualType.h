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

class QualType {
public:
  QualType(std::string name, bool refTag=false);
  ~QualType();

  std::string getName();
  bool isRef();

private:
  std::string name;
  bool refTag;
};

} /* namespace code */
} /* namespace swift */
