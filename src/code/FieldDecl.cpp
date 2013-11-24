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

FieldDecl::FieldDecl(std::shared_ptr<ClassDecl> cd, std::string name,
    std::shared_ptr<QualType> ty) {
}

FieldDecl::~FieldDecl() {
  // TODO Auto-generated destructor stub
}

std::shared_ptr<FieldDecl> FieldDecl::createFieldDecl(
    std::shared_ptr<ClassDecl> cd, std::string name,
    std::shared_ptr<QualType> ty) {
  std::shared_ptr<FieldDecl> fd(new FieldDecl(cd, name, ty));
  cd->addDecl(fd);
  return fd;
}

} /* namespace code */
} /* namespace swift */
