/*
 * FieldDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once

#include "Decl.h"
#include "ClassDecl.h"
#include "QualType.h"

namespace swift {
namespace code {

class FieldDecl: public swift::code::Decl {
public:
  FieldDecl(std::shared_ptr<ClassDecl> cd, std::string name, std::shared_ptr<QualType> ty);
  ~FieldDecl();

  static std::shared_ptr<FieldDecl> createFieldDecl(std::shared_ptr<ClassDecl> cd, std::string name, std::shared_ptr<QualType> ty);
};

} /* namespace code */
} /* namespace swift */
