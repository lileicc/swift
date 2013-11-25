/*
 * VarDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "VarDecl.h"

namespace swift {
namespace code {

VarDecl::VarDecl(DeclContext * context, std::string id, QualType ty) :
    parent(context), id(id), ty(ty) {
}

VarDecl::~VarDecl() {
}

} /* namespace code */
} /* namespace swift */
