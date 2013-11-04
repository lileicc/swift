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
  Clause(Ty* typ = NULL);
  virtual ~Clause();
  void setTyp(Ty* typ);
  Ty* getTyp();
private:
  Ty* typ;
};

}
}
