/*
 * NullLiteral.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: leili
 */

#include "NullLiteral.h"

namespace swift {
namespace code {

NullLiteral::NullLiteral() {
}

NullLiteral::~NullLiteral() {
}

void NullLiteral::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
