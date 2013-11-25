/*
 * ParamVarDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "ParamVarDecl.h"

namespace swift {
namespace code {

ParamVarDecl::ParamVarDecl(DeclContext * context, std::string id, QualType ty) :
    VarDecl(context, id, ty) {
}

ParamVarDecl::~ParamVarDecl() {
}

} /* namespace code */
} /* namespace swift */
