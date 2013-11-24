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
  FieldDecl(ClassDecl* cd, std::string name, QualType ty);
  ~FieldDecl();

  static FieldDecl* createFieldDecl(ClassDecl* cd, std::string name, QualType ty);

private:
  ClassDecl* parent;
  std::string id;
  QualType ty;
};

} /* namespace code */
} /* namespace swift */
