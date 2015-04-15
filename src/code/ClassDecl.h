/*
 * ClassDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include <vector>
#include "Decl.h"
#include "DeclContext.h"
#include "Type.h"

namespace swift {
namespace code {

class ClassDecl: public Decl, public DeclContext {
public:
  ~ClassDecl();
  static ClassDecl* createClassDecl(DeclContext* ns, const std::string & name);
  static ClassDecl* createClassDecl(DeclContext* ns, const std::string & name, std::vector<Type> inherit);
  const std::string& getName() const;
  std::vector<Type>& getInherit();

  // For Printer
  void print(printer::Printer* prt);

protected:
  ClassDecl(DeclContext* ns, std::string name, std::vector<Type> inherit = std::vector<Type>());

private:
  DeclContext* parent; // usually it is a namespace
  std::string name;
  // inheritance
  std::vector<Type> inherit;
};

} /* namespace code */
} /* namespace swift */
