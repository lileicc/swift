/*
 * NamespaceDecl.h
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

class NamespaceDecl: public Decl, public DeclContext {
public:
  NamespaceDecl(std::string name = std::string());
  ~NamespaceDecl();

  const std::string& getName();

  // For Printer
  void print(printer::Printer* prt);

private:
  std::string name;
};

} /* namespace code */
} /* namespace swift */
