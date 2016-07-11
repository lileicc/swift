/*
 * ConjugatePrior.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: yiwu
 */

#include "ConjugatePrior.h"

#include "../../ir/IRHeader.h"

namespace swift {
namespace analyzer {
namespace conjugate {

ConjugatePrior::ConjugatePrior(std::string _distrb)
  : distrb(_distrb) {
}

std::string ConjugatePrior::getDistr() {return distrb;}

}
}
} /* namespace swift */
