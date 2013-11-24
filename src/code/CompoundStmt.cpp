/*
 * CompoundStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CompoundStmt.h"

namespace swift {
namespace code {

CompoundStmt::CompoundStmt() {
  // TODO Auto-generated constructor stub

}

CompoundStmt::~CompoundStmt() {
  // TODO Auto-generated destructor stub
}

void CompoundStmt::addStmt(Stmt* st) {
  body.push_back(st);
}

} /* namespace code */
} /* namespace swift */
