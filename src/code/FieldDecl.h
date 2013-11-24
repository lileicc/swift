/*
 * FieldDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <memory>
#include "Decl.h"
#include "ClassDecl.h"
#include "QualType.h"

namespace swift {
namespace code {

class FieldDecl: public swift::code::Decl {
public:
  FieldDecl(ClassDecl* cd, std::string name, std::shared_ptr<QualType> ty);
  ~FieldDecl();

  static FieldDecl* createFieldDecl(ClassDecl* cd, std::string name, std::shared_ptr<QualType> ty);

private:
  ClassDecl* parent;
  std::string id;
  std::shared_ptr<QualType> ty;
};

} /* namespace code */
} /* namespace swift */
