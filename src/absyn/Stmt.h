/*
 * Stmt.h
 *
 *  Created on: Oct 31, 2013
 *      Author: yiwu
 */

#pragma once

#include "Absyn.h"

namespace swift {
namespace absyn {

class Stmt: public Absyn {
public:
  Stmt(int l, int c);
  virtual ~Stmt();
};

}
}
