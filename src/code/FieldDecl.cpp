/*
 * FieldDecl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "FieldDecl.h"
#include "QualType.h"

namespace swift {
namespace code {

FieldDecl::FieldDecl(ClassDecl* cd, std::string name,
    std::shared_ptr<QualType> ty) : parent(cd), id(name), ty(ty) {
}

FieldDecl::~FieldDecl() {
  ty = NULL;
}

FieldDecl* FieldDecl::createFieldDecl(ClassDecl* cd, std::string name,
    std::shared_ptr<QualType> ty) {
  FieldDecl* fd = new FieldDecl(cd, name, ty);
  cd->addDecl(fd);
  return fd;
}

} /* namespace code */
} /* namespace swift */
