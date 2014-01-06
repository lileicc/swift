#pragma once

#include <cstdio>
#include <string>

#include "../code/CodeForwardDeclaration.h"

namespace swift {
namespace printer {

class CPPPrinter {
public:
  CPPPrinter(std::string);
  virtual ~CPPPrinter();

  // main framework of the program
  void print(code::Code* prog);

  // Statements and Expressions
  void print(code::ArraySubscriptExpr* term);
  void print(code::BinaryOperator* term);
  void print(code::CallExpr* term);
  void print(code::CaseStmt* term);
  void print(code::ClassDecl* term);
  void print(code::CompoundStmt* term);
  void print(code::DeclStmt* term);
  void print(code::FieldDecl* term);
  void print(code::FloatingLiteral* term);
  void print(code::ForStmt* term);
  void print(code::FunctionDecl* term);
  void print(code::IfStmt* term);
  void print(code::IntegerLiteral* term);
  void print(code::NamespaceDecl* term);
  void print(code::ParamVarDecl* term);
  void print(code::ReturnStmt* term);
  void print(code::SpecialStmt* term);
  void print(code::SwitchStmt* term);
  void print(code::Type* term);
  void print(code::VarDecl* term);
  void print(code::VarRef* term);

private:
  FILE* file;
};

}
}


