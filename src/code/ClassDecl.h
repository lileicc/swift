/*
 * ClassDecl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#pragma once
#include <string>
#include "Decl.h"
#include "DeclContext.h"

namespace swift {
namespace code {

class ClassDecl: public Decl, public DeclContext {
public:
  ~ClassDecl();
  static ClassDecl* createClassDecl(DeclContext* ns, const std::string & name);
  const std::string& getName() const;

  // For Printer
  void print(printer::Printer* prt);

protected:
  ClassDecl(DeclContext* ns, std::string name);

private:
  DeclContext* parent; // usually it is a namespace
  std::string name;
};

} /* namespace code */
} /* namespace swift */
