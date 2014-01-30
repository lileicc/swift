/*
 * FloatingLiteral.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "FloatingLiteral.h"

namespace swift {
namespace code {

FloatingLiteral::FloatingLiteral(double val) :
    val(val) {
  // TODO Auto-generated constructor stub

}

FloatingLiteral::~FloatingLiteral() {
  // TODO Auto-generated destructor stub
}

double FloatingLiteral::getVal() const {
  return val;
}

// For Printer
void FloatingLiteral::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
