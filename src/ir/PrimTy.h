/*
 * PrimTy.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include <string>
namespace swift{
namespace ir{
class PrimTy : public Ty {
public:
  PrimTy();
  ~PrimTy();
  string name;
};
}
}