/*
 * VarArrayDecl.cpp
 *
 *  Created on: Jul 14, 2014
 *      Author: yiwu
 */

#include "VarArrayDecl.h"

namespace swift {
namespace code {

VarArrayDecl::VarArrayDecl(DeclContext * context, std::string id, Type ty, std::vector<Expr*> arr, Expr* value) :
    VarDecl(context, id, ty, value), arr(arr) {
}

VarArrayDecl::~VarArrayDecl() {
  for(size_t i = 0; i < arr.size(); ++ i)
    if(arr[i] != NULL)
      delete(arr[i]);
}

const std::vector<Expr*>& VarArrayDecl::getArr() const {
  return arr;
}

// For Printer
void VarArrayDecl::print(printer::Printer* prt) {
  prt->print(this);
}

} /* namespace code */
} /* namespace swift */
