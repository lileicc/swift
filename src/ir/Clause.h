/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once

#include "IRForwardDecl.h"

namespace swift {
namespace ir {

class Clause {
public:
  Clause(const Ty* typ = NULL);
  virtual ~Clause();
  void setTyp(const Ty* typ);
  const Ty* getTyp() const;
  // For Debugging Use
  virtual void print(FILE* file, int indent);
private:
  const Ty* typ;
};

}
}
