/*
 * IfThen.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
#pragma once

namespace swift{
namespace ir{

class IfThen: public Clause {
public:
  IfThen();
  ~IfThen();
private:
  Expr* cond;
  Clause* thcl;
  Clause* elcl;
};

}
}