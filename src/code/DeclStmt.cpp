/*
 * DeclStmt.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "DeclStmt.h"

namespace swift {
namespace code {

DeclStmt::DeclStmt(Decl* dec) : dec(dec) {
}

DeclStmt::~DeclStmt() {
  delete dec;
}

} /* namespace code */
} /* namespace swift */
