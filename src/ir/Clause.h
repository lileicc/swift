/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once

namespace swift{
namespace ir{

class Clause {
public:
  Clause();
  virtual ~Clause();
  void setType(Type* ty);
private:
  Type* ty;
};

}
}