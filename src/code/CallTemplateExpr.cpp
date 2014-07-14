/*
 * CallTemplateExpr.cpp
 *
 *  Created on: Jul 14, 2014
 *      Author: yiwu
 */

#include "CallTemplateExpr.h"
#include "Identifier.h"
#include "BinaryOperator.h"

namespace swift {
namespace code {

CallTemplateExpr::CallTemplateExpr(code::Expr* fn, std::vector<code::Expr*> args, std::vector<code::Expr*> tempArgs) :
    CallExpr(fn, args), tempArgs(tempArgs) {
}

CallTemplateExpr::~CallTemplateExpr() {
  for(size_t i = 0; i < tempArgs.size(); ++ i)
    if(tempArgs[i] != NULL)
      delete tempArgs[i];
}

const std::vector<Expr*>& CallTemplateExpr::getTempArgs() const {
  return tempArgs;
}

// For Printer
void CallTemplateExpr::print(printer::Printer* prt) {
  prt->print(this);
}

CallTemplateExpr* CallTemplateExpr::createMethodCall(std::string varname,
    std::string methodname, std::vector<Expr*> args, std::vector<Expr*> tempArgs) {
  return new CallTemplateExpr(
      new BinaryOperator(new Identifier(varname), new Identifier(methodname),
          OpKind::BO_FIELD), args, tempArgs);
}

} /* namespace code */
} /* namespace swift */

