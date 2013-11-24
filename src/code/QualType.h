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
  QualType(std::string name);
  ~QualType();

private:
  std::string name;
};

} /* namespace code */
} /* namespace swift */
